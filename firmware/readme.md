# Arcpad

- 11 MX switches and the encoder in a 3×4 matrix.
- Encoder rotation and its press switch. The press is placed at matrix `[0,0]`
- 16 daisy-chained SK6812MINI-E RGB LEDs: LED1–LED5 form a light bar and LED6–LED16 are the 11 switch LEDs.

## Pin map

| Function           | PCB net / XIAO header | XIAO RP2040 GPIO used by QMK |
| ------------------ | --------------------- | ---------------------------- |
| Matrix row 0       | D0                    | GP26                         |
| Matrix row 1       | D1                    | GP27                         |
| Matrix row 2       | D2                    | GP28                         |
| Matrix column 0    | D3                    | GP29                         |
| Matrix column 1    | D4                    | GP6                          |
| Matrix column 2    | D5                    | GP7                          |
| Matrix column 3    | D6                    | GP0                          |
| Encoder A          | D8                    | GP2                          |
| Encoder B          | D9                    | GP4                          |
| RGB data into LED1 | D10                   | GP3                          |

Switch map:

|            | Column 0 (D3) | Column 1 (D4) | Column 2 (D5) | Column 3 (D6) |
| ---------- | ------------- | ------------- | ------------- | ------------- |
| Row 0 (D0) | encoder press | SW1           | SW2           | SW3           |
| Row 1 (D1) | SW4           | SW5           | SW6           | SW7           |
| Row 2 (D2) | SW8           | SW9           | SW10          | SW11          |

## LED order and behavior

LEDs 1–5 are part of the light bar and show a five-step green bar for the current RGB brightness. The other 11 LEDs are tied to SW1–SW11. The starting brightness and maximum are conservative to limit USB current.

## Default controls

The base layer uses F13–F23 for SW1–SW11, which provides unambiguous inputs
for host-side macro software. Hold the encoder press for the RGB layer:

| Control       | Base layer          | Held encoder / RGB layer                   |
| ------------- | ------------------- | ------------------------------------------ |
| Encoder turn  | volume down / up    | RGB brightness down / up                   |
| Encoder press | momentary RGB layer | —                                          |
| SW1–SW3       | F13–F15             | RGB toggle / previous effect / next effect |
| SW4–SW7       | F16–F19             | hue down / up, saturation down / up        |
| SW8–SW9       | F20–F21             | brightness down / up                       |
| SW10          | F22                 | bootloader                                 |
| SW11          | F23                 | clear EEPROM                               |
