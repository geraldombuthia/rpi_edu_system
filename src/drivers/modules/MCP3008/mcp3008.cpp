#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHANNEL 0
#define SPI_SPEED   1000000  // 1 MHz

class MCP3008 {
public:
    MCP3008(int channel = SPI_CHANNEL, int speed = SPI_SPEED) : spi_channel(channel), spi_speed(speed) {
        if (wiringPiSetup() == -1) {
            throw std::runtime_error("Failed to setup wiringPi");
        }

        if (wiringPiSPISetup(spi_channel, spi_speed) == -1) {
            throw std::runtime_error("Failed to setup SPI");
        }
    }

    int readADC(int channel) {
        if (channel < 0 || channel > 7) {
            throw std::invalid_argument("Channel must be between 0 and 7");
        }

        unsigned char buffer[3];
        buffer[0] = 1;  // Start bit
        buffer[1] = (8 + channel) << 4;  // Single-ended mode, channel (0-7)
        buffer[2] = 0;  // Don't care byte

        wiringPiSPIDataRW(spi_channel, buffer, 3);

        int result = ((buffer[1] & 3) << 8) + buffer[2];
        return result;
    }

    void readAllChannels() {
        for (int channel = 0; channel < 8; channel++) {
            int value = readADC(channel);
            std::cout << "Channel " << channel << ": " << value << std::endl;
        }
    }

private:
    int spi_channel;
    int spi_speed;
};

