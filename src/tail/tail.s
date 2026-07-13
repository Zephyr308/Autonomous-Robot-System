;************************************************************
; @file    tail.s
; @brief   Rear IR sensor driver (PA5)
;
; Provides:
;   TAIL_Init()   - Initialize PA5 as a digital GPIO input
;   TAIL_sense()  - Read PA5 sensor state
;
; Returns:
;   R0 = 0x20 if sensor output is HIGH
;   R0 = 0x00 if sensor output is LOW
;************************************************************

        THUMB

;------------------------------------------------------------
; Register addresses
;------------------------------------------------------------

SYSCTL_RCGCGPIO_R     EQU     0x400FE608

GPIO_PORTA_DATA_R     EQU     0x400043FC
GPIO_PORTA_DIR_R      EQU     0x40004400
GPIO_PORTA_AFSEL_R    EQU     0x40004420
GPIO_PORTA_DEN_R      EQU     0x4000451C
GPIO_PORTA_AMSEL_R    EQU     0x40004528
GPIO_PORTA_PCTL_R     EQU     0x4000452C

;------------------------------------------------------------
; Constants
;------------------------------------------------------------

PORTA_CLOCK           EQU     0x01
IR_PIN                EQU     0x20          ; PA5

;------------------------------------------------------------

        AREA    |.text|, CODE, READONLY, ALIGN=2

        EXPORT  TAIL_Init
        EXPORT  TAIL_sense

;============================================================
; Initialize rear IR sensor
;============================================================

TAIL_Init

        ; Enable Port A clock
        LDR     R1, =SYSCTL_RCGCGPIO_R
        LDR     R0, [R1]
        ORR     R0, R0, #PORTA_CLOCK
        STR     R0, [R1]

        ; Small delay to allow clock to stabilize
        LDR     R0, [R1]

        ; Disable alternate function on PA5
        LDR     R1, =GPIO_PORTA_AFSEL_R
        LDR     R0, [R1]
        BIC     R0, R0, #IR_PIN
        STR     R0, [R1]

        ; Configure PA5 as GPIO
        LDR     R1, =GPIO_PORTA_PCTL_R
        LDR     R0, [R1]
        BIC     R0, R0, #(0xF << 20)
        STR     R0, [R1]

        ; Disable analog mode
        LDR     R1, =GPIO_PORTA_AMSEL_R
        LDR     R0, [R1]
        BIC     R0, R0, #IR_PIN
        STR     R0, [R1]

        ; Configure PA5 as input
        LDR     R1, =GPIO_PORTA_DIR_R
        LDR     R0, [R1]
        BIC     R0, R0, #IR_PIN
        STR     R0, [R1]

        ; Enable digital function
        LDR     R1, =GPIO_PORTA_DEN_R
        LDR     R0, [R1]
        ORR     R0, R0, #IR_PIN
        STR     R0, [R1]

        BX      LR

;============================================================
; Read rear IR sensor
;
; Returns:
;     R0 = 0x20 if PA5 HIGH
;     R0 = 0x00 if PA5 LOW
;============================================================

TAIL_sense

        LDR     R1, =GPIO_PORTA_DATA_R
        LDR     R0, [R1]
        AND     R0, R0, #IR_PIN
        BX      LR

        ALIGN
        END
