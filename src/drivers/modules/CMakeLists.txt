set(LIB_NAME Drv_Modules)
add_library(${LIB_NAME} STATIC )

target_include_directories(${LIB_NAME} PUBLIC
        MPU6050/
        MCP3008/
        HMC5883L/
        BME280/
        GPS/
)

target_sources(${LIB_NAME} PRIVATE
        MPU6050/mpu6050.cpp
        MCP3008/mcp3008.cpp
        HMC5883L/hmc5883l.cpp
        BME280/bme280.cpp
        GPS/gps_data.cpp
        GPS/gps.c
        GPS/nmea.c
        GPS/serial.c
)

target_link_libraries(${LIB_NAME} PUBLIC
        wiringPi lgpio i2c m
)
