;************************************************************
; @file    limb.s
; @brief   Motor GPIO control driver (Legacy Assembly)
;
; This file is retained for reference only.
; Active implementation should use limb.c.
;
; Motor control pins:
;   PE2 - Motor Left control
;   PE3 - Motor Right control
;
; Functions:
;   LIMBS_Init
;   TURN_Left
;   TURN_Right
;   FORWARD
;   STOP
;
;************************************************************

        THUMB

;------------------------------------------------------------
; Register definitions
;------------------------------------------------------------

SYSCTL_RCGCGPIO_R     EQU     0x400FE608

GPIO_PORTE_DATA_R     EQU     0x400243FC
GPIO_PORTE_DIR_R      EQU     0x40024400
GPIO_PORTE_AFSEL_R    EQU     0x40024420
GPIO_PORTE_DR8R_R     EQU     0x40024508
GPIO_PORTE_DEN_R      EQU     0x4002451C
GPIO_PORTE_AMSEL_R    EQU     0x40024528
GPIO_PORTE_PCTL_R     EQU     0x4002452C


;------------------------------------------------------------
; Constants
;------------------------------------------------------------

PORTE_CLOCK           EQU     0x10

MOTOR_LEFT            EQU     0x04       ; PE2
MOTOR_RIGHT           EQU     0x08       ; PE3
MOTOR_MASK            EQU     0x0C       ; PE2 + PE3


        AREA |.text|, CODE, READONLY, ALIGN=2

        EXPORT LIMBS_Init
        EXPORT TURN_Left
        EXPORT TURN_Right
        EXPORT FORWARD
        EXPORT STOP


;============================================================
; Initialize motor control GPIO
;============================================================

LIMBS_Init

        ; Enable Port E clock
        LDR     R1, =SYSCTL_RCGCGPIO_R
        LDR     R0, [R1]
        ORR     R0, R0, #PORTE_CLOCK
        STR     R0, [R1]

        ; Allow clock stabilization
        LDR     R0, [R1]


        ; Disable alternate function
        LDR     R1, =GPIO_PORTE_AFSEL_R
        LDR     R0, [R1]
        BIC     R0, R0, #MOTOR_MASK
        STR     R0, [R1]


        ; Select GPIO function
        LDR     R1, =GPIO_PORTE_PCTL_R
        LDR     R0, [R1]
        BIC     R0, R0, #(0xFF << 8)
        STR     R0, [R1]


        ; Disable analog function
        LDR     R1, =GPIO_PORTE_AMSEL_R
        LDR     R0, [R1]
        BIC     R0, R0, #MOTOR_MASK
        STR     R0, [R1]


        ; Configure PE2 and PE3 as outputs
        LDR     R1, =GPIO_PORTE_DIR_R
        LDR     R0, [R1]
        ORR     R0, R0, #MOTOR_MASK
        STR     R0, [R1]


        ; Enable 8mA drive strength
        LDR     R1, =GPIO_PORTE_DR8R_R
        LDR     R0, [R1]
        ORR     R0, R0, #MOTOR_MASK
        STR     R0, [R1]


        ; Enable digital function
        LDR     R1, =GPIO_PORTE_DEN_R
        LDR     R0, [R1]
        ORR     R0, R0, #MOTOR_MASK
        STR     R0, [R1]


        ; Stop motors initially
        LDR     R1, =GPIO_PORTE_DATA_R
        MOV     R0, #0
        STR     R0, [R1]


        BX      LR


;============================================================
; Turn Left
;
; PE2 = 1
; PE3 = 0
;============================================================

TURN_Left

        LDR     R1, =GPIO_PORTE_DATA_R
        MOV     R0, #MOTOR_LEFT
        STR     R0, [R1]

        BX      LR


;============================================================
; Turn Right
;
; PE2 = 0
; PE3 = 1
;============================================================

TURN_Right

        LDR     R1, =GPIO_PORTE_DATA_R
        MOV     R0, #MOTOR_RIGHT
        STR     R0, [R1]

        BX      LR


;============================================================
; Move Forward
;
; PE2 = 1
; PE3 = 1
;============================================================

FORWARD

        LDR     R1, =GPIO_PORTE_DATA_R
        MOV     R0, #MOTOR_MASK
        STR     R0, [R1]

        BX      LR


;============================================================
; Stop Motors
;
; PE2 = 0
; PE3 = 0
;============================================================

STOP

        LDR     R1, =GPIO_PORTE_DATA_R
        MOV     R0, #0
        STR     R0, [R1]

        BX      LR


        ALIGN
        END
