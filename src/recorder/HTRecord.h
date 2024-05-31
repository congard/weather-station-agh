#ifndef WEATHERSTATION_HTRECORD_H
#define WEATHERSTATION_HTRECORD_H

#include <ctime>

namespace ws {
/**
 * Stands for Humidity Temperature Record
 *
 * <br><br>Stores 32-bit float as just 12 bits.
 *
 * <br><br>Floating point precision:
 * <ul>
 *   <li>Integral part: 8-bit precision</li>
 *   <li>Floating part: 4-bit precision</li>
 * </ul>
 */
class __attribute__((packed)) HTRecord {
public:
    HTRecord(float humidity, float temp, uint32_t timestamp);

    float getHumidity() const;
    float getTemperature() const;

    /**
     * @return The time in ms counted from the device boot
     * @note Overflows every ≈49 days
     */
    uint32_t getTimestamp() const;

private:
    int8_t m_humidity;
    int8_t m_temp;
    uint8_t m_floatParts;
    uint32_t m_timestamp;
};
}

#endif //WEATHERSTATION_HTRECORD_H
