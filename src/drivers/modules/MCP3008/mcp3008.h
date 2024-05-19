#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>

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

