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


## Using

You can use node-pifacedigital as commandline tool or library.

### Commandline

Setting output value:
```
pifacedigital --type set --pin 1 --value 1
```

Getting input value:
```
pifacedigital --type get --pin 1
```

Watch input values:
```
pifacedigital --type watch --pin 1
```
### Library

#### Constructor

The constructor of `PIFaceDigital` takes two arguments. HW_ADDR the address of
your board (setted via jumper) and the optional `closeOnExit` if true all output
pins will reset to 0 if the node process receives the `exit` signal.

```
var PIFD = require('node-pifacedigital');
var pi = PIFD.PIFaceDigital(0,true);
```

You can set the value of on of the output pins with:

```
var value = 1;
pi.set(pin,value);
```

You can read the input pin value with:
```
var val = pi.get(pin);
```
or all input values at once:
```
var val = pi.getInput();
```

You can watch changes on a single Input-Pin with:

```
var callback = function(pin,type){
  // Type will be 'lohi' or 'hilo'.
}
pi.watch(pin,callback);
```
