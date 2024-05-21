
#ifndef WEATHERSTATION_FONT4X4_H
#define WEATHERSTATION_FONT4X4_H

#include "Font.h"

class Font4x4 : public Font {
public:
    const uint8_t *getChar(char c) const override;
    int width() const override;
    int height() const override;
};

#endif //WEATHERSTATION_FONT4X4_H