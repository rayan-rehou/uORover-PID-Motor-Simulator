# Joystick Motor Control (Jog Prototype)

An ESP32 reads a joystick and drives a 28BYJ-48 stepper motor through a ULN2003 driver. The motor turns faster the further you push, stops when you let go, tracks its angle, stops at ±180° and sets zero with a click of the stick. I built it to practise jog control for the uORover arm's joints.

**Watch the demo, then try the simulation with a live Serial Monitor:** [rayan-rehou.github.io/#jogctl](https://rayan-rehou.github.io/#jogctl)

Status: built and tested on a real breadboard (November 2026).

## What it does

- Push the stick right: the motor turns clockwise. Push left: counter-clockwise.
- Push further: it turns faster (20 ms per step when barely pushed, 2 ms when fully pushed).
- Let go: the stick returns to its centre, which is inside the dead zone, so the motor stops.
- Every step is counted, so the ESP32 knows the angle (2048 steps = 360°).
- It stops at +180° and −180°, like a real joint with limits.
- Clicking the stick makes the current spot the new zero.
- The angle is printed to the Serial Monitor 5 times per second.

## Hardware

- ESP32 Dev Module
- HW-504 joystick module
- 28BYJ-48 stepper motor (5 V)
- ULN2003 driver board
- Breadboard and jumper wires

## Wiring

| Component | ESP32 |
|---|---|
| Joystick VRx | GPIO 34 (analog input) |
| Joystick SW | GPIO 32 (`INPUT_PULLUP`) |
| Joystick + | GPIO 13 set HIGH (3.3 V) |
| Joystick GND | GND |
| ULN2003 IN1 / IN2 / IN3 / IN4 | GPIO 26 / 25 / 33 / 27 |
| ULN2003 + / − | VIN (5 V) / GND |
| 28BYJ-48 | plugs into the ULN2003 board |

Everything is on the left side of the ESP32. The joystick is powered from GPIO 13 set HIGH because the 3V3 pin is on the other side of the board.

## How it works

1. `analogRead(34)` reads the stick from 0 (full left) to 4095 (full right). I measured my joystick's real centre at about 1835.
2. Dead zone: between 1635 and 2035 the motor does nothing.
3. To take one step, the ESP32 moves to the next row of the 4-step coil table (`SEQ`) and writes it to IN1–IN4. Going forward through the rows turns right, going backward turns left.
4. `map()` turns how far the stick is pushed into the wait between steps: 20 ms (slow) to 2 ms (fast).
5. `position` counts the steps: +1 right, −1 left. Angle = position × 360 ÷ 2048.
6. The motor only steps if `position` is still inside ±1024 steps (±180°).
7. The angle is printed with `millis()` every 200 ms, so printing never slows the motor down.

## Bugs I fixed

- **All 4 driver LEDs on at once:** the coils have to be switched on two at a time, one row of the table per step, in order (1+2, then 2+3, then 3+4, then 4+1).
- **LEDs changing but motor not turning:** the delay between steps was too short (1 ms). 2 ms is the fastest this motor can follow.
- **Wrong speed direction on the left:** the left `map()` had its numbers reversed. It must be `map(x, 1635, 0, 20, 2)`.
- **Angle stuck at 0:** the lines that count `position` were missing, and so was `Serial.begin()`.
- **Joystick reading nothing:** the wires were swapped (SW on 34, VRx on 32) and + was on VIN. Fixed to VRx → 34, SW → 32, + → 3.3 V.

## Files

- [`Joystick_Motor_Control.ino`](Joystick_Motor_Control.ino): the full program (C++, Arduino framework)
