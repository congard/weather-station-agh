#ifndef WEATHERSTATION_RUNNER_H
#define WEATHERSTATION_RUNNER_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <string>

namespace ws {
class Runner {
public:
    struct Config {
        UBaseType_t priority {1};
        configSTACK_DEPTH_TYPE stackDepth {4096};
        std::string name;
    };

public:
    Runner();
    virtual ~Runner() = default;

    bool run(const Config &config);
    bool run();
    bool isRunning() const;

protected:
    virtual void onRun() = 0;

private:
    void destroy();

    static void onRun(void *pvParameters);

private:
    TaskHandle_t m_taskHandle;
};
}

#endif //WEATHERSTATION_RUNNER_H
