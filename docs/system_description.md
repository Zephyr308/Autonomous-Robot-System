# Autonomous Robot System – Description

## Overview
This project implements an autonomous robot with **reactive behaviors**. It integrates:

- **Head Sensor (Ultrasonic)**: Measures distance to obstacles in front.
- **Tail Sensor (IR)**: Detects obstacles behind the robot.
- **Limbs (DC Motors)**: Provides forward and turning motions.
- **Neck (Servo Motor)**: Rotates for scanning surroundings.
- **Lights (RGB LEDs)**: Indicate behavior states.
- **Behavior Logic (State Machine)**: Determines robot actions based on sensor inputs.
- **Timer-based Motion Controller**: Executes movement commands asynchronously.

## System Architecture
Refer to `block_diagram.png` for visual representation.

## Development Notes
- All sensor and actuator drivers are **bare-metal**, written in C and ARM assembly.
- **Interrupts** are used for time-critical sensors (Ultrasonic, Timer tick).
- **Non-blocking control** ensures responsive and concurrent execution.
