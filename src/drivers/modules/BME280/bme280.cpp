#include "bme280.h"
#include <cstddef>
#include <unistd.h>
#include <fcntl.h>

int32_t BME280::compensate_temp(int32_t adc_T) {
    int32_t var1, var2, T;
    var1 = ((((adc_T >> 3) - ((int32_t) dig_T1 << 1))) * ((int32_t) dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t) dig_T1)) * ((adc_T >> 4) - ((int32_t) dig_T1))) >> 12) * ((int32_t) dig_T3))
           >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

uint32_t BME280::compensate_pressure(int32_t adc_P) {
    int64_t var1, var2, p;
    var1 = ((int64_t) t_fine) - 128000;
    var2 = var1 * var1 * (int64_t) dig_P6;
    var2 = var2 + ((var1 * (int64_t) dig_P5) << 17);
    var2 = var2 + (((int64_t) dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t) dig_P3) >> 8) + ((var1 * (int64_t) dig_P2) << 12);
    var1 = (((((int64_t) 1) << 47) + var1)) * ((int64_t) dig_P1) >> 33;
    if (var1 == 0) {
        return 0; // Avoid exception caused by division by zero
    }
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t) dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t) dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t) dig_P7) << 4);
    return (uint32_t)p;
}

uint32_t BME280::compensate_humidity(int32_t adc_H) {
    int32_t v_x1_u32r;
    v_x1_u32r = (t_fine - ((int32_t) 76800));
    v_x1_u32r = (((((adc_H << 14) - (((int32_t) dig_H4) << 20) - (((int32_t) dig_H5) * v_x1_u32r)) +
                   ((int32_t) 16384)) >> 15) * (((((((v_x1_u32r * ((int32_t) dig_H6)) >> 10) * (((v_x1_u32r *
                           ((int32_t) dig_H3))
                           >> 11) + ((int32_t) 32768))) >> 10) + ((int32_t) 2097152)) *
                           ((int32_t) dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t) dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
    return (uint32_t)(v_x1_u32r >> 12);
}

void BME280::bme280_read_raw(int32_t *humidity, int32_t *pressure, int32_t *temperature) {
    uint8_t readBuffer[8];
    read_registers(0xF7, readBuffer, 8);
    *pressure = ((uint32_t) readBuffer[0] << 12) | ((uint32_t) readBuffer[1] << 4) | (readBuffer[2] >> 4);
    *temperature = ((uint32_t) readBuffer[3] << 12) | ((uint32_t) readBuffer[4] << 4) | (readBuffer[5] >> 4);
    *humidity = (uint32_t) readBuffer[6] << 8 | readBuffer[7];
}

void BME280::write_register(uint8_t reg, uint8_t data) {
    uint8_t buf[2] = {reg, data};
    if (write(i2c_fd, buf, 2) != 2) {
        perror("Failed to write to the i2c bus");
        // //exit(1);
    }
    usleep(10000); // Delay required after write operation
}

void BME280::read_registers(uint8_t reg, uint8_t *buf, uint16_t len) {
    if (write(i2c_fd, &reg, 1) != 1) {
        perror("Failed to write to the i2c bus");
        //exit(1);
    }
    if (read(i2c_fd, buf, len) != len) {
        perror("Failed to read from the i2c bus");
        //exit(1);
    }
    usleep(10000); // Delay required after read operation
}

void BME280::read_compensation_parameters() {
    uint8_t buffer[24];
    read_registers(0x88, buffer, 24);

    dig_T1 = (uint16_t)buffer[0] | ((uint16_t)buffer[1] << 8);
    dig_T2 = (int16_t)buffer[2] | ((int16_t)buffer[3] << 8);
    dig_T3 = (int16_t)buffer[4] | ((int16_t)buffer[5] << 8);

    dig_P1 = (uint16_t)buffer[6] | ((uint16_t)buffer[7] << 8);
    dig_P2 = (int16_t)buffer[8] | ((int16_t)buffer[9] << 8);
    dig_P3 = (int16_t)buffer[10] | ((int16_t)buffer[11] << 8);
    dig_P4 = (int16_t)buffer[12] | ((int16_t)buffer[13] << 8);
    dig_P5 = (int16_t)buffer[14] | ((int16_t)buffer[15] << 8);
    dig_P6 = (int16_t)buffer[16] | ((int16_t)buffer[17] << 8);
    dig_P7 = (int16_t)buffer[18] |((int16_t)buffer[19] << 8);
    dig_P8 = (int16_t)buffer[20] | ((int16_t)buffer[21] << 8);
    dig_P9 = (int16_t)buffer[22] | ((int16_t)buffer[23] << 8);

    read_registers(0xA1, buffer, 1);
    dig_H1 = buffer[0];

    read_registers(0xE1, buffer, 7);
    dig_H2 = (int16_t)buffer[0] | ((int16_t)buffer[1] << 8);
    dig_H3 = (uint8_t)buffer[2];
    dig_H4 = (int16_t)(buffer[3] << 4) | (buffer[4] & 0xF);
    dig_H5 = (int16_t)(buffer[5] << 4) | (buffer[4] >> 4);
    dig_H6 = (int8_t)buffer[6];
}

BME280::BME280(uint8_t address) {
    this->i2c_addr = address;
    char *filename = (char*)"/dev/i2c-1";
    if ((i2c_fd = open(filename, O_RDWR)) < 0) {
        perror("Failed to open the i2c bus");
        //exit(1);
    }
    if (ioctl(i2c_fd, I2C_SLAVE, i2c_addr) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        //exit(1);
    }
    read_compensation_parameters();
    write_register(0xF2, 0x01); // Set humidity oversampling to x1
    write_register(0xF4, 0x27); // Set temperature and pressure oversampling to x1 and forced mode
}

BME280::Measurement_t BME280::measure() {
    int32_t pressure, humidity, temperature;
    write_register(0xF4, 0x27); // Set temperature and pressure oversampling to x1 and forced mode
    usleep(50000); // Delay required for measurement
    bme280_read_raw(&humidity, &pressure, &temperature);

    temperature = compensate_temp(temperature);
    pressure = compensate_pressure(pressure);
    humidity = compensate_humidity(humidity);

    measurement.temperature = temperature / 100.0f; // in degrees Celsius
    measurement.pressure = pressure / 100.0f; // in hPa
    measurement.humidity = humidity / 1024.0f; // in %
    return measurement;
}

uint8_t BME280::get_chipID() {
    uint8_t id;
    read_registers(0xD0, &id, 1);
    return id;
}

BME280::~BME280() {
    close(i2c_fd);
}
