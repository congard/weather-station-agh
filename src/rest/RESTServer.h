#ifndef WEATHERSTATION_RESTSERVER_H
#define WEATHERSTATION_RESTSERVER_H

#include "RESTComponent.h"
#include "network/NetworkManager.h"

#include <vector>
#include <expressif/http/server/HTTPServer.h>

namespace ws {
class RESTServer {
public:
    explicit RESTServer(NetworkManager &network);

    void start();
    void stop();

    bool isValid() const;

    void addComponent(RESTComponentPtr component);

    template<typename T, typename ...Args>
    void addComponent(Args&&... args) {
        addComponent(std::make_unique<T>(std::forward<Args>(args)...));
    }

    inline auto& getHTTPServer() {
        return m_server;
    }

private:
    expressif::http::server::HTTPServer m_server;
    std::vector<RESTComponentPtr> m_components;
};
}

#endif //WEATHERSTATION_RESTSERVER_H
