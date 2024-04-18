cmake_minimum_required(VERSION 3.25)
project(Edusat LANGUAGES C CXX)

set(SOURCES
    src/drivers/modules/BME280/bme280.cpp
    src/drivers/modules/DHT11/dht11.cpp
    src/drivers/modules/HMC5883L/hmc5883l.cpp
    src/drivers/modules/MCP3008/mcp3008.cpp
    src/drivers/modules/MPU6050/mpu6050.cpp
    src/main.cpp
)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")



add_executable(my_executable ${SOURCES})

target_include_directories(my_executable PRIVATE 
        src/drivers/modules/BME280 
        src/drivers/modules/DHT11 
        src/drivers/modules/HMC5883L 
        src/drivers/modules/MCP3008 
        src/drivers/modules/MPU6050
)

target_link_libraries(my_executable wiringPi lgpio i2c)

