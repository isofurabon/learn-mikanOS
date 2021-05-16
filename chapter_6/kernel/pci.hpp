/**
 * Control PCI bus
 * 
 */

#pragma once

#include <cstdint>
#include <array>

#include "error.hpp"

namespace pci {
    /* Constants */
    // I/O port address for CONFIG_ADDRESS 
    constexpr uint16_t ConfigAddress = 0x0cf8;

    //I/O port address for CONFIG_DATA
    constexpr uint16_t ConfigData = 0x0cfc;

    struct ClassCode {
        uint8_t base, sub, interface;

        bool Match(uint8_t b) { return b == base; }

        bool Match(uint8_t b, uint8_t s) { return Match(b) && s == sub; }

        bool Match(uint8_t b, uint8_t s, uint8_t i) { return Match(b, s) && i == interface; }
    };

    struct Device {
        uint8_t bus, device, function, header_type;
        ClassCode class_code;
    };

    /* Basic Read/Write */
    void WriteAddress(uint32_t address);
    void WriteData(uint32_t value);
    uint32_t ReadData();

    /* Read/Write PCI Configuration */ 
    uint16_t ReadVendorId(uint8_t bus, uint8_t device, uint8_t function);
    uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function);
    uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function);  

    /*
    * 31:24 - Base class
    * 21:16 - Sub class
    * 15:8  - Interface  
    * 7:0   - Revision
    */ 
    ClassCode ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);

    inline uint16_t ReadVendorId(const Device& dev) {
        return ReadVendorId(dev.bus, dev.device, dev.function);
    }

    uint32_t ReadConfReg(const Device& dev, uint8_t reg_addr);
    void WriteConfReg(const Device& dev, uint8_t reg_addr, uint32_t value);

    /*
    * 23:16 - Subordinate bus
    * 15:8  - Secondary bus
    * 7:0   - Revision
    */ 
    uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);

    bool IsSingleFunctionDevice(uint8_t header_type);


    inline std::array<Device, 32> devices;
    inline int num_devices;

    /* search all pci devices recursively, then put them into 'devices' array. */
    Error ScanAllBus();

    constexpr uint8_t CalcBarAddress(unsigned int bar_index) {
        return 0x10 + 4 * bar_index;
    }

    WithError<uint64_t> ReadBar(Device& device, unsigned int bar_index);
}