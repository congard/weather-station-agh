#ifndef WEATHERSTATION_DISPLAYRENDERER_H
#define WEATHERSTATION_DISPLAYRENDERER_H

#include <string>

class Display;

class DisplayRenderer {
public:
    explicit DisplayRenderer(Display &display);
    virtual ~DisplayRenderer() = default;

    virtual void render() = 0;

    virtual std::string getName() = 0;

protected:
    Display &m_display;
};

#endif //WEATHERSTATION_DISPLAYRENDERER_H
