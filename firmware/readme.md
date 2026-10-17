# Arcpad — QMK firmware for a Seeed XIAO RP2040

This keyboard definition is based on the supplied KiCad schematic and board
images. It targets the **Seeed XIAO RP2040**, not the similarly-shaped XIAO
SAMD21 named in the original schematic symbol. The two boards share the header
footprint, but their MCU GPIO names are different.

## What is included

- 11 MX switches on a diode-isolated 3×4 matrix, with the top-left position
  intentionally unused.
- Encoder rotation and its press switch. The press is placed at matrix `[3,0]`
  (the encoder's S1 pad is Column 0 and S2 is D7), so it is a normal,
  remappable key rather than a special hard-coded input.
- 16 daisy-chained SK6812MINI-E RGB LEDs using the RP2040 PIO-backed QMK
  WS2812 driver: LED1–LED5 are the right-side bar and LED6–LED16 are the 11
  switch LEDs.
- A clean four-layer starter keymap and a separate VIA build target with an
  accompanying VIA v3 definition.

## Pin map

| Function | PCB net / XIAO header | XIAO RP2040 GPIO used by QMK |
| --- | --- | --- |
| Matrix row 0 | D0 | GP26 |
| Matrix row 1 | D1 | GP27 |
| Matrix row 2 | D2 | GP28 |
| Matrix row 3 (encoder press) | D7 | GP1 |
| Matrix column 0 | D3 | GP29 |
| Matrix column 1 | D4 | GP6 |
| Matrix column 2 | D5 | GP7 |
| Matrix column 3 | D6 | GP0 |
| Encoder A | D8 | GP2 |
| Encoder B | D9 | GP4 |
| RGB data into LED1 | D10 | GP3 |

The switch map is:

| | Column 0 (D3) | Column 1 (D4) | Column 2 (D5) | Column 3 (D6) |
| --- | --- | --- | --- | --- |
| Row 0 (D0) | unused | SW1 | SW2 | SW3 |
| Row 1 (D1) | SW4 | SW5 | SW6 | SW7 |
| Row 2 (D2) | SW8 | SW9 | SW10 | SW11 |
| Row 3 (D7) | encoder press | unused | unused | unused |

The standard `COL2ROW` scanner is sufficient: the encoder press bridges
Column 0 to its dedicated fourth row. It has no diode, but that row contains no
other switch, so it cannot create a matrix ghost path.

## LED order and behavior

The schematic routes the LED chain in numerical order: `LED1 → … → LED16`.
The RGB matrix entries therefore use exactly that order. LEDs 1–5 are flagged
as indicators and show a five-step green bar for the current RGB brightness;
the other 11 LEDs are tied to SW1–SW11. The starting brightness and maximum are
deliberately conservative to limit USB current.

The supplied part is an **RGB**, 24-bit SK6812MINI-E, so GRB byte order is set
explicitly in `config.h`. This is not an RGBW configuration.

## Default controls

The base layer uses F13–F23 for SW1–SW11, which provides unambiguous inputs
for host-side macro software. Hold the encoder press for the RGB layer:

| Control | Base layer | Held encoder / RGB layer |
| --- | --- | --- |
| Encoder turn | volume down / up | RGB brightness down / up |
| Encoder press | momentary RGB layer | — |
| SW1–SW3 | F13–F15 | RGB toggle / previous effect / next effect |
| SW4–SW7 | F16–F19 | hue down / up, saturation down / up |
| SW8–SW9 | F20–F21 | brightness down / up |
| SW10 | F22 | bootloader |
| SW11 | F23 | clear EEPROM |

## Build and flash

From the root of this QMK checkout, run:

```sh
qmk compile -kb arcpad -km default
qmk flash -kb arcpad -km default
```

To flash manually, hold the XIAO RP2040's `BOOT` button while connecting USB.
It mounts as `RPI-RP2`; copy the generated `.uf2` file to that drive.

## VIA

Build the VIA-enabled image with:

```sh
qmk compile -kb arcpad -km via
```

Then flash that image and load `via.json` through VIA's Design tab (V3
definitions enabled). The definition covers all 12 physical inputs—including
the encoder press—and encoder rotation. It also exposes QMK RGB Matrix controls.
Its USB VID/PID must remain synchronized with `keyboard.json`.

For official auto-detection later, submit the `via` keymap through the VIA QMK
Userspace workflow and submit `via.json` to the VIA Keyboards repository.

## Before assembling or powering the board

1. **Add a 3.3 V-to-5 V data level shifter.** The PCB powers the
   SK6812MINI-E chain at 5 V but the RP2040 data pin is only 3.3 V. The LED
   datasheet's high-level threshold is specified relative to VDD, so the
   present 330 Ω series resistor does not guarantee reliable data reception.
   A 74AHCT1G125/74AHCT125 powered at 5 V (after the resistor placement is
   reconsidered) is the robust fix.
2. **Budget USB current.** Sixteen RGB LEDs can exceed the current available
   from some USB ports when showing full white. The 128/255 QMK cap reduces
   this risk but does not replace measuring the finished board. Do not raise
   it without checking the LED datasheet and power path.
3. If turning the encoder changes volume in the opposite direction, swap
   `pin_a` and `pin_b` in `keyboard.json` and rebuild.

## Build provenance

This source uses QMK's current data-driven `keyboard.json` conventions and the
RP2040 `vendor` WS2812 driver. It was prepared against QMK firmware commit
`180f394b489c238cb231c2bf8b080262155e03c0` (2026-10-16).
