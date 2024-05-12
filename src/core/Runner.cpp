#include "Runner.h"

#define TAG "Runner"

Runner::Runner()
    : m_taskHandle() {}

bool Runner::run(const Config &config) {
    auto ret = xTaskCreate(
        onRun,
        config.name.c_str(),
        config.stackDepth,
        this,
        config.priority,
        &m_taskHandle
    );

    return ret == pdPASS;
}

// Fixes "Default member initializer needed within definition
// of enclosing class 'Runner' outside of member functions"
bool Runner::run() {
    return run({});
}

bool Runner::isRunning() const {
    return m_taskHandle != nullptr;
}

void Runner::destroy() {
    if (isRunning()) {
        auto handle = m_taskHandle;
        m_taskHandle = nullptr;
        vTaskDelete(handle);
    }
}

void Runner::onRun(void *pvParameters) {
    auto instance = static_cast<Runner*>(pvParameters);
    instance->onRun();
    instance->destroy();
}
