#include "WWWComponent.h"
#include "rest/RESTServer.h"
#include "partition/www/WWWPartition.h"
#include "core/log.h"

#include "partition/PartitionManager.h"

#include <fstream>

LOG_TAG("WWWComponent");

WWWComponent::WWWComponent() = default;

void WWWComponent::enableFor(RESTServer &server) {
    server.getHTTPServer().addEndpoint(HTTPMethod::Get, "/{path}*", get);
}

static auto getTypeByExt(std::string_view ext) {
    if (ext == "html")
        return "text/html";
    else if (ext == "css")
        return "text/css";
    else if (ext == "js")
        return "text/javascript";
    else if (ext == "png")
        return "image/png";
    else if (ext == "ico")
        return "image/x-icon";
    return "";
}

void WWWComponent::get(Request &req) {
    using namespace expressif::http::server;

    auto path = req.getPathVar("path");

    if (path.empty())
        path = "index.html";

    if (std::ifstream file(ws::Partition::absolute(ws::WWWPartition::MountPoint, path)); file.is_open()) {
        auto ext = std::string_view {path}.substr(path.find_last_of('.') + 1);
        auto type = getTypeByExt(ext);

        req.response().setType(type);

        char buff[512]; // TODO: increase? Test performance.

        req.response().writeChunks([&]() {
            if (file) {
                auto n = file.readsome(buff, sizeof(buff));
                return ConstBuffer(reinterpret_cast<byte_t*>(buff), n);
            } else {
                return ConstBuffer {};
            }
        });
    } else {
        req.response().error404();
    }
}
