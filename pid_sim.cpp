#include <iostream>

int main() {
    double speed = 0;        // the car isn't moving yet
    double target = 30;      // we want it to go 30
    double dt = 0.01;        // we check the car every 0.01 seconds

    double friction = 0.5;   // the floor slows the car down
    double kp = 20;          // P: how hard we chase the target
    double ki = 10;          // I: how fast we learn the steady push
    double integral = 0;     // the I's memory, empty at the start

    for (int step = 0; step < 500; step++) {                  // 500 frames x 0.01 s = 5 seconds
        double error = target - speed;                        // gap
        integral = integral + error * dt;                     // I memory
        double push = kp * error + ki * integral;             // P + I
        speed = speed + (push - friction * speed) * dt;       // move the car

        if (step % 50 == 0) {                                 // print every 0.5 s
            std::cout << "time: " << step * dt << " speed: " << speed << std::endl;
        }
    }
    return 0;
}
