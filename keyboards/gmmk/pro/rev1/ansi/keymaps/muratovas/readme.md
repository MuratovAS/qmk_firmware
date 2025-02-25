# GMMK PRO (ANSI)

A tenkeyless 75% keyboard made and sold by Glorious LLC. Equipped with the STM32 ARM Cortex-M4 microcontroller, with support for rotary encoders and three additional layouts. [More info at Glorious](https://www.pcgamingrace.com/products/glorious-gmmk-pro-75-barebone-black-reservation)

Make config for this keyboard (Docker):

    util/docker_build.sh gmmk/pro/ansi:muratovas

Flashing config for this keyboard:

    util/docker_build.sh gmmk/pro/ansi:muratovas:flash

To reset the board into bootloader mode, do one of the following:

* Space+B will reset the board to bootloader mode if Stock ROM
* Fn+Backslash will reset the board to bootloader mode if you have flashed the default QMK keymap
* Hold the Escape key while connecting the USB cable (also erases persistent settings)
* Hold the Reset switch mounted on the bottom side of the PCB while connecting the USB cable
