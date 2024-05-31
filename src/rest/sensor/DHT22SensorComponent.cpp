#include "DHT22SensorComponent.h"
#include "rest/RESTServer.h"
#include "sensor/DHT22Sensor.h"
#include "core/log.h"

#include <expressif/http/server/HTTPServer.h>
#include <ArduinoJson.h>

LOG_TAG("DHT22SensorComponent");

namespace ws {
DHT22SensorComponent::DHT22SensorComponent(DHT22Sensor &sensor)
    : m_sensor(sensor) {}

void DHT22SensorComponent::enableFor(RESTServer &server) {
    auto &httpServer = server.getHTTPServer();
    httpServer.addEndpoint(HTTPMethod::Get, "/api/sensors/dht22", endpointHandler(get));
    httpServer.addEndpoint(HTTPMethod::Post, "/api/sensors/dht22", endpointHandler(post));
}

void DHT22SensorComponent::get(Request &req) const {
    JsonDocument json;
    json["humidity"] = m_sensor.getRelativeHumidity();
    json["temperature"] = m_sensor.getCelsius();
    json["updateFrequency"] = m_sensor.getUpdateFrequency();
    writeJson(req, json);
}

void DHT22SensorComponent::post(Request &req) {
    readJson(req, [this, &req](const JsonDocument &json) {
        auto updateFrequency = json["updateFrequency"];

        if (!isValidType<int>(updateFrequency)) {
            writeError(req, "Unsupported type");
        } else if (updateFrequency.is<int>()) {
            JsonDocument resp;
            m_sensor.setUpdateFrequency(updateFrequency.as<int>());
            setAndLog(resp, "updateFrequency", m_sensor.getUpdateFrequency());
            writeJson(req, resp);
        } else {
            // updateFrequency is not defined at all
            writeError(req, "Only 1 parameter is acceptable: updateFrequency");
        }
    });
}
}
