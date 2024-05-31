#ifndef WEATHERSTATION_FONT16X16_H
#define WEATHERSTATION_FONT16X16_H

#include "Font.h"

namespace ws {
class Font16x16 : public Font {
public:
    const uint8_t *getChar(char c) const override;
    int width() const override;
    int height() const override;
};
}

#endif //WEATHERSTATION_FONT16X16_H
