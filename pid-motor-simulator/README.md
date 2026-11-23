# uORover Arm PID Motor Simulator

Before tuning PID on the real motors of the **uOttawa Mars Rover Team's robotic arm**, I wrote a fake motor in **Python** and **C++** to see how PID control actually behaves.

**Try it live:** interactive version with sliders and graphs on my portfolio → [rayan-rehou.github.io/#pidsim](https://rayan-rehou.github.io/#pidsim)

## The model
Like a toy car: pushing speeds it up, friction slows it down (more friction the faster it goes).
Every 0.01 s:

```
error    = target - speed
integral = integral + error * dt
push     = kp * error + ki * integral        # P + I
speed    = speed + (push - friction * speed) * dt
```

- **P (kp):** chases the target. Bigger gap → bigger push.
- **I (ki):** remembers the leftover gap and keeps pushing until it's closed.

## Results (target 30, friction 0.5)

| Test | Result | Lesson |
|---|---|---|
| Fixed push, no PID | Levels off at 20 | Open loop never looks at the target |
| P only, kp = 1 | Levels off at 20 | P alone leaves a steady-state gap |
| P only, kp = 100 | 29.85, almost instantly | Bigger kp = smaller gap, never zero |
| P only, kp = 250 | Explodes | kp too big = unstable |
| kp = 5, ki = 10 | Peaks ~33.6, settles ~1.8 s | I closes the gap, with some overshoot |
| kp = 5, ki = 50 | Peaks ~40.7, settles ~1.5 s | More I = more overshoot |
| kp = 20, ki = 50 | Peaks ~31.9, settles ~0.95 s | Stronger P reduces the bump |
| **kp = 20, ki = 10** | **No overshoot, settles ~0.2 s** | **Best in this sim** |

## Run it
```
python pid_sim.py          # plots speed vs target (needs matplotlib)
g++ pid_sim.cpp -o pid_sim && ./pid_sim   # prints speed every 0.5 s
```

## Limits
This motor can push infinitely hard and instantly, so a bigger kp always looks better here. A real motor has a torque limit and noisy encoders, so these numbers don't transfer directly to the arm, but the tuning method does.
