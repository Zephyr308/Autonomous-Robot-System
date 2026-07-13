;************************************************************
; @file    lights.s
; @brief   LED GPIO initialization (Legacy Assembly)
;
; This file is retained for reference only.
; Active implementation should use lights.c.
;
; Configures:
;   PF1 - Red LED
;   PF2 - Blue LED
;   PF3 - Green LED
;
;************************************************************

        THUMB

;------------------------------------------------------------
; Register definitions
;------------------------------------------------------------

SYSCTL_RCGCGPIO_R     EQU     0x400FE608

GPIO_PORTF_DIR_R      EQU     0x40025400
GPIO_PORTF_AFSEL_R    EQU     0x40025420
GPIO_PORTF_DEN_R      EQU     0x4002551C
GPIO_PORTF_AMSEL_R    EQU     0x40025528
GPIO_PORTF_PCTL_R     EQU     0x4002552C

GPIO_PORTF_LOCK_R     EQU     0x40025520
GPIO_PORTF_CR_R       EQU     0x40025524

GPIO_LOCK_KEY         EQU     0x4C4F434B


;------------------------------------------------------------
; Constants
;------------------------------------------------------------

PORTF_CLOCK           EQU     0x20
LED_PINS              EQU     0x0E       ; PF1, PF2, PF3


        AREA |.text|, CODE, READONLY, ALIGN=2

        EXPORT LIGHTS_Init


;============================================================
; Initialize LED GPIO pins
;============================================================

LIGHTS_Init

        ; Enable Port F clock
        LDR     R1, =SYSCTL_RCGCGPIO_R
        LDR     R0, [R1]
        ORR     R0, R0, #PORTF_CLOCK
        STR     R0, [R1]

        ; Allow clock to stabilize
        LDR     R0, [R1]


        ; Unlock Port F protected pins
        LDR     R1, =GPIO_PORTF_LOCK_R
        LDR     R0, =GPIO_LOCK_KEY
        STR     R0, [R1]


        ; Allow configuration changes
        LDR     R1, =GPIO_PORTF_CR_R
        MOV     R0, #0xFF
        STR     R0, [R1]


        ; Disable alternate functions
        LDR     R1, =GPIO_PORTF_AFSEL_R
        LDR     R0, [R1]
        BIC     R0, R0, #LED_PINS
        STR     R0, [R1]


        ; Select GPIO function
        LDR     R1, =GPIO_PORTF_PCTL_R
        LDR     R0, [R1]
        BIC     R0, R0, #(0xFFF << 4)
        STR     R0, [R1]


        ; Disable analog mode
        LDR     R1, =GPIO_PORTF_AMSEL_R
        LDR     R0, [R1]
        BIC     R0, R0, #LED_PINS
        STR     R0, [R1]


        ; Configure PF1-PF3 as outputs
        LDR     R1, =GPIO_PORTF_DIR_R
        LDR     R0, [R1]
        ORR     R0, R0, #LED_PINS
        STR     R0, [R1]


        ; Enable digital GPIO
        LDR     R1, =GPIO_PORTF_DEN_R
        LDR     R0, [R1]
        ORR     R0, R0, #LED_PINS
        STR     R0, [R1]


        BX      LR


        ALIGN
        END
