#include "mouse.hpp"
#include "graphics.hpp"

namespace {
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

    void DrawMouseCursor(const PixelWriter* pixel_writer, const Vector2D<int> position) {
        /* draw mouse */
        for(int dy = 0; dy < MOUSE_CURSOR_HEIGHT; ++dy){
            for(int dx = 0; dx < MOUSE_CURSOR_WIDTH; ++dx){
                if (MOUSE_CURSOR_SHAPE[dy][dx] == '@'){
                    pixel_writer->Write(position.x + dx, position.y + dy, {0, 0, 0});
                } else if (MOUSE_CURSOR_SHAPE[dy][dx] == '.'){
                    pixel_writer->Write(position.x + dx, 100 + position.y, {255, 255, 255});
                }
            }
        }
    }

    void EraseMouseCursor(const PixelWriter* pixel_writer, const Vector2D<int> position, const PixelColor erase_color) {
        for(int dy = 0; dy < MOUSE_CURSOR_HEIGHT; ++dy){
            for(int dx = 0; dx < MOUSE_CURSOR_WIDTH; ++dx){
                if (MOUSE_CURSOR_SHAPE[dy][dx] != ' '){
                    pixel_writer->Write(position.x + dx, position.y + dy, erase_color);
                }
            }
        }
    }
}

MouseCursor::MouseCursor(PixelWriter* writer, const PixelColor erase_color, const Vector2D<int> initial_position)
    :m_pixel_writer{writer}, m_erase_color{erase_color}, m_position{initial_position} {
        DrawMouseCursor(m_pixel_writer, m_position);
    }

void MouseCursor::MoveRelative(const Vector2D<int> displacement) {
    EraseMouseCursor(m_pixel_writer, m_position, m_erase_color);
    m_position += displacement;
    DrawMouseCursor(m_pixel_writer, m_position);
}
