#ifndef GUI_H
#define GUI_H

#include "lv_drv_conf.h"
#include "lv_conf.h"
#include "lvgl.h"
#include <SDL2/SDL.h>

/**
 * @brief This is the GUI class
 * Performs the display of the data received by the application
*/

class GUI {
    /**
      * Constructor
     */
    GUI() = default;
    /**
     * Destructor
    */
    ~GUI() = default;
public:
    /**
     * @brief Initialize the GUI
     * @return 0 if successful, -1 otherwise
    */
    int init();
    /**
     * @brief Get the GUI interface instance
     * @return the GUI interface instance
     *
    */
    static GUI* get_instance();
    /**
     * @brief Update the GUI
     * @return 0 if successful, -1 otherwise
    */

    int update();

private:

};

#endif // GUI_H