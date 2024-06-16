#ifndef GPS_DATA_H
#define GPS_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <gps.h>


typedef enum gps_state {
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
    gps_state_t location(loc_t *data);


};
#endif // GPS_DATA_H