#pragma once
#include "frame_buffer_config.hpp"

struct PixelColor {
    uint8_t r, g, b;
};

inline bool operator==(const PixelColor& lhs, const PixelColor& rhs) {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

inline bool operator!=(const PixelColor& lhs, const PixelColor& rhs) {
    return !(lhs == rhs);
}

class PixelWriter {
public:
    virtual ~PixelWriter() = default;
    virtual void Write(int x, int y, const PixelColor& c) = 0;
    virtual int Width() const = 0;
    virtual int Height() const = 0;
};

class FrameBufferWriter : public PixelWriter {
public:
    FrameBufferWriter(const FrameBufferConfig& config) :m_config{config} {}
    virtual ~FrameBufferWriter() = default;
    virtual int Width() const override { return m_config.horizontal_resolution; }
    virtual int Height() const override { return m_config.vertical_resolution; }

protected:
    inline uint8_t* PixelAt(int x, int y) const {
        return m_config.frame_buffer + 4 * (m_config.pixels_per_scan_line * y + x);
    }

private:
    const FrameBufferConfig& m_config;
};

class RGBResv8BitPerColorPixelWriter : public FrameBufferWriter {
public:
    // https://cpprefjp.github.io/lang/cpp11/inheriting_constructors.html
    using FrameBufferWriter::FrameBufferWriter;

    virtual void Write(int x, int y, const PixelColor& c) override;
};

class BGRResv8BitPerColorPixelWriter : public FrameBufferWriter {
public:
    using FrameBufferWriter::FrameBufferWriter;

    virtual void Write(int x, int y, const PixelColor& c) override;
};

template <typename T>
struct Vector2D {
    T x, y;

    template <typename U>
    Vector2D<T>& operator +=(const Vector2D<U>& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
};

void DrawRectangle(PixelWriter& writer, const Vector2D<int>& pos, const Vector2D<int>& size, const PixelColor& c);
void FillRectangle(PixelWriter& writer, const Vector2D<int>& pos, const Vector2D<int>& size, const PixelColor& c);

const PixelColor kDesktopBGColor{45, 118, 237};
const PixelColor kDesktopFGColor{255, 255, 255};

void DrawDesktop(PixelWriter& writer);