import matplotlib.pyplot as plt

speed = 0       # the car isn't moving yet
target = 30     # we want it to go 30
dt = 0.01       # we check the car every 0.01 seconds

friction = 0.5  # the floor slows the car down
kp = 20         # P: how hard we chase the target
ki = 10         # I: how fast we learn the steady push
integral = 0    # the I's memory, empty at the start

times = []      # time of each frame
speeds = []     # speed of each frame

for step in range(500):                                   # 500 frames x 0.01 s = 5 seconds
    error = target - speed                                # gap: + too slow, - too fast, 0 perfect
    integral = integral + error * dt                      # I memory: add this frame's gap to the pile
    push = kp * error + ki * integral                     # P (gap right now) + I (pile of past gaps)
    speed = speed + (push - friction * speed) * dt        # move the car: push vs friction over 0.01 s

    times.append(step * dt)
    speeds.append(speed)

plt.plot(times, speeds, label="speed")
plt.axhline(target, linestyle="--", label="target")
plt.xlabel("time (s)")
plt.ylabel("speed")
plt.title(f"kp={kp}, ki={ki}")
plt.legend()
plt.show()
