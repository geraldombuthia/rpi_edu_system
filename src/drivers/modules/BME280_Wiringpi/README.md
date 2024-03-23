

Dependencies
```
sudo apt-get install libi2c-dev i2c-tools

git clone https://github.com/WiringPi/WiringPi.git

cd WiringPi/

./build debian

mv debian-template/wiringpi_3.1_arm64.deb .

sudo apt install ./wiringpi_3.1_arm64.deb 

wiringpi


```

Compiling alone
```
g++ bme280readdata.cpp -o bme280readdata -lwiringPi

```
Output should look like this
```
{"sensor":"bme280", "humidity":54.36, "pressure":1011.89, "temperature":25.58, "altitude":9.23, "timestamp":1469568295}
```