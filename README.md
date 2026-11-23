# uORover Projects

My work, tests and prototypes for the **uOttawa Mars Rover Team (uORover)**. I'm on the embedded software team for the rover's robotic arm, and these are the things I built to learn how its joints are controlled before working on the real motors.

| Project | What it does | Demo |
|---|---|---|
| [PID Motor Simulator](pid-motor-simulator/) | A fake motor in Python and C++ to see how P and I gains change speed control: steady-state error, overshoot and settling time | [Try it](https://rayan-rehou.github.io/#pidsim) |
| [Joystick Motor Control (Jog Prototype)](joystick-motor-control/) | An ESP32 and a joystick drive a stepper motor: dead zone, faster the further you push, angle tracking, ±180° limits and click to zero | [Watch and try it](https://rayan-rehou.github.io/#jogctl) |

## What I practiced

- PID control: how the P and I gains affect steady-state error, overshoot and settling time
- Simulating a motor in Python (matplotlib) and C++ before touching hardware
- Jog control on real hardware: reading a joystick with the ESP32's ADC, a dead zone, and a speed command with `map()`
- Driving a stepper motor, counting steps to track the angle, joint limits in software, and setting zero

## Note

The real arm uses moteus brushless motor controllers. These are learning prototypes: the numbers don't transfer directly to the arm, but the methods do.

Portfolio: [rayan-rehou.github.io](https://rayan-rehou.github.io)
