#include "HTRecord.h"

#include <cmath>

namespace ws {
HTRecord::HTRecord(float humidity, float temp, uint32_t timestamp)
    : m_humidity(static_cast<int8_t>(humidity)),
      m_temp(static_cast<int8_t>(temp)),
      m_timestamp(timestamp)
{
    // returns 1st floating digit
    auto floating = [](float f, int8_t i8) {
        return static_cast<uint8_t>(std::round((f - (float) i8) * 10));
    };

    auto humidityFloating = floating(humidity, m_humidity);
    auto tempFloating = floating(temp, m_temp);

    m_floatParts = static_cast<uint8_t>((humidityFloating << 4) | tempFloating);
}

float HTRecord::getHumidity() const {
    auto i = static_cast<float>(m_humidity);
    auto f = static_cast<float>(m_floatParts >> 4) / 10.0f;
    return i + f;
}

float HTRecord::getTemperature() const {
    auto i = static_cast<float>(m_temp);
    auto f = static_cast<float>(m_floatParts & 0b00001111) / 10.0f;
    return i + f;
}

uint32_t HTRecord::getTimestamp() const {
    return m_timestamp;
}
}
