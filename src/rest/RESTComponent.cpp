#include "RESTComponent.h"
#include "core/log.h"

LOG_TAG("RESTComponent");

using namespace expressif::http::server;

namespace ws {
void RESTComponent::writeJson(Request &req, const JsonDocument &json, size_t chunkSize) {
    std::string jsonStr;
    serializeJson(json, jsonStr);

    auto resp = req.response();
    resp.setType("application/json");
    resp.write(jsonStr, chunkSize);

    LOGI("Response: %s", jsonStr.c_str());
}

void RESTComponent::writeError(Request &req, std::string_view message, size_t chunkSize) {
    JsonDocument json;
    json["error"]["message"] = message;
    writeJson(req, json, chunkSize);
}

void RESTComponent::readJson(Request &req, const ReadCallback &readCallback) {
    if (auto opt = req.readAll(); opt.has_value()) {
        auto &data = opt.value();

        JsonDocument json;

        if (auto result = deserializeJson(json, data); result.code() == DeserializationError::Ok) {
            readCallback(json);
        } else {
            std::string message = "JSON Deserialization error: ";
            message += result.c_str();
            message += ", code: ";
            message += std::to_string(result.code());
            writeError(req, message);
        }
    } else {
        writeError(req, "Read error");
    }
}

void RESTComponent::log(std::string_view message) {
    LOGI("%s", message.data());
}
}
