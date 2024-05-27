#include <freertos/FreeRTOS.h>

#include "Application.h"

Application::Application()
    : m_display(*this) {}

DHT22Sensor& Application::getDHT22Sensor() {
    return m_htModule.getSensor();
}

void Application::exec() {
    m_htModule.run();
    m_display.run();

    constexpr auto sleepSeconds = 10;
    uint64_t timeSeconds = 0;

    while (true) {
        printf("uptime: %llum %llus\n", timeSeconds / 60, timeSeconds % 60);
        timeSeconds += sleepSeconds;
        sleep(sleepSeconds * 1000);
    }
}

void Application::setTime(time_t seconds) {
    timeval now {.tv_sec = seconds};
    settimeofday(&now, nullptr);
}

time_t Application::getTime() {
    time_t result;
    time(&result);
    return result;
}

uint64_t Application::getUptime() {
    return pdTICKS_TO_MS(xTaskGetTickCount());
}

void Application::sleep(int ms) {
    vTaskDelay(pdMS_TO_TICKS(ms));
}
