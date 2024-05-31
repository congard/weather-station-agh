/**
 * Usage:
 * 1. Include this header to your cpp file
 * 2. Use the LOG_TAG macro to define the tag
 * 3. Log using the LOGI macro
 */

#ifndef WEATHERSTATION_LOG_H
#define WEATHERSTATION_LOG_H

#include <esp_log.h>

#define LOGI(...) ESP_LOGI(TAG, __VA_ARGS__)

#define LOG_TAG(name) constexpr static auto TAG = name

#endif //WEATHERSTATION_LOG_H
