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

## Instructions
1. Clone this repository and run `git submodule update --init`
2. Open your sketch and upload it to your Arduino
3. Put the board into DFU mode by shorting these pins with pliers or a wire. ([diagram](http://arduino.cc/en/uploads/Hacking/Uno-front-DFU-reset.png))
4. Compile the fork of dfu-programmer by doing these steps:
  * Install build pre-reqs
      * Ubuntu: build-essentials, automake, libusb-dev, libusb-1.0.0-dev
  * Compile dfu-programmer

    ```
    cd tools/dfu-programmer
    ./bootstrap.sh
    ./configure
    make
    ```
  * The compiled binary will be at `tools/dfu-programmer/src/dfu-programmer`

5. Install the keyboard bootloader:

    ```
    $dfu-programmer_path at90usb162unor3 erase
    $dfu-programmer_path at90usb162unor3 flash --debug 1 firmware/Arduino-keyboard.hex
    $dfu-programmer_path at90usb162unor3 reset
    ```

6. Done! Unplug and plug back in to start sending "aaaaa"
7. To reset your Arduino back to normal so you can edit the sketch:
  * Short the pins like in Step 5 to get back to DFU mode
  * Re-flash the default firmware

    ```
    $dfu-programmer_path at90usb162unor3 erase
    $dfu-programmer_path at90usb162unor3 flash --debug 1 firmware/Arduino-usbserial.hex
    $dfu-programmer_path at90usb162unor3 reset
    ```
  * Unplug and plug back in. It's ready for a sketch upload.

## References

[MitchTech Uno HID Keyboard walkthrough](http://mitchtech.net/arduino-usb-hid-keyboard/)

[USB HID Keycode Reference](http://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/translate.pdf) ("HID Usage ID" column)

Detailed Arduino UNO Keyboard HID firmware compilation tutorial:
* [Part 1](http://hunt.net.nz/users/darran/weblog/13a32/Arduino_UNO_Keyboard_HID_Part_1.html)
* [Part 2](http://hunt.net.nz/users/darran/weblog/faf5e/Arduino_UNO_Keyboard_HID_Part_2.html)

[Making dfu-programmer work with the Uno R3 atmega16u2](http://academic.cleardefinition.com/2012/07/31/using-dfu-programmer-with-an-arduino-uno-r3/)