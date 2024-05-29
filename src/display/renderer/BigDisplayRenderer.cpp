#include <cstring>

#include "BigDisplayRenderer.h"
#include "../bitmap/BitmapRenderer.h"
#include "../bitmap/Font4x4.h"
#include "../bitmap/Font24x24.h"
#include "../bitmap/Font16x16.h"
#include "core/Application.h"

BigDisplayRenderer::BigDisplayRenderer(Display &parent)
        : DisplayRenderer(parent),
          m_tempRefreshRequired(true),
          m_humidityRefreshRequired(true)
{
    auto &sensor = parent.getApplication().getDHT22Sensor();
    sensor.addOnUpdateListener([this](bool isTempChanged, bool isHumidityChanged) {
        m_tempRefreshRequired = isTempChanged;
        m_humidityRefreshRequired = isHumidityChanged;
    });
}

void BigDisplayRenderer::render() {
    time_t timeSec = Application::getTime();
    auto timeInfo = localtime(&timeSec);

    char strBuff[128];

    auto displayText = [&](int page, bool invert = false) {
        ssd1306_display_text(
                &m_display.getDev(), page, strBuff,
                static_cast<int>(strlen(strBuff)), invert
        );
    };
    constexpr int display_width = 128;
    constexpr int w_f4 = 4 * 8; // 'xx:xx:xx'
    constexpr int w_f4_date = 4 * 10; //xx.xx.xxxx
    constexpr int h_f4 = 4;
    uint8_t buffer_f4[BitmapRenderer::getBufferSize(w_f4, h_f4)] = {0};
    BitmapRenderer renderer_f4 {BitmapView {buffer_f4, w_f4, h_f4}};
    Font4x4 font_4;
    // time
    sprintf(strBuff, "%02i:%02i:%02i", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    renderer_f4.drawText(strBuff, 0, 0, font_4);
    auto showBitmap_f4 = [this, &renderer_f4](int x, int y) {
        ssd1306_bitmaps(&m_display.getDev(), x, y, renderer_f4.data(), renderer_f4.width(), renderer_f4.height(), false);
    };
    showBitmap_f4(display_width / 2 - w_f4 / 2, 0);

    // date
    uint8_t buffer_f4_date[BitmapRenderer::getBufferSize(w_f4_date, h_f4)] = {0};
    BitmapRenderer renderer_f4_date {BitmapView {buffer_f4_date, w_f4_date, h_f4}};
    auto showBitmap_f4_date = [this, &renderer_f4_date](int x, int y) {
        ssd1306_bitmaps(&m_display.getDev(), x, y, renderer_f4_date.data(), renderer_f4_date.width(), renderer_f4_date.height(), false);
    };
    sprintf(strBuff, "%02i.%02i.%i", timeInfo->tm_mday, timeInfo->tm_mon + 1, timeInfo->tm_year + 1900);
    renderer_f4_date.drawText(strBuff, 0, 0, font_4);
    showBitmap_f4_date(display_width / 2 - w_f4_date / 2, 6);

    if (m_tempRefreshRequired || m_humidityRefreshRequired) {
        constexpr int w = 24 * 5; // 'xx.xC', 'xx.x%'
        constexpr int h = 24;
        uint8_t buffer[BitmapRenderer::getBufferSize(w, h)] = {0};
        BitmapRenderer renderer {BitmapView {buffer, w, h}};
        Font24x24 font;
        auto &sensor = m_display.getApplication().getDHT22Sensor();

        auto showBitmap = [this, &renderer](int x, int y) {
            ssd1306_bitmaps(&m_display.getDev(), x, y, renderer.data(), renderer.width(), renderer.height(), false);
        };

        if (m_tempRefreshRequired) {
            sprintf(strBuff, "%.1fC", sensor.getCelsius());
            renderer.drawText(strBuff, 0, 0, font);
            showBitmap(display_width / 2 - w / 2, 12);
            m_tempRefreshRequired = false;
        }

        if (m_humidityRefreshRequired) {
            std::memset(buffer, 0, sizeof(buffer));
            sprintf(strBuff, "%.1f%%", sensor.getRelativeHumidity());
            renderer.drawText(strBuff, 0, 0, font);
            showBitmap(display_width / 2 - w / 2, 40);
            m_humidityRefreshRequired = false;
        }
    }
}

std::string BigDisplayRenderer::getName() {
    return "BigDisplayRenderer";
}
