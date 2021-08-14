#include "console.hpp"

#include <cstring>
#include "font.hpp"
#include "layer.hpp"

Console::Console(const PixelColor& fg_color, const PixelColor& bg_color):
    m_writer{nullptr}, m_fg_color{fg_color}, m_bg_color{bg_color}, m_buffer{}, m_cursor_row{0}, m_cursor_column{0} {}

void Console::PutString(const char* s){
    while(*s) {
        if (*s == '\n'){
            NewLine();
        } else if (m_cursor_column < kColumns - 1){
            WriteAscii(*m_writer, Vector2D<int>{8 * m_cursor_column, 16 * m_cursor_row}, *s, m_fg_color);
            m_buffer[m_cursor_row][m_cursor_column] = *s;
            ++m_cursor_column;
        }
        ++s;
    }
    if (layer_manager) {
        layer_manager->Draw();
    }
}

void Console::SetWriter(PixelWriter* writer) {
    if (writer == m_writer) {
        return;
    }
    m_writer = writer;
    Refresh();
}


void Console::NewLine() {
    m_cursor_column = 0;
    if (m_cursor_row < kRows - 1){
        ++m_cursor_row;
    } else {
        // fill console with bg color
        for (int y = 0; y < 16 * kRows; ++y){
            for (int x = 0; x < 8 * kColumns; ++x){
                m_writer->Write(Vector2D<int>{x, y}, m_bg_color);
            }
        }

        // scroll (re-write characters from buf)
        for (int row = 0; row < kRows - 1; ++row){
            memcpy(m_buffer[row], m_buffer[row+1], kColumns+1);
            WriteString(*m_writer, Vector2D<int>{0, 16*row}, m_buffer[row], m_fg_color);
        }
        memset(m_buffer[kRows - 1], 0, kColumns+1);
    }
}

void Console::Refresh() {
    for (int row = 0; row < kRows; ++row) {
        WriteString(*m_writer, Vector2D<int>{0, 16 * row}, m_buffer[row], m_fg_color);
    }
}