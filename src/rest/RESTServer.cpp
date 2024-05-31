#include "RESTServer.h"

#include <esp_log.h>

constexpr static auto TAG = "RESTServer";

#define LOG(...) ESP_LOGI(TAG, __VA_ARGS__)

namespace ws {
RESTServer::RESTServer(NetworkManager &network) {
    network.addOnConnectedHandler([this] {
        if (!isValid()) {
            ESP_ERROR_CHECK(m_server.start());
            LOG("Server started");
        }
    });

    network.addOnDisconnectedHandler([this] {
        if (isValid()) {
            assert(m_server.stop());
            LOG("Server stopped");
        }
    });
}

void RESTServer::start() {
    m_server.start();
}

void RESTServer::stop() {
    m_server.stop();
}

bool RESTServer::isValid() const {
    return m_server.isValid();
}

void RESTServer::addComponent(RESTComponentPtr component) {
    component->enableFor(*this);
    m_components.emplace_back(std::move(component));
}
}
