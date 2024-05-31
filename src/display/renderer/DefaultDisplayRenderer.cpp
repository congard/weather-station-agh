#include <cstring>

#include "DefaultDisplayRenderer.h"
#include "../bitmap/BitmapRenderer.h"
#include "../bitmap/Font16x16.h"
#include "core/Application.h"

DefaultDisplayRenderer::DefaultDisplayRenderer(Display &parent)
    : DisplayRenderer(parent),
      m_tempRefreshRequired(true),
      m_humidityRefreshRequired(true)
{
    auto &sensor = parent.getApplication().getHTModule().getSensor();
    sensor.addOnUpdateListener([this](bool isTempChanged, bool isHumidityChanged) {
        m_tempRefreshRequired = isTempChanged;
        m_humidityRefreshRequired = isHumidityChanged;
    });
}

void DefaultDisplayRenderer::render() {
    time_t timeSec = Application::getTime();
    auto timeInfo = localtime(&timeSec);

    char strBuff[128];

    auto displayText = [&](int page, bool invert = false) {
        ssd1306_display_text(
            &m_display.getDev(), page, strBuff,
            static_cast<int>(strlen(strBuff)), invert
        );
    };

    // time
    sprintf(strBuff, "%02i:%02i:%02i", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    displayText(0);

    // date
    sprintf(strBuff, "%02i.%02i.%i", timeInfo->tm_mday, timeInfo->tm_mon + 1, timeInfo->tm_year + 1900);
    displayText(1);

    // temperature and humidity
    if (m_tempRefreshRequired || m_humidityRefreshRequired) {
        constexpr int w = 16 * 5; // 'xx.xC', 'xx.x%'
        constexpr int h = 16;
        uint8_t buffer[BitmapRenderer::getBufferSize(w, h)] = {0};
        BitmapRenderer renderer {BitmapView {buffer, w, h}};
        Font16x16 font;
        auto &sensor = m_display.getApplication().getHTModule().getSensor();

        auto showBitmap = [this, &renderer](int x, int y) {
            ssd1306_bitmaps(&m_display.getDev(), x, y, renderer.data(), renderer.width(), renderer.height(), false);
        };

        if (m_tempRefreshRequired) {
            sprintf(strBuff, "%.1fC", sensor.getCelsius());
            renderer.drawText(strBuff, 0, 0, font);
            showBitmap(128 / 2 - w / 2, 16); // TODO: constant for 128 (display width)
            m_tempRefreshRequired = false;
        }

        if (m_humidityRefreshRequired) {
            std::memset(buffer, 0, sizeof(buffer));
            sprintf(strBuff, "%.1f%%", sensor.getRelativeHumidity());
            renderer.drawText(strBuff, 0, 0, font);
            showBitmap(128 / 2 - w / 2, 32);
            m_humidityRefreshRequired = false;
        }
    }
}

std::string DefaultDisplayRenderer::getName() {
    return "DefaultDisplayRenderer";
}
