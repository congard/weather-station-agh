#include "HelloWorldComponent.h"
#include "RESTServer.h"

using namespace expressif::http::server;

void ws::HelloWorldComponent::enableFor(RESTServer &server) {
    server.getHTTPServer().addEndpoint(HTTPMethod::Get, "/api/hello", [](Request &req) {
        req.response().write("Hello world!");
    });
}
