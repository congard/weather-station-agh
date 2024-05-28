#ifndef WEATHERSTATION_NETWORKMANAGER_H
#define WEATHERSTATION_NETWORKMANAGER_H

#include <expressif/wifi/WiFi.h>
#include <tulz/util/noncopyable.h>

class NetworkManager : tulz::noncopyable {
    using Wifi = expressif::wifi::WiFi;

public:
    NetworkManager();

    void start();
    void stop();

    void run();

    void addOnConnectedHandler(const Wifi::Handler<> &handler);
    void addOnDisconnectedHandler(const Wifi::Handler<> &handler);

private:
    Wifi *m_wifi;
};

#endif //WEATHERSTATION_NETWORKMANAGER_H
