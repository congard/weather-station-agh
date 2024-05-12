#ifndef WEATHERSTATION_DHT22SENSOR_H
#define WEATHERSTATION_DHT22SENSOR_H

#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "core/Runner.h"

#include <tulz/observer/Subject.h>
#include <atomic>

class DHT22Sensor : public TemperatureSensor, public HumiditySensor, public Runner {
    // isTempChanged, isHumidityChanged
    using UpdateSubject_t = tulz::Subject<bool, bool>;

public:
    DHT22Sensor();

    DHT22Sensor(const DHT22Sensor&) = delete;
    DHT22Sensor(DHT22Sensor&&) = delete;

    DHT22Sensor& operator=(const DHT22Sensor&) = delete;
    DHT22Sensor& operator=(DHT22Sensor&&) = delete;

    void setUpdateFrequency(int ms);
    int getUpdateFrequency() const;

    float getCelsius() const override;
    float getRelativeHumidity() const override;

    UpdateSubject_t::Subscription_t addOnUpdateListener(const UpdateSubject_t::Observer_t &listener);

protected:
    [[noreturn]] void onRun() override;

private:
    int m_updateFreq;
    UpdateSubject_t m_onUpdate;

private:
    std::atomic<float> m_celsius;
    std::atomic<float> m_humidity;
};

#endif //WEATHERSTATION_DHT22SENSOR_H
