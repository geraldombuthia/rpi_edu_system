set(LIB_NAME Drv_Modules)
add_library(${LIB_NAME} STATIC)

target_include_directories(${LIB_NAME} PUBLIC
        MPU6050/
        MCP3008/
        HMC5883L/
        BME280/
)

target_sources(${LIB_NAME} PRIVATE
        MPU6050/mpu6050.cpp
        MCP3008/mcp3008.cpp
        HMC5883L/hmc5883l.cpp
        BME280/bme280.cpp
)

target_link_libraries(${LIB_NAME} PUBLIC
        wiringPi lgpio
)
