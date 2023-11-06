

#include "timer.h"

//*****************************************************************************
//
// This is a flag that gets set in the interrupt handler to indicate that an
// interrupt occurred.
//
//*****************************************************************************
extern bool TimerOverFlowFlag;


//*****************************************************************************
//
// The interrupt handler for the for Timer0B interrupt.
//
//*****************************************************************************
void
Timer0AIntHandler(void)
{
    //
    // Clear the timer interrupt flag.
    //
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Set a flag to indicate that the interrupt occurred.
    //
    TimerOverFlowFlag = true;
}

//*****************************************************************************
//
// Configure Timer0 as a 16-bit one-shot counter with a single interrupt
// after (x) ms.
//
//*****************************************************************************
void init_timer (void)
{

    //
    // The Timer0 peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);


    //
    // The Timer0 peripheral must be enabled for use.
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);


}

void start_timer_ms(uint32_t ms)
{
    //
    // Enable processor interrupts.
    //
    IntMasterEnable();
    //
    // Set the Timer0 load value to  x ms.
    //
    TimerLoadSet(TIMER0_BASE, TIMER_BOTH, (SysCtlClockGet() / 1000) * ms );

    //
    // Configure the Timer0B interrupt for timer timeout.
    //
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0AIntHandler);    // Registering  isr


    //
    // Enable the Timer0B interrupt on the processor (NVIC).
    //
    IntEnable(INT_TIMER0A);

    //
    // Enable Timer0A.
    //
    TimerEnable(TIMER0_BASE, TIMER_BOTH);
    //
    // Configure the Timer0B interrupt for timer timeout.
    //
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}
