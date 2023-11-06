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
    // Enable GPIO port A which is used for UART0 pins.
       // TODO: change this to whichever GPIO port you are using.
       //
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

       //
       // Configure the pin muxing for UART0 functions on port A0 and A1.
       // This step is not necessary if your part does not support pin muxing.
       // TODO: change this to select the port/pin you are using.
       //
       GPIOPinConfigure(GPIO_PA0_U0RX);
       GPIOPinConfigure(GPIO_PA1_U0TX);

       //
       // Enable UART0 so that we can configure the clock.
       //
       SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

       //
       // Use the internal 16MHz oscillator as the UART clock source.
       //
       UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

       //
       // Select the alternate (UART) function for these pins.
       // TODO: change this to select the port/pin you are using.
       //
       GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

       //
       // Initialize the UART for console I/O.
       //
       UARTStdioConfig(0, 115200, 16000000);




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




