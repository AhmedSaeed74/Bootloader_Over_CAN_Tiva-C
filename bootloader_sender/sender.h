/*
 * sender.h
 *
 *  Created on: Sep 29, 2023
 *      Author: Mohamed Abosreea
 */

#ifndef SENDER_H_
#define SENDER_H_

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/can.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"

void sender_init(void);

void send_message(uint8_t id , uint8_t  *data);

void CANIntHandler(void);


#endif /* SENDER_H_ */
