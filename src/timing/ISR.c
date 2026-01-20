void TIMER2A_Handler(void)
{
    TIMER2->ICR = 1;
    TIMING_Tick();
}
