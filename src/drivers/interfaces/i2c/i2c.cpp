// #include "i2c.h"

// int main()
// {
//     int file;
//     int adapter_nr = 1;
//     int addr = 0x76;

//     char filename[20];
//     char buf[4] = {0};

//     snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);

//     file = open(filename, O_RDWR);
//     if (file < 0)
//     {
//         perror("Error opening file");
//         printf("Error: %s\n", strerror(errno));
//         exit(1);
//     }

//     if (ioctl(file, I2C_SLAVE, addr) < 0)
//     {
//         perror("Failed to acquire bus access and/or talk to slave");
//         printf("Error: %s\n", strerror(errno));
//         exit(1);
//     }
//     __u8 reg = 0xF7;
//     __u8 reg1 = 0xFE;
//     // replace with register addresses and data
//     buf[0] = reg;

//     if (write(file, buf, 1) != 1)
//     {
        printf("Error writing to i2c slave");
//         exit(1);
//     }
//     if(read(file, buf, 3) != 3)
//     {
//         perror("Failed to read from the i2c bus");
//         printf("Error: %s\n", strerror(errno));
//         exit(1);
//     }
//     int pressure = (buf[0] << 12) | (buf[1] << 4) | buf[2] >> 4;
//     printf("Pressure: %d\n", pressure);
//     buf[0] = reg1;
//     int temperature = (buf[0] << 12) | (buf[1] << 4) | (buf[2] >> 4);
//     printf("temperature: %d\n", temperature);
// }
