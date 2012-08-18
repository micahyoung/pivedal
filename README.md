# The Pivedal

The unofficial VIM clutch of Pivotal Labs

## Hardware

* [Arduino Uno rev3](http://arduino.cc/en/Main/ArduinoBoardUno)
* Pedal sensor (TBD)

### Purchase
* [Arduino Store](http://store.arduino.cc/ww/index.php?main_page=product_info&cPath=11_12&products_id=195)
* [Adafruit](http://adafruit.com/products/50)

### Why Uno rev3?
Unos support an alternate method of flashing called [DFU](http://arduino.cc/en/Hacking/DFUProgramming8U2).
This allows us to use alternate bootloaders (i.e. HID Keyboard) and still reflash the Arduino regardless
of the state its in. Rev2 and later made it much easier to get the board into DFU mode. Rev3 was chosen
because it is the easiest to buy currently and has a new chip: the 16u2.

## References

[MitchTech Uno HID Keyboard walkthrough](http://mitchtech.net/arduino-usb-hid-keyboard/)

Detailed Arduino UNO Keyboard HID firmware compilation tutorial:
* [Part 1](http://hunt.net.nz/users/darran/weblog/13a32/Arduino_UNO_Keyboard_HID_Part_1.html)
* [Part 2](http://hunt.net.nz/users/darran/weblog/faf5e/Arduino_UNO_Keyboard_HID_Part_2.html)

[Making dfu-programmer work with the Uno R3 atmega16u2](http://academic.cleardefinition.com/2012/07/31/using-dfu-programmer-with-an-arduino-uno-r3/)
