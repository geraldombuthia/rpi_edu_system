cmake_minimum_required(VERSION 3.25)
project(Edusat LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")

include(FetchContent)

set(APP_TARGET Edusat CACHE INTERNAL "")

get_filename_component(APP_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

find_package(SDL2 REQUIRED)

set(APP_SOURCE_DIR ${APP_CMAKE_DIR})

message(APP_SOURCE_DIR: ${APP_SOURCE_DIR})

set(APP_SOURCE_DIR ${APP_CMAKE_DIR}/src)

include_directories(
    ${APP_SOURCE_DIR}
    ${APP_SOURCE_DIR}/include
    ${APP_SOURCE_DIR}/include/lvgl
    src/drivers/modules/BME280
    src/drivers/modules/DHT11
    src/drivers/modules/HMC5883L
    src/drivers/modules/MCP3008
    src/drivers/modules/MPU6050
    ${CMAKE_SOURCE_DIR}/lvgl
)

set(SOURCES
    src/drivers/modules/BME280/bme280.cpp
    src/drivers/modules/DHT11/dht11.cpp
    src/drivers/modules/HMC5883L/hmc5883l.cpp
    src/drivers/modules/MCP3008/mcp3008.cpp
    src/drivers/modules/MPU6050/mpu6050.cpp
    src/main.cpp
)
# target_include_directories(my_executable PRIVATE
#     ${SDL_INCLUDE_DIRS}
#     ${APP_SOURCE_DIR}
#     ${CMAKE_SOURCE_DIR}/include
#     ${APP_SOURCE_DIR}/gui/ui
#     src/drivers/modules/BME280
#     src/drivers/modules/DHT11
#     src/drivers/modules/HMC5883L
#     src/drivers/modules/MCP3008
#     src/drivers/modules/MPU6050
#     ${CMAKE_SOURCE_DIR}/lvgl
# )

FetchContent_Declare(lv_drivers
    GIT_REPOSITORY https://github.com/lvgl/lv_drivers)
FetchContent_MakeAvailable(lv_drivers)

set(APP_LIBRARIES
    lvgl::lvgl
    lvgl::drivers
)

add_subdirectory(${CMAKE_SOURCE_DIR}/lvgl)

add_executable(${APP_TARGET} ${SOURCES})

target_link_libraries(${APP_TARGET} ${APP_LIBRARIES} ${SDL2_LIBRARIES} lvgl lv_drivers wiringPi lgpio i2c)

message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS} SOURCE: ${APP_SOURCE_DIR} CMAKE Source: ${CMAKE_SOURCE_DIR} LVGL: ${CMAKE_SOURCE_DIR}/lvgl LV_DRIVERS: ${lv_drivers}")
