cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)
project(Edusat)
set(APP_TARGET Edusat)

# Find the SDL library
find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})
include_directories(.)

set(LV_CONF_BUILD_DISABLE_EXAMPLES 1) 
set(LV_CONF_BUILD_DISABLE_DEMOS 1)

add_subdirectory(lvgl)
add_subdirectory(lv_drivers)
add_subdirectory(src/drivers/modules)

add_executable(${APP_TARGET}
src/gui/gui_app.cpp
src/gui/ui/screens/ui_Screen1.c
src/gui/ui/ui_helpers.c
src/gui/ui/ui.h
src/gui/ui/ui.c
src/main.cpp
)

target_link_libraries(${APP_TARGET}
PRIVATE
lvgl::lvgl 
lv_drivers
${SDL2_LIBRARIES}
drv_modules
)