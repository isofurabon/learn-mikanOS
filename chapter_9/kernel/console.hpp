#pragma once

#include "graphics.hpp"

class Console {
public:
    static constexpr int kRows = 25, kColumns = 80;

    Console(const PixelColor& fg_color, const PixelColor& bg_color);
    void PutString(const char* s);
    void SetWriter(PixelWriter* writer);

private:
    void NewLine();
    void Refresh();

    PixelWriter* m_writer;
    const PixelColor m_fg_color, m_bg_color;
    char m_buffer[kRows][kColumns+1];
    int m_cursor_row, m_cursor_column;
};