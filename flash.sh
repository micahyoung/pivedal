#!/bin/bash
dfu_programmer_path=tools/dfu-programmer/src/dfu-programmer
dfu_chipset=at90usb162unor3
dfu_cmd="$dfu_programmer_path $dfu_chipset"
keyboard_firmware="firmware/Arduino-keyboard.hex"
usbserial_firmware="firmware/Arduino-usbserial.hex"

if [ "$1" == "keyboard" ]; then
  firmware=$keyboard_firmware
elif [ "$1" == "arduino" ]; then
  firmware=$usbserial_firmware
else
  firmware=$1
fi

if [ -f "$firmware" -a "${firmware: -4}" == ".hex" ]; then
  $dfu_cmd erase &&
  $dfu_cmd flash "$firmware" &&
  $dfu_cmd reset &&
  echo All Done. Now unplug to reset.
else
  echo Usage: $0 firmware.hex
fi
