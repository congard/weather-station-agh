#include "HTRecorder.h"
#include "core/Application.h"

#include <esp_log.h>

constexpr static auto TAG = "HTRecorder";

#define LOG(...) ESP_LOGI(TAG, __VA_ARGS__)

HTRecorder::HTRecorder(DHT22Sensor &sensor)
    : m_sensor(sensor),
      m_records(256),
      m_periodSec(10) {}

void HTRecorder::setMaxRecordCount(int count) {
    m_records.resize(count);
}

void HTRecorder::setPeriod(int sec) {
    m_periodSec = sec;
}

int HTRecorder::getMaxRecordCount() const {
    return static_cast<int>(m_records.capacity());
}

int HTRecorder::getPeriod() const {
    return m_periodSec;
}

void HTRecorder::onRun() {
    LOG("Recording has been started");

    while (true) {
        auto humidity = m_sensor.getRelativeHumidity();
        auto temp = m_sensor.getCelsius();

        if (humidity != DHT22Sensor::None && temp != DHT22Sensor::None) {
            std::lock_guard locker(m_mutex);
            auto &record = m_records.emplace_back(humidity, temp, Application::getUptime());
            LOG("Data recorded: humidity=%.1f %%, temperature=%.1f °C, timestamp=%lli, record_count=%zu",
                record.getHumidity(), record.getTemperature(), record.getTimestamp(), m_records.size());
        }

        Application::sleep(m_periodSec * 1000);
    }
}
