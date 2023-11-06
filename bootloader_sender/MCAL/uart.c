/*
 * uart.c
 *
 *  Created on: Sep 20, 2023
 *      Author: Ahned2XD
 */

#include "uart.h"

/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   UART_API.c                                                   *
 *                                                                             *
 * [AUTHORS]:     Ahmed Saeed, Amr Gafar, Kareem Abd-elrasheed,                *
 *                Mohamed Abosreea, Ahmed Maher, and Mohamed Ramadan           *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        03/09/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: source file for UART APIs                                    *
 *                                                                             *
 *******************************************************************************/

/*******************************************************************************
 *                      Functions definitions                                  *
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
void init_uart(void)
{
    /* Enable UART0 peripheral */
    SysCtlPeripheralEnable((uint32_t)UART0_PERIPH);

    /* Enable GPIOA peripheral (UART0 pins) */
    SysCtlPeripheralEnable((uint32_t)UART0_GPIO_PERIPH);

    /* Configure UART0 pins (PA0 as UART0 Rx, PA1 as UART0 Tx) */
    GPIOPinConfigure((uint32_t)GPIO_PA0_U0RX);
    GPIOPinConfigure((uint32_t)GPIO_PA1_U0TX);
    GPIOPinTypeUART((uint32_t)UART0_GPIO_BASE, (uint8_t)UART0_RX_PIN | (uint8_t)UART0_TX_PIN);

    /* Initialize UART0 module */
    UARTConfigSetExpClk((uint32_t)UART0_MODULE, (uint32_t)SysCtlClockGet(), (uint32_t)115200, ((uint32_t)UART_CONFIG_WLEN_8 | (uint32_t)UART_CONFIG_STOP_ONE | (uint32_t)UART_CONFIG_PAR_NONE));

    /* Enable UART0 module */
    UARTEnable((uint32_t)UART0_MODULE);


}


/*
 * Description :
 * This function sends a text message over UART
 * communication by taking a null-terminated
 * string as input then iterating through each
 * character in the string.
 * Parameters: text-> The null-terminated string to be transmitted over UART.
 * Returns: None.
 */
void UARTprint(const char* text)
{
    uint16_t k;

    for(k = 0U ; k < strlen(text) ; k++)
    {
        /* Send the message character by character till
         * reaching the null terminator */
        UARTCharPut((uint32_t)UART0_MODULE, (uint8_t)(text[k]));
    }

}




