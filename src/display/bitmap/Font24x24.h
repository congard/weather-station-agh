
#ifndef WEATHERSTATION_FONT24X24_H
#define WEATHERSTATION_FONT24X24_H

#include "Font.h"

class Font24x24 : public Font {
        public:
        const uint8_t *getChar(char c) const override;
        int width() const override;
        int height() const override;
};


#endif //WEATHERSTATION_FONT24X24_H
