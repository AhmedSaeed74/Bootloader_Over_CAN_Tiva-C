/*
 * can.h
 *
 *  Created on: Sep 23, 2023
 *      Author: lenovo
 */

#ifndef CAN_H_
#define CAN_H_


#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include <string.h>
#include "driverlib/can.h"
#include "inc/hw_can.h"



void
CANIntHandler(void);

void
init(void);


uint32_t Recieve_word(uint8_t MessageId);
extern tCANMsgObject sCANMessage;
void Recieve_word_arr(uint8_t MessageId , uint32_t * array , uint32_t size);


#endif /* CAN_H_ */
