#ifndef WEATHERSTATION_DEFAULTDISPLAYRENDERER_H
#define WEATHERSTATION_DEFAULTDISPLAYRENDERER_H

#include "DisplayRenderer.h"

namespace ws {
class DefaultDisplayRenderer : public DisplayRenderer {
public:
    explicit DefaultDisplayRenderer(Display &parent);

    void render() override;

private:
    bool m_tempRefreshRequired;
    bool m_humidityRefreshRequired;
};
}

#endif //WEATHERSTATION_DEFAULTDISPLAYRENDERER_H
