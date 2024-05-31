#include "DHT22Sensor.h"

#include <am2302_rmt.h>
#include <esp_log.h>

#define TAG "DHT22Sensor"

namespace ws {
DHT22Sensor::DHT22Sensor()
    : m_updateFreq(MinUpdateFreq),
      m_celsius(None),
      m_humidity(None) {}

void DHT22Sensor::setUpdateFrequency(int ms) {
    m_updateFreq = std::max(ms, MinUpdateFreq);
}

int DHT22Sensor::getUpdateFrequency() const {
    return m_updateFreq;
}

float DHT22Sensor::getCelsius() const {
    return m_celsius;
}

float DHT22Sensor::getRelativeHumidity() const {
    return m_humidity;
}

DHT22Sensor::UpdateSubject_t::Subscription_t DHT22Sensor::addOnUpdateListener(
    const UpdateSubject_t::Observer_t &listener
) {
    return m_onUpdate.subscribe(listener);
}

void DHT22Sensor::onRun() {
    am2302_config_t am2302_config = {
        .gpio_num = 4, // TODO: config constant
    };
    am2302_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
    };

    am2302_handle_t sensor {};
    ESP_ERROR_CHECK(am2302_new_sensor_rmt(&am2302_config, &rmt_config, &sensor));

    ESP_LOGI(TAG, "Sensor is ready");

    while (true) {
        // the delay between each sensor read is required by the data sheet
        vTaskDelay(pdMS_TO_TICKS(m_updateFreq));

        float temperature;
        float humidity;

        ESP_ERROR_CHECK(am2302_read_temp_humi(sensor, &temperature, &humidity));
        ESP_LOGI(TAG, "Temperature: %.1f °C, Humidity: %.1f %%", temperature, humidity);

        auto almostEquals = [](float f1, float f2, float eps = 0.05f) {
            return std::abs(f1 - f2) < eps;
        };

        bool isTempChanged = !almostEquals(m_celsius, temperature);
        bool isHumidityChanged = !almostEquals(m_humidity, humidity);

        m_celsius = temperature;
        m_humidity = humidity;

        if (isTempChanged || isHumidityChanged) {
            m_onUpdate.notify(isTempChanged, isHumidityChanged);
        }
    }
}
}
