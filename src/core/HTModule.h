#ifndef WEATHERSTATION_HTMODULE_H
#define WEATHERSTATION_HTMODULE_H

#include "sensor/DHT22Sensor.h"
#include "recorder/HTRecorder.h"

namespace ws {
class HTModule {
public:
    HTModule();

    void run();

    DHT22Sensor& getSensor();
    HTRecorder& getRecorder();

private:
    DHT22Sensor m_sensor;
    HTRecorder m_recorder;
};
}

#endif //WEATHERSTATION_HTMODULE_H
