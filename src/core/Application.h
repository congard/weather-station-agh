#ifndef WEATHERSTATION_APPLICATION_H
#define WEATHERSTATION_APPLICATION_H

#include "sensor/DHT22Sensor.h"
#include "display/Display.h"
#include "network/NetworkManager.h"
#include "rest/RESTModule.h"
#include "HTModule.h"

class Application : tulz::noncopyable {
public:
    Application();

    DHT22Sensor& getDHT22Sensor();
    NetworkManager& getNetworkManager();

    [[noreturn]] void exec();

    static void setTime(time_t seconds);
    static time_t getTime();

    /**
     * @return The uptime, in ms.
     */
    static uint64_t getUptime();

    static void sleep(int ms);

private:
    HTModule m_htModule;
    Display m_display;
    NetworkManager m_network;
    RESTModule m_restModule;
};

#endif //WEATHERSTATION_APPLICATION_H
