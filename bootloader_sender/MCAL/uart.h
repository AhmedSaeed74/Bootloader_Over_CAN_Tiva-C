/*
 * uart.h
 *
 *  Created on: Sep 20, 2023
 *      Author: Ahned2XD
 */

#ifndef UART_H_
#define UART_H_



/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* UART0 configuration */
#define UART0_MODULE UART0_BASE
#define UART0_PERIPH SYSCTL_PERIPH_UART0
#define UART0_GPIO_PERIPH SYSCTL_PERIPH_GPIOA
#define UART0_GPIO_BASE GPIO_PORTA_BASE
#define UART0_TX_PIN GPIO_PIN_1
#define UART0_RX_PIN GPIO_PIN_0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * This function initializes the UART module, sets up
 * the necessary GPIO pins for UART communication, and
 * establishes communication parameters including the baud rate,
 * data frame format, and parity settings.
 * Parameters: None.
 * Returns: None.
 */
void init_uart(void);

/*
 * Description :
 * This function sends a text message over UART
 * communication by taking a null-terminated
 * string as input then iterating through each
 * character in the string.
 * Parameters: text-> The null-terminated string to be transmitted over UART.
 * Returns: None.
 */
void UARTprint(const char* text);


#endif /* UART_H_ */
