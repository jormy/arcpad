# arcpad

arcpad is a 11 key macropad with a rotary enccoder and a light bar.
made for Hack Club's Stardance Hackpad program.

## features

- snap fit 3d printed case with no screws needed
- 11 keys in a 4x3 layout
- EC11 rotary encoder
- light bar composed of 5 LEDS that can be programmed to show whatever you want (e.g. volume, brightness)
- QMK firmware with VIA support (not tested yet)

## CAD model

I wanted to keep the design really compact, so I decided not to use screws and secured the PCB with friction instead.

The PCB is sandwiched between a base and a top plate, the PCB is secured to the top plate when the switches are attached, and the top plate secures to the base with some neat snap fit geometry

![Case render](/assets/renders/render.PNG)

![Attachment mechanism](/assets/cross_section.png)

All parts of the model are printable with no supports, with exception of the USB-C opening in the base.

## PCB

here are the schematic andn PCB designs, both made in Kicad:

![Schematic](/assets/schematic.png)

![PCB design](/assets/pcb.png)

![PCB render](/assets//renders/pcb%20render.png)

## Firmware

This macropad uses QMK firmware. It has VIA support, though I will need to test it when I make the physical macropad.

## BOM

everything you need to make this macropad

- 11x Cherry MX Switches
- 11x DSA Keycaps
- 12x through-hole 1N4148 Diodes
- 16x SK6812 MINI-E LEDs
- 1x EC11 Rotary encoder
- 1x XIAO RP2040
- 1x 100 µF capacitor
- 1x 330Ω resistor
- 1x Case (3 3d printed parts)
