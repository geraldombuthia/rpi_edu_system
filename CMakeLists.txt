cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)
project(Edusat)
set(APP_TARGET Edusat)

if(EXISTS "/opt/vc")
    set(IS_RASPBERRY_PI TRUE)
else()
    set(IS_RASPBERRY_PI FALSE)
endif()

# Find the SDL library
find_package(SDL2 REQUIRED)

# Lvgl
include_directories(.)
set(LV_CONF_BUILD_DISABLE_EXAMPLES 1)
set(LV_CONF_BUILD_DISABLE_DEMOS 1)

add_subdirectory(lvgl)
add_subdirectory(lv_drivers)
add_subdirectory(src)

