#include "RESTModule.h"
#include "core/Application.h"

#include "HelloWorldComponent.h"

RESTModule::RESTModule(Application &application)
    : m_server(application.getNetworkManager())
{
    m_server.addComponent<HelloWorldComponent>();
}

void RESTModule::run() {
    m_server.start();
}
