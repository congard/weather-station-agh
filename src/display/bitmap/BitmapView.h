#ifndef WEATHERSTATION_BITMAPVIEW_H
#define WEATHERSTATION_BITMAPVIEW_H

#include <cstdint>

class BitmapView {
public:
    inline BitmapView(uint8_t *bitmap, int16_t width, int16_t height)
        : m_bitmap(bitmap),
          m_width(width),
          m_height(height) {}

    inline auto data() const {
        return m_bitmap;
    }

    inline auto width() const {
        return m_width;
    }

    inline auto height() const {
        return m_height;
    }

    inline auto operator[](int index) const {
        return m_bitmap[index];
    }

    inline auto& operator[](int index) {
        return m_bitmap[index];
    }

private:
    uint8_t *m_bitmap;
    int16_t m_width;
    int16_t m_height;
};

#endif //WEATHERSTATION_BITMAPVIEW_H
