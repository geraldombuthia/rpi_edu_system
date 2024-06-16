# EDUSAT Training Kit
# RPI EDUSAT development code
This is the code to a test of the Edusat development with the aim of attempting to test whether the code will work well with a Raspberry Pi.

## Installation
### Raspberry Pi OS

### Configuration and setup
`sudo raspi-config`

Select Interface Options > SSH > select yes to enable > press okay to exit

Select Interface Options > VNC > select yes to enable > press okay to exit

Select Interface Options > SPI > select yes to enable > press okay to exit

Select Interface Options > I2C > select yes to enable > press okay to exit


### Update
`sudo apt update`
`sudo apt upgrade`

### Install Environment
`sudo apt install g++ git cmake Ninja build-essentials libi2c-dev i2c-tools`

#### Install WiringPi
```
# fetch the source
sudo apt install git
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi

# build the package
./build debian
mv debian-template/wiringpi-3.0-1.deb .

# install it
sudo apt install ./wiringpi-3.0-1.deb

```
For Debug

```
WIRINGPI_DEBUG=1 ./my_wiringpi_program

WIRINGPI_DEBUG=1 gpio readall

```
#### Install lgpio
```
git clone https://github.com/joan2937/lg.git

cd lg

make 

sudo make install
```

#### Install i2c-tools
```
sudo apt-get install i2c-tools libi2c-dev
```
#### Install LVGL
```
git clone https://github.com/lvgl/lvgl.git // 

cd lvgl

git fetch origin v8.3.6

git checkout tags/v8.3.6

```
OR 

```
git clone --branch v8.3.6 --depth 1 https://github.com/lvgl/lvgl.git lvgl

git submodule add https://github.com/lvgl/lvgl.git lvgl

git submodule update --init --recursive


```

#### Install GPS driver ->libgps
```
git clone https://github.com/joyalraju/libgps.git

make

sudo make install
```
### BUILD
```
mkdir build


cd build

cmake ..


make
```
## Getting started with the EDUSAT


### Install software
### Setup Application


