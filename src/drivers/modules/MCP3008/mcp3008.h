#ifndef MCP3008_H
#define MCP3008_H

#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>
// #include "mcp3008.h"
#include <stdexcept>
#include <iostream>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPI_CHANNEL 0
#define SPI_SPEED   1000000  // 1 MHz

class MCP3008 {
public:
    MCP3008(int channel = SPI_CHANNEL, int speed = SPI_SPEED);

    int readADC(int channel);

    void readAllChannels();

private:
    int spi_channel;
    int spi_speed;
};

#endif // MCP3008_H