#include "ApplicationComponent.h"
#include "rest/RESTServer.h"
#include "core/Application.h"
#include "core/log.h"

LOG_TAG("ApplicationComponent");

namespace ws {
namespace Key {
constexpr static auto Time = "time";
constexpr static auto Uptime = "time";
}

ApplicationComponent::ApplicationComponent() = default;

void ApplicationComponent::enableFor(RESTServer &server) {
    auto &httpServer = server.getHTTPServer();
    httpServer.addEndpoint(HTTPMethod::Get, "/api/uptime", getUptime);
    httpServer.addEndpoint(HTTPMethod::Get, "/api/time", getTime);
    httpServer.addEndpoint(HTTPMethod::Post, "/api/time", setTime);
}

void ApplicationComponent::getUptime(Request &req) {
    JsonDocument json;
    json[Key::Uptime] = Application::getUptime();
    writeJson(req, json);
}

void ApplicationComponent::getTime(Request &req) {
    JsonDocument json;
    json[Key::Time] = Application::getTime();
    writeJson(req, json);
}

void ApplicationComponent::setTime(Request &req) {
    readJson(req, [&](const JsonDocument &json) {
        if (json.size() != 1) {
            writeError(req, "Only 1 parameter is acceptable: time");
        } else if (auto timeObj = json[Key::Time]; !timeObj.is<time_t>()) {
            writeError(req, "Expected parameter 'time' of type time_t");
        } else if (auto time = timeObj.as<time_t>(); time < 0) {
            // time_t can be signed: can be defined as __int_least64_t
            writeError(req, "time cannot be negative");
        } else {
            JsonDocument resp;
            Application::setTime(time);
            setAndLog(resp, Key::Time, Application::getTime());
            writeJson(req, resp);
        }
    });
}
}
