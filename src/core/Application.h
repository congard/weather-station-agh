#ifndef WEATHERSTATION_APPLICATION_H
#define WEATHERSTATION_APPLICATION_H

#include "partition/PartitionManager.h"
#include "sensor/DHT22Sensor.h"
#include "display/Display.h"
#include "network/NetworkManager.h"
#include "rest/RESTModule.h"
#include "HTModule.h"

class Application : tulz::noncopyable {
public:
    Application();

    HTModule& getHTModule();
    NetworkManager& getNetworkManager();

    Display& getDisplay();

    [[noreturn]] void exec();

    static void setTime(time_t seconds);

    /**
     * @return The time since epoch, in seconds
     */
    static time_t getTime();

    /**
     * @return The uptime, in ms.
     */
    static uint64_t getUptime();

    static void sleep(int ms);

private:
    ws::PartitionManager m_partitionManager;
    HTModule m_htModule;
    Display m_display;
    NetworkManager m_network;
    RESTModule m_restModule;
};

#endif //WEATHERSTATION_APPLICATION_H
