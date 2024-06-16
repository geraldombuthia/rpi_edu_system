#include "gps_data.h"


GPS::GPS() {
    
};

GPS::~GPS() {
    
};

gps_state_t GPS::init() {
    gps_init();

    return GPS_STATE_INIT;
}

gps_state_t GPS::location(loc_t *data) {
    gps_location(data);

    return GPS_STATE_READ;
}
