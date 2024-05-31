#include "DisplayComponent.h"
#include "rest/RESTServer.h"
#include "display/Display.h"
#include "display/renderer/DefaultDisplayRenderer.h"
#include "core/log.h"

LOG_TAG("DisplayComponent");

namespace Key {
constexpr static auto RefreshPeriod = "refreshPeriod";
constexpr static auto Renderer = "renderer";
}

DisplayComponent::DisplayComponent(Display &display)
    : m_display(display) {}

void DisplayComponent::enableFor(RESTServer &server) {
    auto &httpServer = server.getHTTPServer();
    httpServer.addEndpoint(HTTPMethod::Get, "/api/display/renderers", getRenderers);
    httpServer.addEndpoint(HTTPMethod::Get, "/api/display", endpointHandler(get));
    httpServer.addEndpoint(HTTPMethod::Post, "/api/display", endpointHandler(post));
}

void DisplayComponent::get(Request &req) {
    JsonDocument json;
    json[Key::RefreshPeriod] = m_display.getRefreshPeriod();
    json[Key::Renderer] = getRendererName();
    writeJson(req, json);
}

void DisplayComponent::post(Request &req) {
    readJson(req, [&req, this](const JsonDocument &json) {
        auto refreshPeriod = json[Key::RefreshPeriod];
        auto renderer = json[Key::Renderer];

        if (!isValidType<int>(refreshPeriod)) {
            writeError(req, "refreshPeriod must be of type int");
        } else if (!isValidType<std::string>(renderer)) {
            writeError(req, "renderer must be of type string");
        } else {
            // all types are valid
            JsonDocument resp;

            if (refreshPeriod.is<int>()) {
                m_display.setRefreshPeriod(refreshPeriod.as<int>());
                setAndLog(resp, Key::RefreshPeriod, m_display.getRefreshPeriod());
            }

            if (renderer.is<std::string>()) {
                setRenderer(renderer.as<std::string>());
                setAndLog(resp, Key::Renderer, getRendererName());
            }

            writeJson(req, resp);
        }
    });
}

void DisplayComponent::setRenderer(std::string_view name) {
    if (name == "default") {
        m_display.setRenderer(std::make_unique<DefaultDisplayRenderer>(m_display));
    } else if (name == "big") {
        // TODO
    }
}

std::string DisplayComponent::getRendererName() const {
    if (auto renderer = m_display.getRenderer(); dynamic_cast<DefaultDisplayRenderer*>(renderer) != nullptr)
        return "default";
    // TODO: big
    return {};
}

void DisplayComponent::getRenderers(Request &req) {
    JsonDocument json;
    auto renderers = json["renderers"];
    renderers.add("default");
    renderers.add("big");
    writeJson(req, json);
}
