#ifndef WEATHERSTATION_FONT_H
#define WEATHERSTATION_FONT_H

#include <cstdint>

class Font {
public:
    virtual ~Font() = default;

    virtual const uint8_t* getChar(char c) const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;

    inline auto operator[](char c) const {
        return getChar(c);
    }
};

#endif //WEATHERSTATION_FONT_H
