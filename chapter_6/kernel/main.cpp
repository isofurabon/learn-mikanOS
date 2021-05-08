#include <cstdint>
#include <cstddef>
#include <cstdio>
#include "graphics.hpp"
#include "font.hpp"
#include "console.hpp"

void* operator new(size_t size, void* buf) {
    return buf;
}

void operator delete(void* obj) noexcept {
}

constexpr PixelColor DESKTOP_BG_COLOR{45, 118, 237};
constexpr PixelColor DESKTOP_FG_COLOR{255, 255, 255};

constexpr int MOUSE_CURSOR_WIDTH  = 15;
constexpr int MOUSE_CURSOR_HEIGHT = 24;

constexpr char MOUSE_CURSOR_SHAPE[MOUSE_CURSOR_HEIGHT][MOUSE_CURSOR_WIDTH + 1] = {
  "@              ",
  "@@             ",
  "@.@            ",
  "@..@           ",
  "@...@          ",
  "@....@         ",
  "@.....@        ",
  "@......@       ",
  "@.......@      ",
  "@........@     ",
  "@.........@    ",
  "@..........@   ",
  "@...........@  ",
  "@............@ ",
  "@......@@@@@@@@",
  "@......@       ",
  "@....@@.@      ",
  "@...@ @.@      ",
  "@..@   @.@     ",
  "@.@    @.@     ",
  "@@      @.@    ",
  "@       @.@    ",
  "         @.@   ",
  "         @@@   ",
};

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

    /* draw mouse */
    for(int dy = 0; dy < MOUSE_CURSOR_HEIGHT; ++dy){
        for(int dx = 0; dx < MOUSE_CURSOR_WIDTH; ++dx){
            if (MOUSE_CURSOR_SHAPE[dy][dx] == '@'){
                pixel_writer->Write(200 + dx, 100 + dy, {0, 0, 0});
            } else if (MOUSE_CURSOR_SHAPE[dy][dx] == '.'){
                pixel_writer->Write(200 + dx, 100 + dy, {255, 255, 255});
            }
        }
    }
    while (1) __asm__("hlt");
}
