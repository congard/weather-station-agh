#ifndef WEATHERSTATION_DISPLAYRENDERER_H
#define WEATHERSTATION_DISPLAYRENDERER_H

#include <string>
#include <tulz/util/noncopyable.h>

namespace ws {
class Display;

class DisplayRenderer : tulz::noncopyable {
public:
    explicit DisplayRenderer(Display &display);
    virtual ~DisplayRenderer() = default;

    virtual void render() = 0;

protected:
    Display &m_display;
};
}

#endif //WEATHERSTATION_DISPLAYRENDERER_H
