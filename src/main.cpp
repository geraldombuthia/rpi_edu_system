#include <cstddef>
#include <cstdio>
#include "mpu6050.h"
#include "bme280.h"

int main()
{
    MPU6050 mpu6050(0x68, true);
    float roll, pitch, yaw;
    float ax, ay, az, gr, gp, gy;

    // Create an instance of the BME280 class
    BME280 sensor(0x76);
    // Call the measure method to get the measurements
    BME280::Measurement_t measurements = sensor.measure();

    // Now you can access the measurements
    float temperature = measurements.temperature; // in degrees Celsius
    float pressure = measurements.pressure;       // in hPa
    float humidity = measurements.humidity;       // in %
    float altitude = measurements.altitude;       // in meters

    while (1)
    {
        mpu6050.getGyro(&roll, &pitch, &yaw);
        mpu6050.getAccel(&ax, &ay, &az);
        printf("Roll: %f, Pitch: %f, Yaw: %f\n\n", roll, pitch, yaw);
        printf("Ax: %f, Ay: %f, Az: %f\n\n", ax, ay, az);

        printf("Temperature: %.2f C\n", temperature);
        printf("Pressure: %.2f hPa\n", pressure);
        printf("Humidity: %.2f %%\n", humidity);
        printf("Altitude: %.2f m\n", altitude);
    }
}