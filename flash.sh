#!/bin/bash
dfu_programmer_path=tools/dfu-programmer/src/dfu-programmer
dfu_chipset=at90usb162unor3
dfu_cmd="$dfu_programmer_path $dfu_chipset"

firmware=$1

if [ -f "$firmware" -a "${firmware: -4}" == ".hex" ]; then
  $dfu_cmd erase &&
  $dfu_cmd flash "$firmware" &&
  $dfu_cmd reset &&
  echo All Done. Now unplug to reset.
else
  echo Usage: $0 firmware.hex
fi
