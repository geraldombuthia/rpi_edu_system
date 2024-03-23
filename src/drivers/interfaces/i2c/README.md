# I2C Interface code to the Raspberry Pi

## Requirements 
1. Raspberry Pi OS (32/64 bit)
2. i2c-tools
## Objectives
To provide a communication interface between the i2c devices and the Raspberry Pi

## Determining 12C connected devices on the Raspberry Pi os
`sudo i2cdetect -y 1`

Will list down a table with the addresses conected to the raspberry pi.
## I2C devices include
| Device  | Address |
|---------|---------|
| MPU6050 | 68 |
| BME280  | 76 |
| HMC5883l| 1e |

