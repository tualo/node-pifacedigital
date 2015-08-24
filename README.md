# PI Face Digital

This package contains a nodejs library and command line tool for the pifacedigital board.
As long as the user is in the group spi this module does not need any root privileges.

## Installation

On a fresh Raspbian installation you should enable SPI. Therefor start `raspi-config` and
enable SPI under "Advanced Options".

After rebooting you should add your user to the SPI-Group:
```
usermod -a -G spi pi
```

### Install necessary libraries

```
git clone https://github.com/piface/libmcp23s17.git
cd libmcp23s17/
make
sudo make install
```

```
git clone https://github.com/piface/libpifacedigital.git
cd libpifacedigital/
make
sudo make install
```

### Install node-pifacedigital

```
npm install node-pifacedigital -g
```
