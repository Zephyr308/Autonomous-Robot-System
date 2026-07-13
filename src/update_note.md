✅ timing.c/h (scheduler foundation)
✅ limb_hw.c/h
✅ limbs.c/h
✅ head_hw.c/h
✅ head.c/h
✅ tail.c/h
✅ utils.c/h
✅ robot.c/h


Robot/
│
├── system/
│   ├── timing.c
│   ├── timing.h
│   ├── utils.c
│   └── utils.h
│
├── drivers/
│   ├── limb_hw.c
│   ├── limb_hw.h
│   ├── head_hw.c
│   ├── head_hw.h
│
├── sensors/
│   ├── head.c
│   ├── head.h
│   ├── tail.c
│   └── tail.h
│
├── control/
│   ├── limbs.c
│   ├── limbs.h
│   ├── robot.c
│   └── robot.h
│
├── devices/
│   ├── neck.c
│   ├── neck.h
│   ├── lights.c
│   └── lights.h
│
└── legacy/
    ├── delay.c
    ├── delay.h
    ├── head.s
    ├── tail.s
    ├── motors.s
    └── lights.s

0ms
 |
 +-- LIMBS_Update
 +-- HEAD_Update
 +-- ROBOT_Update
 +-- NECK_Update
 +-- LIGHTS_Update


10ms
 |
 +-- LIMBS_Update
 +-- HEAD_Update


20ms
 |
 +-- LIMBS_Update
 +-- HEAD_Update
 +-- NECK_Update


50ms
 |
 +-- ROBOT_Update


Task timing table

The firmware now behaves like this:

Task	Period	Purpose
LIMBS_Update()	10ms	motor control
HEAD_Update()	10ms	ultrasonic processing
ROBOT_Update()	50ms	decision making
NECK_Update()	20ms	servo movement
LIGHTS_Update()	100ms	LED effects
Runtime behaviour

Example:

0ms
 |
 +-- LIMBS_Update
 +-- HEAD_Update
 +-- ROBOT_Update
 +-- NECK_Update
 +-- LIGHTS_Update


10ms
 |
 +-- LIMBS_Update
 +-- HEAD_Update


20ms
 |
 +-- LIMBS_Update
 +-- HEAD_Update
 +-- NECK_Update


50ms
 |
 +-- ROBOT_Update

No module blocks another.

Old vs new firmware flow
Old:
main()
 |
 |
delay()
 |
 |
Timer interrupt
 |
 |
sensor
 |
 |
motor
 |
 |
delay again
New:
main()

while(1)
{
    scheduler

        |
        +-- motors
        |
        +-- sensors
        |
        +-- robot brain
        |
        +-- servo
        |
        +-- lights
}

Final project dependency tree
main.c

 |
 +-- timing
 |
 +-- robot
 |      |
 |      +-- head
 |      |
 |      +-- tail
 |      |
 |      +-- limbs
 |
 +-- neck
 |
 +-- lights


Hardware layer:

limb_hw
head_hw


The firmware is now converted from a blocking interrupt-driven design into a cooperative embedded control system.

The next recommended step is a cleanup pass:

Add system_config.h (central pins/constants)
Add watchdog recovery
Add motor PWM speed control
Add neck scanning behaviour
Add robot behaviour states (explore / avoid / hide / idle) properly.

