#ifndef WEATHERSTATION_DISPLAYCOMPONENT_H
#define WEATHERSTATION_DISPLAYCOMPONENT_H

#include "rest/RESTComponent.h"

class Display;

class DisplayComponent : public RESTComponent {
public:
    explicit DisplayComponent(Display &display);

    void enableFor(RESTServer &server) override;

private:
    void get(Request &req);
    void post(Request &req);

    static void getRenderers(Request &req);

private:
    void setRenderer(std::string_view name);
    std::string getRendererName() const;

private:
    Display &m_display;
};

#endif //WEATHERSTATION_DISPLAYCOMPONENT_H
