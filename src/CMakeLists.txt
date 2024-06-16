add_executable(${APP_TARGET} # Only add platform independent sources
        gui/gui_app.cpp
        gui/ui/screens/ui_Screen1.c
        gui/ui/ui_helpers.c
        gui/ui/ui.h
        gui/ui/ui.c
        main.cpp
        #        main.cpp # TODO - write platform independent main
)

add_subdirectory(gui)
target_link_libraries(${APP_TARGET}
        PRIVATE
        GUI
)
add_subdirectory(drivers/modules)
target_link_libraries(${APP_TARGET}
        PRIVATE
        Drv_Modules
)


if(IS_RASPBERRY_PI)
    add_subdirectory(drivers/modules)
    target_link_libraries(${APP_TARGET}
            PRIVATE
            Drv_Modules
    )
endif ()