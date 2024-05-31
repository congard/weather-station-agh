#ifndef WEATHERSTATION_RESTCOMPONENT_H
#define WEATHERSTATION_RESTCOMPONENT_H

#include <memory>
#include <sstream>
#include <tulz/util/noncopyable.h>

#include <expressif/http/server/HTTPServer.h>
#include <ArduinoJson.h>

class Application;
class RESTServer;

class RESTComponent : tulz::noncopyable {
public:
    virtual ~RESTComponent() = default;

    virtual void enableFor(RESTServer &server) = 0;

protected:
    using Request = expressif::http::server::Request;
    using HTTPMethod = expressif::http::server::HTTPMethod;

    using ReadCallback = std::function<void(const JsonDocument&)>;

    static void writeJson(Request &req, const JsonDocument &json, size_t chunkSize = 0);
    static void writeError(Request &req, std::string_view message, size_t chunkSize = 0);
    static void readJson(Request &req, const ReadCallback &readCallback);

    /**
     * @tparam T The type.
     * @param v The input data.
     * @return `true` if the key is not specified or,
     * if specified, it must be of type `T`.
     */
    template<typename T>
    static bool isValidType(const JsonVariantConst &v) {
        return v.isUnbound() || v.is<T>();
    }

    /**
     * Associates the value with the key and logs
     * the corresponding message.
     * @tparam T The type.
     * @param json The json object to append to.
     * @param key The key.
     * @param value The value.
     */
    template<typename T>
    static void setAndLog(JsonDocument &json, std::string_view key, T &&value) {
        json[key] = value;

        std::ostringstream stream;
        stream << key << " was set to " << value;

        log(stream.view());
    }

private:
    static void log(std::string_view message);
};

using RESTComponentPtr = std::unique_ptr<RESTComponent>;

#define endpointHandler(handler) [this](Request &req) { handler(req); }

#endif //WEATHERSTATION_RESTCOMPONENT_H
