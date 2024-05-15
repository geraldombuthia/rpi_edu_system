// // #include "dht11.h"

// #include <wiringPi.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #define MAXTIMINGS	85
// #define DHTPIN		3



// int		dht11_dat[5] = { 0, 0, 0, 0, 0 };
// double	temp;
// double	humidity;

// int read_dht11_dat()
// {
// 	uint8_t		laststate = HIGH;
// 	uint8_t		counter = 0;
// 	uint8_t		j = 0, i;

// 	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

// 	pinMode(DHTPIN, OUTPUT);
// 	digitalWrite(DHTPIN, LOW);
// 	delay(18);
// 	digitalWrite(DHTPIN, HIGH);
// 	delayMicroseconds(40);
// 	pinMode(DHTPIN, INPUT);

// 	for (i = 0; i < MAXTIMINGS; i++)
// 	{
// 		counter = 0;
// 		while (digitalRead(DHTPIN) == laststate)
// 		{
// 			counter++;
// 			delayMicroseconds(1);
// 			if (counter == 255)
// 				break;
// 		}
// 		laststate = digitalRead(DHTPIN);

// 		if (counter == 255)
// 			break;

// 		if ((i >= 4) && (i % 2 == 0))
// 		{
// 			dht11_dat[j / 8] <<= 1;
// 			if (counter > 64)
// 				dht11_dat[j / 8] |= 1;
// 			j++;
// 		}
// 	}

// 	if ((j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)))
// 	{
// 		temp = dht11_dat[2] + (dht11_dat[3] / 10);
// 		humidity = dht11_dat[0] + (dht11_dat[1] / 10);
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

// int main(int argc, char *argv[])
// {
// 	int ret = 0;

// 	if (wiringPiSetup() == -1)
// 		exit(1);
// 	while (ret == 0)
// 	{
// 		ret = read_dht11_dat();
// 		delay(100);
// 	}
// 	printf("Humidity: %.1f%%\nTemperature: %.1f C\n", humidity, temp);
// 	return(0);
// }