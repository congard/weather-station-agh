
#ifndef WEATHER_STATION_AGH_BIGDISPLAYRENDERER_H
#define WEATHER_STATION_AGH_BIGDISPLAYRENDERER_H

#include "DisplayRenderer.h"

class BigDisplayRenderer : public DisplayRenderer {
public:
    explicit BigDisplayRenderer(Display &parent);

    void render() override;

    std::string getName() override;

private:
    bool m_tempRefreshRequired;
    bool m_humidityRefreshRequired;
};


#endif //WEATHER_STATION_AGH_BIGDISPLAYRENDERER_H
