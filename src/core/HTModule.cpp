#include "HTModule.h"

namespace ws {
HTModule::HTModule()
    : m_recorder(m_sensor) {}

void HTModule::run() {
    m_sensor.run();
    m_recorder.run();
}

DHT22Sensor& HTModule::getSensor() {
    return m_sensor;
}

HTRecorder& HTModule::getRecorder() {
    return m_recorder;
}
}
