#include "mouse.hpp"
#include "graphics.hpp"

namespace {
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
}

void DrawMouseCursor(PixelWriter* pixel_writer, Vector2D<int> position) {
  for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
    for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
      if (MOUSE_CURSOR_SHAPE[dy][dx] == '@') {
        pixel_writer->Write(position.x + dx, position.y + dy, {0, 0, 0});
      } else if (MOUSE_CURSOR_SHAPE[dy][dx] == '.') {
        pixel_writer->Write(position.x + dx, position.y + dy, {255, 255, 255});
      } else {
        pixel_writer->Write(position.x + dx, position.y + dy, kMouseTransparentColor);
       }
     }
   }
 }