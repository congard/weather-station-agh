cmake_minimum_required(VERSION 3.16.0)
set(CMAKE_CXX_STANDARD 20)

# workaround for https://github.com/espressif/esp-idf/issues/3920
set(PROJECT_VER 1)

if (DEFINED ENV{EXPRESSIF_PATH})
    message(STATUS "External Expressif library will be used")
    set(EXPRESSIF_PATH "$ENV{EXPRESSIF_PATH}")
else()
    set(EXPRESSIF_PATH "components/expressif")
endif()

message(STATUS "EXPRESSIF_PATH: ${EXPRESSIF_PATH}")

# add this line before `include`
list(APPEND EXTRA_COMPONENT_DIRS
        "${EXPRESSIF_PATH}/components"
        "components/esp-idf-ssd1306/components"
        "components/am2302_rmt"
        "components/tulz-observer")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(WeatherStation LANGUAGES CXX)