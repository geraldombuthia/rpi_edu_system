#include <stdio.h>
#include <stdlib.h>
#include <gps.h>


enum gps_state {
    GPS_STATE_INIT,
    GPS_STATE_READ,
    GPS_STATE_ERROR
} gps_state_t;
/**
 * @brief GPS class
 *
 */
class GPS {
public:
    /**
     * @brief Construct a new GPS object
     */
    GPS();
    /**
     *@brief Destroy the GPS object
     */
    ~GPS();
    /**
     * @brief Initialize the GPS
     */
    gps_state_t init();
    /**
     * @brief Get the location
     * @param data Contains the location data
     * @return loc_t
     */
    gps_state_t gps_location(loc_t *data);


}
