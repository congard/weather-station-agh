#include "HTRecorderComponent.h"
#include "rest/RESTServer.h"
#include "recorder/HTRecorder.h"
#include "core/log.h"
#include "core/Application.h"

LOG_TAG("HTRecorderComponent");

namespace ws {
namespace Key {
constexpr static auto MaxRecordCount = "maxRecordCount";
constexpr static auto Period = "period";
}

HTRecorderComponent::HTRecorderComponent(HTRecorder &recorder)
    : m_recorder(recorder) {}

void HTRecorderComponent::enableFor(RESTServer &server) {
    auto &httpServer = server.getHTTPServer();
    httpServer.addEndpoint(HTTPMethod::Get, "/api/recorders/ht/records", endpointHandler(getRecords));
    httpServer.addEndpoint(HTTPMethod::Get, "/api/recorders/ht", endpointHandler(get));
    httpServer.addEndpoint(HTTPMethod::Post, "/api/recorders/ht", endpointHandler(post));
}

void HTRecorderComponent::get(RESTComponent::Request &req) const {
    JsonDocument json;
    json[Key::MaxRecordCount] = m_recorder.getMaxRecordCount();
    json[Key::Period] = m_recorder.getPeriod();
    writeJson(req, json);
}

void HTRecorderComponent::post(RESTComponent::Request &req) {
    readJson(req, [this, &req](const JsonDocument &json) {
        auto maxRecordCount = json[Key::MaxRecordCount];
        auto period = json[Key::Period];

        if (!isValidType<int>(maxRecordCount)) {
            writeError(req, "maxRecordCount must be of type int");
        } else if (!isValidType<int>(period)) {
            writeError(req, "period must be of type int");
        } else {
            // all types are valid
            JsonDocument resp;

            if (maxRecordCount.is<int>()) {
                m_recorder.setMaxRecordCount(maxRecordCount.as<int>());
                setAndLog(resp, Key::MaxRecordCount, m_recorder.getMaxRecordCount());
            }

            if (period.is<int>()) {
                m_recorder.setPeriod(period.as<int>());
                setAndLog(resp, Key::Period, m_recorder.getPeriod());
            }

            writeJson(req, resp);
        }
    });
}

static bool convertToJson(const HTRecord &src, JsonVariant dst) {
    JsonDocument json;
    json["humidity"] = src.getHumidity();
    json["temperature"] = src.getTemperature();

    // timestamp since epoch (01.01.1970) in seconds
    auto timestampSinceEpoch = (Application::getTime() * 1000 - Application::getUptime() + src.getTimestamp()) / 1000;
    json["timestamp"] = timestampSinceEpoch;

    return dst.set(json);
}

void HTRecorderComponent::getRecords(Request &req) const {
    auto params = req.getQueryParams("from", "to", "last");

    struct {
        std::optional<size_t> from;
        std::optional<size_t> to;
        std::optional<size_t> last;
    } pVal; // param values

    auto tryParseOrError = [&](const std::string &key, std::optional<size_t> &result) {
        auto &str = params[key];

        // ok - value will be left unchanged
        if (str.empty())
            return true;

        // if param is specified, try to parse its value
        char* end;
        auto i = std::strtol(str.c_str(), &end, 10);

        if (end - str.c_str() == str.size()) {
            // ok, str was fully read
            result = i;
            return true;
        }

        writeError(req, key + ": invalid value: expected integer");

        return false;
    };

    if (!tryParseOrError("from", pVal.from))
        return;

    if (!tryParseOrError("to", pVal.to))
        return;

    if (!tryParseOrError("last", pVal.last))
        return;

    if ((pVal.from.has_value() || pVal.to.has_value()) && pVal.last.has_value()) {
        writeError(req, "parameter 'last' cannot be used with 'from' or 'to'");
        return;
    }

    auto from = pVal.from.value_or(0);
    auto to = pVal.to.value_or(-1); // if empty, will be equal to size_t max value

    if (from > to) {
        writeError(req, "from > to");
        return;
    }

    JsonDocument json;
    json["records"] = JsonArray {};

    m_recorder.readRecords([&](const HTRecorder::RecordBuffer &records) {
        auto recordCount = records.size();

        if (!pVal.last.has_value()) {
            from = std::min(from, recordCount);
            to = std::min(to, recordCount);
        } else {
            from = std::max(static_cast<ssize_t>(recordCount) - static_cast<ssize_t>(*pVal.last), 0);
            to = recordCount;
        }

        for (size_t i = from; i < to; ++i) {
            json["records"].add(records[i]);
        }
    });

    // note: the json is being sent in 512-byte chunks
    writeJson(req, json, 512);
}
}
