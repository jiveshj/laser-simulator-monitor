# Laser test setup software

## Preliminary Specification

### Overview

The test setup for a new laser board consists of 4 components:

* A laptop or PC running the main test program (Python/C++/Matlab)
* An Isolated I2C controller board connected by USB/serial to the PC
* A test monitor board also connected by USB (via Arduino pro micro)
  to the PC
* The DUT (device under test), a laser controller

Testing will be performed in several phases:

* Phase I - DUT with no laser or wavelength controller (aka WLD)
* Phase II - Install WLD and laser simulator
* Phase III - Install a real laser

The test is managed by an application program on a PC.  This program
can be written in any convenient language which can communicate with
devices over a USB emulated serial port (Windows `COM` port or linux
`/dev/ttyUSB` or `/dev/ttyACM`).

In addition, embedded programs written in `C/C++` run on AVR
microcontrollers on the I2C controller and test monitor boards.
These programs respond to simple single-line text commands and return
short responses.

### Communication with test boards

#### I2C controller

The I2C controller responds to many commands, but only a few are
useful here.  Send `h` (help) for a complete list.

    d             disable all connected lasers
	e 0           enable laser 0
	i 0 100       set laser 0 current to 100mA (up to 2500mA)
    n 0 250       set non-volatile (permanent) current to 250mA
	r 0           read data from laser 0
	
The `r` command returns output like this:

    IMON 0.000A
    PMON 0.025V
     VSET 0.012V
     TEMP  21.6
      VCC 2.502
    Laser V2.1 config

`VSET` should be close to what was set with the `i` command.

`VCC` is half the power supply voltage and should always be about 2.5V

`TEMP` is the temperature sensor on the laser board.

`IMON` and `PMON` are the monitor current and photodiode monitor
voltage as reported by the WLD controller.

#### Monitor board

The monitor board should respond to the following commands:

    r 0          read ADC channel 0
	r            read all ADC channels
	p 123        set digital pot to 123
	n 123        set digital pot nonvolatile to 123
	e            enable power to laser controller
	d            disable power to laser controller
	l 3          set LED control mask to 3 (both LEDs on)\
	i            read digital inputs

NOTE:  The monitor board V1.0 is designed using an Arduino Pro Micro
(Sparkfun design).  This board turns out to be difficult/impossible to
program without using the Arduino IDE.

The Pro Mini could be substituted as it is almost exactly the same
pinout, though and FTDI serial thing is required.
	
### Software Initialization

At power-up, the software should initialize the direction and pull-up
of each I/O.  Power should be disabled to the laser driver board (net
"IN_ADR" driven low).

### 1.  Test of new board

Prompt the user to be sure that no laser or controller module is
installed and all cables are correctly connected.

Set the digital pot to an appropriately low current limit (100mA?).
Enable power to the laser board.  Read output voltage (ADC11) and
current (ADC9) and display.

_Over current limit_ - turn off power and prompt the user to diagnose

_No over current_ - prompt the user to record the values displayed

### 2.  Test I/O functions through I2C master

Send `r 0` to I2C controller and capture output.  Should be similar to
the below.

    IMON 0.000A
    PMON 0.025V
     VSET 0.012V
     TEMP  21.6
      VCC 2.502
    Laser V2.1 config

Check that VCC and TEMP are sensible, report any communication errors.
If `I2C RD ERR` is received, there is no working I2C communcation with
the laser controller.  Report to the user.

Loop over current settings from 0 to 2500 in steps of 100 and expect:

    I(set)  VSET
	0       0.009V (0-0.05V)
	100     0.101V (0.090-0.110V)
	...
	1000    0.980V (0.9V-1.1V)
	...
	2000    1.955V (1.9V-2.1V)
	...
	2500    2.440V (2.4V-2.6V)

Make sure the values are
