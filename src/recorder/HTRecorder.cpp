#include "HTRecorder.h"
#include "core/Application.h"
#include "core/log.h"

LOG_TAG("HTRecorder");

namespace ws {
HTRecorder::HTRecorder(DHT22Sensor &sensor)
    : m_sensor(sensor),
      m_records(256),
      m_periodSec(10) {}

void HTRecorder::setMaxRecordCount(int count) {
    m_records.resize(count);
}

void HTRecorder::setPeriod(int sec) {
    m_periodSec = std::max(sec, DHT22Sensor::MinUpdateFreq / 1000);
}

int HTRecorder::getMaxRecordCount() const {
    return static_cast<int>(m_records.capacity());
}

int HTRecorder::getPeriod() const {
    return m_periodSec;
}

void HTRecorder::onRun() {
    LOGI("Recording has been started");

    while (true) {
        auto humidity = m_sensor.getRelativeHumidity();
        auto temp = m_sensor.getCelsius();

        if (humidity != DHT22Sensor::None && temp != DHT22Sensor::None) {
            std::lock_guard locker(m_mutex);
            auto &record = m_records.emplace_back(humidity, temp, Application::getUptime());
            LOGI("Data recorded: humidity=%.1f %%, temperature=%.1f °C, timestamp=%lu, record_count=%zu",
                 record.getHumidity(), record.getTemperature(), record.getTimestamp(), m_records.size());
        }

        Application::sleep(m_periodSec * 1000);
    }
}
}
