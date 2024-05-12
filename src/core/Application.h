#ifndef WEATHERSTATION_APPLICATION_H
#define WEATHERSTATION_APPLICATION_H

#include "sensor/DHT22Sensor.h"
#include "display/Display.h"

class Application {
public:
    Application();

    DHT22Sensor& getDHT22Sensor();

    [[noreturn]] void exec();

    static void setTime(time_t seconds);
    static time_t getTime();

private:
    DHT22Sensor m_dht22Sensor;
    Display m_display;
};

#endif //WEATHERSTATION_APPLICATION_H
