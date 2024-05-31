#include "RESTModule.h"
#include "core/Application.h"

#include "HelloWorldComponent.h"
#include "core/ApplicationComponent.h"
#include "display/DisplayComponent.h"
#include "recorder/HTRecorderComponent.h"
#include "sensor/DHT22SensorComponent.h"
#include "www/WWWComponent.h"

RESTModule::RESTModule(Application &application)
    : m_server(application.getNetworkManager())
{
    m_server.addComponent<HelloWorldComponent>();
    m_server.addComponent<ApplicationComponent>();
    m_server.addComponent<DisplayComponent>(application.getDisplay());
    m_server.addComponent<HTRecorderComponent>(application.getHTModule().getRecorder());
    m_server.addComponent<DHT22SensorComponent>(application.getHTModule().getSensor());
    m_server.addComponent<WWWComponent>();
}

void RESTModule::run() {
    m_server.start();
}
