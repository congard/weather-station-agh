#include <freertos/FreeRTOS.h>

#include "Application.h"

Application::Application()
    : m_display(*this),
      m_restModule(*this) {}

DHT22Sensor& Application::getDHT22Sensor() {
    return m_htModule.getSensor();
}

NetworkManager& Application::getNetworkManager() {
    return m_network;
}

void Application::exec() {
    m_restModule.run();

    // the order is important: network must be
    // started after the RESTModule because of
    // callbacks
    m_network.run();

    m_htModule.run();
    m_display.run();

    constexpr auto sleepSeconds = 10;
    uint64_t timeSeconds = 0;

    while (true) {
        // Based on
        // https://github.com/espressif/arduino-esp32/blob/6bfcd6d9a9a7ecd07d656a7a88673c93e7d4d537/cores/esp32/Esp.cpp#L132
        // Note esp_get_free_heap_size is equivalent to xPortGetFreeHeapSize and is equivalent to
        // heap_caps_get_free_size(MALLOC_CAP_DEFAULT)
        auto freeHeap = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
        auto totalHeap = heap_caps_get_total_size(MALLOC_CAP_INTERNAL);
        auto usedHeap = totalHeap - freeHeap;
        auto usedPercentage = static_cast<float>(usedHeap) / static_cast<float>(totalHeap) * 100.0f;

        printf("uptime: %llum %llus, heap usage: %i/%i (%.2f %%)\n",
               timeSeconds / 60, timeSeconds % 60,
               usedHeap, totalHeap, usedPercentage);

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
