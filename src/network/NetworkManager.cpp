#include "NetworkManager.h"

#include <esp_event.h>
#include <nvs_flash.h>

#ifndef APP_WIFI_SSID
#define APP_WIFI_SSID ""
#endif

#ifndef APP_WIFI_PASSWORD
#define APP_WIFI_PASSWORD ""
#endif

inline static auto configureWifi() {
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    return expressif::wifi::WiFi::getInstance();
}

NetworkManager::NetworkManager()
    : m_wifi(configureWifi()) {}

void NetworkManager::start() {
    m_wifi->start();
}

void NetworkManager::stop() {
    m_wifi->stop();
}

void NetworkManager::run() {
    start();
    ESP_ERROR_CHECK(m_wifi->connect(APP_WIFI_SSID, APP_WIFI_PASSWORD));
}

void NetworkManager::addOnConnectedHandler(const expressif::wifi::WiFi::Handler<> &handler) {
    m_wifi->addOnConnectedHandler(handler);
}

void NetworkManager::addOnDisconnectedHandler(const expressif::wifi::WiFi::Handler<> &handler) {
    m_wifi->addOnDisconnectedHandler(handler);
}
