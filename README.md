# Obstacle Avoidance Robot using Arduino

This project implements an obstacle-avoidance robot using Arduino. The robot is equipped with ultrasonic sensors to detect obstacles and stepper motors for movement. When an obstacle is detected, the robot stops to avoid a collision. The goal of this project is to demonstrate basic robotics principles and sensor integration.


https://github.com/masoudrahimi39/Obstacle-Avoidance-using-Arduino/assets/65596290/2f3d7016-fab7-4f93-93eb-25cbbade804d




## How It Works

1. **Ultrasonic Sensors**: Continuously measure the distance to nearby objects.
2. **Obstacle Detection**: If an obstacle is detected within a predefined range, the robot stops moving.

### Hardware
- Arduino (specify model, e.g., Arduino Mega)
- Ultrasonic sensor (e.g., HC-SR04)
- Stepper motors
- Stepper motor driver
- Power supply (battery)
- Connecting wires and breadboard

### Software
- Arduino IDE
- Libraries:
  - `Stepper.h` or equivalent for motor control
  - Custom or standard library for ultrasonic sensor (e.g., `NewPing.h`)
