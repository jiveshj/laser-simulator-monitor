# laser-simulator-monitor

This board [(schematic)](Hardware/monitor_board/monitor_board.pdf)
is used for testing new or questionable laser controller boards.
See [github](https://github.com/BU-BOTLab/dDOSI_system/tree/main/Hardware/Electronics/laserDriverCircuit)
for details of the laser driver..  Here is an archived schematic (as of 12/12/23) for reference: 
[laserDriverCircuit.pdf](Documentation/laserDriverCircuit.pdf).

Here is a sketch of the wiring: [test_setup_wiring.png](Documentation/test_setup_wiring.png).

Here is a basic outline of the expected operation of the board when in use:

* Connect 12V external power to J4
* Connect power and monitoring cables (total of 4 cables) from this board to laser controller
* Connect a USB cable from the Arduino to a computer and set up a terminal program (putty or minicom)
* Connect a separate mini-DIN (round) cable between the laser driver
  and the controller (isolated I2C) board on the test setup
  
Power up the setup.  A test menu will appear and allow the user to interactively run a test.

See [(Software)](Software) for specs on the test code.
