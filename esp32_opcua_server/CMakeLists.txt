cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp32_idfArduino_server)
set(common_req log esp_rom esp_common esp_hw_support newlib)
