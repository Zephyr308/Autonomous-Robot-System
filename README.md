# Autonomous Robot System

**Author:** Syed Zain Hasan  
**Role:** Embedded & Mechatronics Engineer  

This repository contains a **modular, autonomous robot system** using the TM4C123 microcontroller. The robot exhibits reactive behaviors using ultrasonic and IR sensors, DC motors, a servo neck, and RGB LEDs.

---

## **Features**
- **Sensor-driven navigation**: Ultrasonic (head) & IR (tail) for obstacle detection.
- **Modular design**: Separate modules for head, tail, limbs, neck, lights, and behavior.
- **State-machine behaviors**: `play`, `shy`, and `avoid`.
- **Non-blocking motion control**: Timer-driven execution of motors and servo.
- **Assembly & Bare-metal C drivers**: Direct register access for precise control.

---

## **Repository Structure**
- `src/`: Source code for all modules
- `utils/`: Utility functions like delay and random number generator
- `docs/`: Documentation and block diagrams
- `main.c`: Entry point, initializes modules and runs state machine

---

## **Hardware**
- TM4C123GH6PM microcontroller
- Ultrasonic sensor
- IR sensor
- DC motors with H-bridge
- Servo motor for neck
- RGB LEDs

---

## **Build & Run**
1. Open the project in **Keil / Code Composer Studio / MCUXpresso**.
2. Build all `.c` and `.s` files.
3. Flash to the TM4C123 MCU.
4. Observe robot behavior and LED indicators.

---

## **Block Diagram**
See `docs/block_diagram.png` for system overview.

---

## **License**
This project is released under the MIT License.
