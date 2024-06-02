#include "hmc5883l.h"


/* Set error flag in HMC5883L object */
void hmc5883l_error(HMC5883L *hmc5883l, char code) {
    switch(code) {
    case HMC5883L_ERR_SETUP:
        hmc5883l->_error = HMC5883L_ERR_SETUP;
        break;

    case HMC5883L_ERR_SELFTEST:
        hmc5883l->_error = HMC5883L_ERR_SELFTEST;
        break;

    case HMC5883L_ERR_SELFTEST_RUNS:
        hmc5883l->_error = HMC5883L_ERR_SELFTEST_RUNS;
        break;

    default:
        hmc5883l->_error = HMC5883L_ERR_UNKNOWN;
        break;
    }
}


/* Read status register */
void hmc5883l_status(HMC5883L *hmc5883l) {
    int status = 0;

    status = wiringPiI2CReadReg8(hmc5883l->_fd, HMC5883L_REGISTER_STATUS);

    hmc5883l->_status = 0;
    hmc5883l->_status |= (status & 1); /* Ready flag */
    hmc5883l->_status |= (status & 2); /* Lock flag */
}


/* Read raw data from sensor */
void hmc5883l_read(HMC5883L *hmc5883l) {
    int x0 = 0, x1 = 0,
        y0 = 0, y1 = 0,
        z0 = 0, z1 = 0;

    float heading = 0;

    /* Read the status register */
    hmc5883l_status(hmc5883l);

    if( hmc5883l->_status == HMC5883L_STATUS_READY ) {
        /* Read data registers */
        x0 = wiringPiI2CReadReg8(hmc5883l->_fd, HMC5883L_REGISTER_OUT_X_L_M);
        x1 = wiringPiI2CReadReg8(hmc5883l->_fd, HMC5883L_REGISTER_OUT_X_H_M);
        z0 = wiringPiI2CReadReg8(hmc5883l->_fd, HMC5883L_REGISTER_OUT_Z_L_M);
        z1 = wiringPiI2CReadReg8(hmc5883l->_fd, HMC5883L_REGISTER_OUT_Z_H_M);
        y0 = wiringPiI2CReadReg8(hmc5883l->_fd, HMC5883L_REGISTER_OUT_Y_L_M);
        y1 = wiringPiI2CReadReg8(hmc5883l->_fd, HMC5883L_REGISTER_OUT_Y_H_M);

        /* Combine 8 bit values to a 16 bit value */
        hmc5883l->_data.x = (int16_t)(x0 | ((int16_t)x1 << 8));
        hmc5883l->_data.y = (int16_t)(y0 | ((int16_t)y1 << 8));
        hmc5883l->_data.z = (int16_t)(z0 | ((int16_t)z1 << 8));

        hmc5883l->_data.x_scaled = hmc5883l->_scale * hmc5883l->_data.x;
        hmc5883l->_data.y_scaled = hmc5883l->_scale * hmc5883l->_data.y;
        hmc5883l->_data.z_scaled = hmc5883l->_scale * hmc5883l->_data.z;

        /* Magnetic field calculation */
        hmc5883l->_magnetic.x =
            hmc5883l->_data.x / _hmc5883l_Gauss_LSB_XY * HMC5883L_CONST_GAUSS2MTESLA;

        hmc5883l->_magnetic.y =
            hmc5883l->_data.y / _hmc5883l_Gauss_LSB_XY * HMC5883L_CONST_GAUSS2MTESLA;

        hmc5883l->_magnetic.z =
            hmc5883l->_data.z / _hmc5883l_Gauss_LSB_Z * HMC5883L_CONST_GAUSS2MTESLA;

        /* Calculate heading */
        heading = atan2(hmc5883l->_magnetic.y, hmc5883l->_magnetic.x);

        if( hmc5883l->_declination_angle > 0 ) {
            heading += hmc5883l->_declination_angle;
        }

        /* Normalize value */
        if( heading < 0 ) heading += 2 * M_PI;
        if( heading > 2 * M_PI ) heading -= 2 * M_PI;

        hmc5883l->_data.orientation_rad = heading;
        hmc5883l->_data.orientation_deg = heading * 180 / M_PI;
    }
}


/* Set sensor gain and corresponding scale factor */
void hmc5883l_set_gain(HMC5883L *hmc5883l, unsigned char gain) {
    wiringPiI2CWriteReg8(hmc5883l->_fd, HMC5883L_REGISTER_CRB, gain);

    hmc5883l->_gain = gain;

    switch(gain) {
    /* +/- 1.3 gauss */
    case HMC5883L_GAIN_1_3:
        _hmc5883l_Gauss_LSB_XY = 1090;
        _hmc5883l_Gauss_LSB_Z  = 980;
        hmc5883l->_scale = 0.92;
        break;

    /* +/- 1.9 gauss */
    case HMC5883L_GAIN_1_9:
        _hmc5883l_Gauss_LSB_XY = 820;
        _hmc5883l_Gauss_LSB_Z  = 760;
        hmc5883l->_scale = 1.22;
        break;

    /* +/- 2.5 gauss */
    case HMC5883L_GAIN_2_5:
        _hmc5883l_Gauss_LSB_XY = 660;
        _hmc5883l_Gauss_LSB_Z  = 600;
        hmc5883l->_scale = 1.52;
        break;

    /* +/- 4.0 gauss */
    case HMC5883L_GAIN_4_0:
        _hmc5883l_Gauss_LSB_XY = 440;
        _hmc5883l_Gauss_LSB_Z  = 400;
        hmc5883l->_scale = 2.27;
        break;

    /* +/- 4.7 gauss */
    case HMC5883L_GAIN_4_7:
        _hmc5883l_Gauss_LSB_XY = 390;
        _hmc5883l_Gauss_LSB_Z  = 255;
        hmc5883l->_scale = 2.56;
        break;

    /* +/- 5.6 gauss */
    case HMC5883L_GAIN_5_6:
        _hmc5883l_Gauss_LSB_XY = 330;
        _hmc5883l_Gauss_LSB_Z  = 295;
        hmc5883l->_scale = 3.03;
        break;

    /* +/- 8.1 gauss */
    case HMC5883L_GAIN_8_1:
        _hmc5883l_Gauss_LSB_XY = 230;
        _hmc5883l_Gauss_LSB_Z  = 205;
        hmc5883l->_scale = 4.35;
        break;

    default:
        break;
    }
}


/* Self test */
char hmc5883l_self_test(HMC5883L *hmc5883l) {
    unsigned char passed = 0;
    unsigned int limit_low = 243,
                 limit_high = 575;

    while(passed == 0) {
        /* Set the sensor to self test mode */
        wiringPiI2CWriteReg8(hmc5883l->_fd, HMC5883L_REGISTER_CRA, 0x71);
        /* Set the gain to 5, limits are then 243-575) */
        wiringPiI2CWriteReg8(hmc5883l->_fd, HMC5883L_REGISTER_CRB, 0xA0);
        /* Set continuous-measurement mode */
        wiringPiI2CWriteReg8(hmc5883l->_fd, HMC5883L_REGISTER_MR, 0x00);

        delay(1);

        /* Read self test data */
        hmc5883l_read(hmc5883l);

        /* Check the values */
        if( hmc5883l->_data.x < limit_low ||  hmc5883l->_data.x > limit_high ||
                hmc5883l->_data.y < limit_low ||  hmc5883l->_data.y > limit_high ||
                hmc5883l->_data.z < limit_low ||  hmc5883l->_data.z > limit_high )
        {
            if( hmc5883l->_gain < HMC5883L_GAIN_8_1 ) {
                hmc5883l_set_gain(hmc5883l, (hmc5883l->_gain + 0x20));

                /* Set limits */
                if( hmc5883l->_gain == HMC5883L_GAIN_5_6 ) {
                    printf("Adjusted gain to 6\n");
                    limit_low = 206;
                    limit_high = 487;
                }

                if( hmc5883l->_gain == HMC5883L_GAIN_8_1 ) {
                    printf("Adjusted gain to 7\n");
                    limit_low = 143;
                    limit_high = 339;
                }

                continue;
            }

            hmc5883l_error(hmc5883l, HMC5883L_ERR_SELFTEST);
            return HMC5883L_ERROR;
        }

        /* Exit self test mode, set defaults */
        wiringPiI2CWriteReg8(hmc5883l->_fd, HMC5883L_REGISTER_CRA, 0x70);

        return HMC5883L_OKAY;
    }

    hmc5883l_error(hmc5883l, HMC5883L_ERR_SELFTEST_RUNS);
    return HMC5883L_ERROR;
}


/*
 * Constructor function
 */
char hmc5883l_init(HMC5883L *hmc5883l) {
    /* The I2C interface descriptor */
    hmc5883l->_fd = wiringPiI2CSetup(HMC5883L_I2C_ADDRESS);

    if( hmc5883l->_fd == -1 ) {
        hmc5883l_error(hmc5883l, HMC5883L_ERR_SETUP);
        return HMC5883L_ERROR;
    }

    /* Set sensor data */
    hmc5883l->_error             = 0;
    hmc5883l->_status            = 0;
    hmc5883l->_gain              = 0;
    hmc5883l->_min_delay         = 0;
    hmc5883l->_max_value         = 800;  /* 8 gauss == 800 microTesla */
    hmc5883l->_min_value         = -800; /* -8 gauss == -800 microTesla */
    hmc5883l->_resolution        = 0.2;  /* 2 milligauss == 0.2 microTesla */
    hmc5883l->_declination_angle = 0;

    hmc5883l->_data.x                = 0;
    hmc5883l->_data.y                = 0;
    hmc5883l->_data.z                = 0;
    hmc5883l->_data.orientation_deg  = 0;
    hmc5883l->_data.orientation_rad  = 0;

    hmc5883l->_magnetic.x        = 0;
    hmc5883l->_magnetic.y        = 0;
    hmc5883l->_magnetic.z        = 0;

    sprintf(hmc5883l->_name, HMC5883L_SENSOR_NAME);

    /* Set default configuration */
    wiringPiI2CWriteReg8(hmc5883l->_fd, HMC5883L_REGISTER_CRA, 0x70);

    delay(1);

    /* Set the gain to a known level */
    hmc5883l_set_gain(hmc5883l, HMC5883L_GAIN_1_3);

    /* Enable the magnetometer */
    wiringPiI2CWriteReg8(hmc5883l->_fd, HMC5883L_REGISTER_MR, 0x00);

    return HMC5883L_OKAY;
}