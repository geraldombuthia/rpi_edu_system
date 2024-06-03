set(LIB_NAME drv_modules)
add_library(${LIB_NAME} INTERFACE)

target_include_directories(${LIB_NAME} INTERFACE
        MPU6050/
        MCP3008/
        HMC5883L/
        DHT11/
        BME280_Wiringpi/
        BME280/
)

target_link_libraries(${LIB_NAME} INTERFACE
        MPU6050/mpu6050.h
        MPU6050/mpu6050.cpp
        MCP3008/mcp3008.h
        MCP3008/mcp3008.cpp
        HMC5883L/hmc5883l.h
        HMC5883L/hmc5883l.cpp
        DHT11/dht11.h
        DHT11/dht11.cpp
        BME280_Wiringpi/bme280.h
        BME280_Wiringpi/bme280.cpp
        BME280/bme280.h
        BME280/bme280.cpp
)

target_compile_options(${LIB_NAME} INTERFACE
    wiringPi lgpio i2c
)