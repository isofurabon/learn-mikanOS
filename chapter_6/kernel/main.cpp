#include <cstdint>
#include <cstddef>
#include <cstdio>

#include <numeric>
#include <vector>

#include "graphics.hpp"
#include "mouse.hpp"
#include "font.hpp"
#include "console.hpp"
#include "pci.hpp"
#include "logger.hpp"
#include "usb/memory.hpp"
#include "usb/device.hpp"
#include "usb/classdriver/mouse.hpp"
#include "usb/xhci/xhci.hpp"
#include "usb/xhci/trb.hpp"

void operator delete(void* obj) noexcept {
}

constexpr PixelColor DESKTOP_BG_COLOR{45, 118, 237};
constexpr PixelColor DESKTOP_FG_COLOR{255, 255, 255};


char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

char console_buf[sizeof(Console)];
Console* console;

int printk(const char* format, ...){
    va_list ap;
    int result;
    char s[1024];

    va_start(ap, format);
    result = vsprintf(s, format, ap);
    va_end(ap);

    console->PutString(s);
    return result;
}

char mouse_cursor_buf[sizeof(MouseCursor)];
MouseCursor* mouse_cursor;

void MouseObserver(int8_t displacement_x, int8_t displacement_y) {
    mouse_cursor->MoveRelative({displacement_x, displacement_y});
}

void SwitchEhci2Xhci(const pci::Device& xhc_dev) {
    bool intel_ehc_exist = false;
    for(int i = 0; i < pci::num_devices; ++i) {
        if (pci::devices[i].class_code.Match(0x0cu, 0x03u, 0x20u) && 0x8086 == pci::ReadVendorId(pci::devices[i])) {
            intel_ehc_exist = true;
            break;
        }
    }

    if (!intel_ehc_exist){
        return;
    }

    uint32_t superspeed_ports = pci::ReadConfReg(xhc_dev, 0xdc);
    pci::WriteConfReg(xhc_dev, 0xd8, superspeed_ports);

    uint32_t ehci2xhci_ports = pci::ReadConfReg(xhc_dev, 0xd4);
    pci::WriteConfReg(xhc_dev, 0xd0, ehci2xhci_ports);

    Log(kDebug, "SwitchEhci2Xhci: S = %02x, xHCI = %02x \n", superspeed_ports, ehci2xhci_ports);
}

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) 
{
    // create pixel writer
    switch(frame_buffer_config.pixel_format){
        case kPixelRGBResv8BitPerColor: 
            pixel_writer = new(pixel_writer_buf)RGBResv8BitPerColorPixelWriter{frame_buffer_config};
            break;

        case kPixelBGRResv8BitPerColor: 
            pixel_writer = new(pixel_writer_buf)BGRResv8BitPerColorPixelWriter{frame_buffer_config};
            break;
    } 

    const int FRAME_WIDTH = frame_buffer_config.horizontal_resolution;
    const int FRAME_HEIGHT = frame_buffer_config.vertical_resolution;

    /* draw desktop */
    FillRectangle(*pixel_writer, {0, 0}, {FRAME_WIDTH, FRAME_HEIGHT - 50}, DESKTOP_BG_COLOR);
    FillRectangle(*pixel_writer, {0, FRAME_HEIGHT - 50}, {FRAME_WIDTH, 50}, {1, 8, 17});
    FillRectangle(*pixel_writer, {0, FRAME_HEIGHT - 50}, {FRAME_WIDTH / 5, 50}, {80, 80, 80});
    DrawRectangle(*pixel_writer, {10, FRAME_HEIGHT - 40}, {30, 30}, {160, 160, 160});

    // create console
    console = new(console_buf)Console{*pixel_writer, DESKTOP_FG_COLOR, DESKTOP_BG_COLOR};
    printk("Welcome to MikanOS!\n");

    SetLogLevel(kDebug);
    
    // Setup mouse
    mouse_cursor = new(mouse_cursor_buf) MouseCursor{
        pixel_writer, DESKTOP_BG_COLOR, {300, 200}
    };


    // Show Devices
    auto err = pci::ScanAllBus();
    Log(kDebug, "ScanAllBus: %s\n", err.Name());

    for(int i = 0; i < pci::num_devices; ++i){
        const auto& dev = pci::devices[i];
        auto vender_id = pci::ReadVendorId(dev);
        auto class_code = pci::ReadClassCode(dev.bus, dev.device, dev.function);

        Log(kDebug, "%d.%d.%d: vend %04x, class %08x (base:%02x, sub:%02x, interface:%02x) head %02x\n", 
            dev.bus, dev.device, dev.function,
            vender_id, class_code, class_code.base, class_code.sub, class_code.interface, dev.header_type);
    }

    // search xHC
    pci::Device* xhc_dev = nullptr;
    for(int i = 0; i < pci::num_devices; ++i) {
        if (pci::devices[i].class_code.Match(0x0cu, 0x03u, 0x30u)) {
            xhc_dev = &pci::devices[i];

            if (0x8086 == pci::ReadVendorId(*xhc_dev)) {
                break;
            }
        }
    }

    if (xhc_dev) {
        Log(kInfo, "xHC has been found: %d.%d.%d\n", xhc_dev->bus, xhc_dev->device, xhc_dev->function);
    }

    // read bar register
    const WithError<uint64_t> xhc_bar = pci::ReadBar(*xhc_dev, 0);
    Log(kDebug, "ReadBar: %s\n", xhc_bar.error.Name());

    const uint64_t xhc_mmio_base = xhc_bar.value & ~static_cast<uint64_t>(0xf);
    Log(kDebug, "xHC mmio_base = %08lx\n", xhc_mmio_base);

    usb::xhci::Controller xhc{xhc_mmio_base};

    if ( 0x8086 == pci::ReadVendorId(*xhc_dev)) {
        SwitchEhci2Xhci(*xhc_dev);
    }
    {
        auto err = xhc.Initialize();
        Log(kDebug, "xhc.Initialize: %s \n", err.Name());
    }

    Log(kInfo, "xHC starting\n");
    xhc.Run();

    usb::HIDMouseDriver::default_observer = MouseObserver;

    for(int i = 1; i <= xhc.MaxPorts(); ++i){
        auto port = xhc.PortAt(i);
        Log(kDebug, "Port %d: IsConnected=%d\n", i, port.IsConnected());

        if (port.IsConnected()){
            if (auto err = ConfigurePort(xhc, port)){
                Log(kError, "failed to confgure port: %s at %s:%d\n", err.Name(), err.File(), err.Line());
                continue;
            }
        }
    }

    while (1) {
        if (auto err = ProcessEvent(xhc)) {
            Log(kError, "Error while ProcessEvent: %s at %s : %d\n", err.Name(), err.File(), err.Line());
        }
    }

    while (1) __asm__("hlt");
}

extern "C" void __cxa_pure_virtual() {
   while (1) __asm__("hlt");
}