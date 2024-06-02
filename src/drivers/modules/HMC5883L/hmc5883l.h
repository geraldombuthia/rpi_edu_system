/**
 * 3-Axis Digital Compass IC HMC5883LL header only library for Raspberry Pi.
 *
 * Author: Martin Albrecht
 *
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 Martin Albrecht <martin.albrecht@javacoffee.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#ifndef __HMC5883L_H__
#define __HMC5883L_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

/* I2C address */
#define HMC5883L_I2C_ADDRESS            0x1E

/* Chip ID */
#define HMC5883L_ID                     (0b11010100)

/* Internal name */
#define HMC5883L_SENSOR_NAME             "HMC5883L"

/* Registers */
#define HMC5883L_REGISTER_CRA            0x00
#define HMC5883L_REGISTER_CRB            0x01
#define HMC5883L_REGISTER_MR             0x02
#define HMC5883L_REGISTER_OUT_X_H_M      0x03
#define HMC5883L_REGISTER_OUT_X_L_M      0x04
#define HMC5883L_REGISTER_OUT_Z_H_M      0x05
#define HMC5883L_REGISTER_OUT_Z_L_M      0x06
#define HMC5883L_REGISTER_OUT_Y_H_M      0x07
#define HMC5883L_REGISTER_OUT_Y_L_M      0x08
#define HMC5883L_REGISTER_STATUS         0x09
#define HMC5883L_REGISTER_IRA            0x0A
#define HMC5883L_REGISTER_IRB            0x0B
#define HMC5883L_REGISTER_IRC            0x0C
#define HMC5883L_REGISTER_TEMP_OUT_H_M   0x31
#define HMC5883L_REGISTER_TEMP_OUT_L_M   0x32

/* Gain definitions */
#define HMC5883L_GAIN_1_3                0x20
#define HMC5883L_GAIN_1_9                0x40
#define HMC5883L_GAIN_2_5                0x60
#define HMC5883L_GAIN_4_0                0x80
#define HMC5883L_GAIN_4_7                0xA0
#define HMC5883L_GAIN_5_6                0xC0
#define HMC5883L_GAIN_8_1                0xE0

/* Errors */
#define HMC5883L_ERR_UNKNOWN             0x01
#define HMC5883L_ERR_SETUP               0x02
#define HMC5883L_ERR_SELFTEST            0x03
#define HMC5883L_ERR_SELFTEST_RUNS       0x04

/* Status codes */
#define HMC5883L_STATUS_READY            0x01
#define HMC5883L_STATUS_LOCK             0x02

/* Constants */
#define HMC5883L_CONST_GAUSS2MTESLA      100

/* General stuff */
#define HMC5883L_OKAY                    0
#define HMC5883L_ERROR                   -1


/* Predefined values, which change with gain setting  */
static float _hmc5883l_Gauss_LSB_XY = 1100.0F;
static float _hmc5883l_Gauss_LSB_Z  = 980.0F;


/* The HMC5883L object */
typedef struct {
    int _fd,
        _status,
        _min_delay,
        _max_value,
        _min_value;

    unsigned char _gain,
             _error;

    char _name[12];

    float _resolution,
          _declination_angle,
          _scale;

    /* Magnetic field data */
    struct {
        float x, y, z;
    } _magnetic;

    /* Sensor data */
    struct {
        float x, y, z;
        float x_scaled, y_scaled, z_scaled;
        double orientation_deg; /* Degrees */
        float orientation_rad; /* Radiants */
    } _data;
} HMC5883L;


/* Function prototypes */
void hmc5883l_error(HMC5883L *hmc5883l, char code);
void hmc5883l_read(HMC5883L *hmc5883l);
void hmc5883l_set_gain(HMC5883L *hmc5883l, unsigned char gain);
char hmc5883l_self_test(HMC5883L *hmc5883l);
char hmc5883l_init(HMC5883L *hmc5883l);

#endif