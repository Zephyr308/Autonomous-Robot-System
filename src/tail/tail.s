GPIO_PORTA_DIR_R   EQU 0x40004400
GPIO_PORTA_DEN_R   EQU 0x4000451C
SYSCTL_RCGCGPIO_R  EQU 0x400FE608
GPIO_PORTA_DATA_R  EQU 0x400043FC

        AREA |.text|, CODE, READONLY
        THUMB
        EXPORT TAIL_Init
        EXPORT TAIL_Read

TAIL_Init
        LDR R1, =SYSCTL_RCGCGPIO_R
        LDR R0, [R1]
        ORR R0, R0, #1
        STR R0, [R1]

        LDR R1, =GPIO_PORTA_DIR_R
        LDR R0, [R1]
        BIC R0, R0, #0x20
        STR R0, [R1]

        LDR R1, =GPIO_PORTA_DEN_R
        LDR R0, [R1]
        ORR R0, R0, #0x20
        STR R0, [R1]
        BX LR

TAIL_Read
        LDR R1, =GPIO_PORTA_DATA_R
        LDR R0, [R1]
        AND R0, R0, #0x20
        BX LR
        END
