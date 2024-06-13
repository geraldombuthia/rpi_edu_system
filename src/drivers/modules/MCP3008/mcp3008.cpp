#include "mcp3008.h"

MCP3008::MCP3008(int channel, int speed) : spi_channel(channel), spi_speed(speed)
{
    if (wiringPiSetup() == -1)
    {
        throw std::runtime_error("Failed to setup wiringPi");
    }

    if (wiringPiSPISetup(spi_channel, spi_speed) == -1)
    {
        throw std::runtime_error("Failed to setup SPI");
    }
    // Set the SPI mode to mode 0
    int fd = wiringPiSPIGetFd(spi_channel);

    if (fd < 0) {
        throw std::runtime_error("Failed to get SPI file descriptor");
    }

    uint8_t mode = SPI_CHANNEL;
    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0) {
        throw std::runtime_error("Failed to set SPI mode");
    }
}

int MCP3008::readADC(int channel)
{
    if (channel < 0 || channel > 7)
    {
        throw std::invalid_argument("Channel must be between 0 and 7");
    }

    unsigned char buffer[3];
    buffer[0] = 1;                  // Start bit
    buffer[1] = (8 + channel) << 4; // Single-ended mode, channel (0-7)
    buffer[2] = 0;                  // Don't care byte

    wiringPiSPIDataRW(spi_channel, buffer, 3);

    int result = ((buffer[1] & 3) << 8) + buffer[2];
    return result;
}

void MCP3008::readAllChannels()
{
    for (int channel = 0; channel < 8; channel++)
    {
        int value = readADC(channel);
        std::cout << "Channel " << channel << ": " << value << std::endl;
    }
}
