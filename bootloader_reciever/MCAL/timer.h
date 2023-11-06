/*
 * timer.h
 *
 *  Created on: Sep 20, 2023
 *      Author: Ahned2XD
 */

#ifndef TIMER_H_
#define TIMER_H_



//*****************************************************************************
//
// Includes
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "timer.h"

//*****************************************************************************
//
// Section : Macro declarations.
//
//*****************************************************************************



//*****************************************************************************
//
//  Section : Macro Functions declarations
//
//*****************************************************************************



//*****************************************************************************
//
//   Section : Data types declaration
//
//*****************************************************************************



//*****************************************************************************
//
//   Section : Functions declarations
//
//*****************************************************************************


/**
 * Timer interrupt handler just raise a flag when timer overflows
 */

void Timer0AIntHandler(void);

/**
 * Timer0 initialize
 *
 */
void init_timer (void);

/**
 * start timer0 with the loaded ms value
 * @param ms -> how many melliseconds to wait
 */
void start_timer_ms(uint32_t ms);

#endif /* TIMER_H_ */
