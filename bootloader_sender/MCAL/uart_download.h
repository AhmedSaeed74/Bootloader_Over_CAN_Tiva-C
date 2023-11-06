/*
 * bootloader.h
 *
 *  Created on: Sep 20, 2023
 *      Author: Ahned2XD
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

//*****************************************************************************
//
// Includes
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/flash.h"
#include "driverlib/interrupt.h"
#include "timer.h"
#include "uart.h"

//*****************************************************************************
//
// Section : Macro declarations.
//
//*****************************************************************************


#define APP_START_1 0x20000
#define APP_START_2 0x22000
#define FLAG_APP_START 0x10000
#define CMD_UPDATE 0x13

//*****************************************************************************
//
//  Section : Macro Functions declarations
//
//*****************************************************************************

#define jump(ADDRESS) ((void (*)(void))(*(int *)(ADDRESS+4)))()

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
 * This function is used to check if there is an update bending or not
 *
 */
void check_download_request(uint32_t waitMelliSeconds);

/**
 * This function is used to download data from uart and burn it on flash
 *
 */
void update (void);


#endif /* BOOTLOADER_H_ */
