set(LIB_NAME GUI)
add_library(${LIB_NAME} STATIC)

target_include_directories(${LIB_NAME} PUBLIC
        .
        ui/
)

target_sources(${LIB_NAME} PRIVATE
        gui_app.cpp
        ui/components/ui_comp_hook.c
        ui/screens/ui_Screen1.c
        ui/ui.c
        ui/ui_helpers.c
)

target_link_libraries(${LIB_NAME} PUBLIC
        ${SDL2_LIBRARIES}
        lvgl::lvgl
        lv_drivers
)
