#ifndef WEATHERSTATION_TEMPERATURESENSOR_H
#define WEATHERSTATION_TEMPERATURESENSOR_H

namespace ws {
class TemperatureSensor {
public:
    virtual ~TemperatureSensor() = default;

    virtual float getCelsius() const = 0;
};
}

#endif //WEATHERSTATION_TEMPERATURESENSOR_H
