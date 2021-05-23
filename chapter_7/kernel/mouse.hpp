#pragma once
#include "graphics.hpp"

class MouseCursor {
public:
    MouseCursor(PixelWriter* writer, const PixelColor erase_color, const Vector2D<int> initial_position);
    void MoveRelative(const Vector2D<int> displacement);

private:
    PixelWriter* m_pixel_writer = nullptr;
    PixelColor m_erase_color;
    Vector2D<int> m_position;
};