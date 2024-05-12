#include "Display.h"
#include "renderer/DefaultDisplayRenderer.h"

#include <esp_log.h>

#define TAG "Display"

Display::Display(Application &application)
    : m_application(application),
      m_renderer(),
      m_dev() {}

void Display::setRenderer(DisplayRendererPtr renderer) {
    m_renderer = std::move(renderer);
}

DisplayRenderer* Display::getRenderer() const {
    return m_renderer.get();
}

SSD1306_t& Display::getDev() {
    return m_dev;
}

Application& Display::getApplication() {
    return m_application;
}

void Display::initDriver() {
#if CONFIG_I2C_INTERFACE
    ESP_LOGI(TAG, "INTERFACE is i2c");
    ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d", CONFIG_SDA_GPIO);
    ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d", CONFIG_SCL_GPIO);
    ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
    i2c_master_init(&m_dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
    ESP_LOGI(tag, "INTERFACE is SPI");
	ESP_LOGI(tag, "CONFIG_MOSI_GPIO=%d", CONFIG_MOSI_GPIO);
	ESP_LOGI(tag, "CONFIG_SCLK_GPIO=%d", CONFIG_SCLK_GPIO);
	ESP_LOGI(tag, "CONFIG_CS_GPIO=%d", CONFIG_CS_GPIO);
	ESP_LOGI(tag, "CONFIG_DC_GPIO=%d", CONFIG_DC_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
	spi_master_init(&m_dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_FLIP
    m_dev._flip = true;
	ESP_LOGW(tag, "Flip upside down");
#endif

#if CONFIG_SSD1306_128x64
    ESP_LOGI(TAG, "Panel is 128x64");
    ssd1306_init(&m_dev, 128, 64);
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
    ESP_LOGI(tag, "Panel is 128x32");
	ssd1306_init(&m_dev, 128, 32);
#endif // CONFIG_SSD1306_128x32

    ssd1306_clear_screen(&m_dev, false);
    ssd1306_contrast(&m_dev, 0xff);
    ssd1306_display_text(&m_dev, 4, " WeatherStation", 15, false);
    vTaskDelay(pdMS_TO_TICKS(1000));
    ssd1306_clear_screen(&m_dev, false);
}

void Display::onRun() {
    initDriver();

    if (m_renderer == nullptr)
        m_renderer = std::make_unique<DefaultDisplayRenderer>(*this);

    constexpr auto updateDelay = 1000;

    while (true) {
        m_renderer->render();
        vTaskDelay(pdMS_TO_TICKS(updateDelay));
    }
}
