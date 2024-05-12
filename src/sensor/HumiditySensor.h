#ifndef WEATHERSTATION_HUMIDITYSENSOR_H
#define WEATHERSTATION_HUMIDITYSENSOR_H

class HumiditySensor {
public:
    virtual ~HumiditySensor() = default;

    virtual float getRelativeHumidity() const = 0;
};

#endif //WEATHERSTATION_HUMIDITYSENSOR_H
