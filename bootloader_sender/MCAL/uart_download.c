/*
 * uart_download.c
 *
 *  Created on: Sep 30, 2023
 *      Author: GPU_Tech
 */


/*
 * bootloader.c
 *
 *  Created on: Sep 20, 2023
 *      Author: Ahned2XD
 */
#include "uart_download.h"




extern uint8_t dummy_image_0[];



extern uint8_t code_downloaded_flag;
bool TimerOverFlowFlag = false;

void check_download_request(uint32_t waitMelliSeconds){


    /*wait for some time for any thing from uart*/
    start_timer_ms(waitMelliSeconds);

    while(!TimerOverFlowFlag)
    {
        /*read data from Uart*/

        /* Check if data is available to read */
        if (UARTCharsAvail((uint32_t)UART0_BASE))
        {
            /* Read and process incoming data */
            uint32_t receivedChar = UARTCharGet((uint32_t)UART0_BASE);


            /* Check if the received character is the update command*/
            if((receivedChar == CMD_UPDATE))
            {
                /*Send ok and start update process*/
                UARTprint("ok\n");
                update();
                break;
            }
            else{
                UARTprint("press 5 to start flashing ?\n");
            }
        }
    }
    TimerOverFlowFlag =false;

}


uint16_t size = 0;

void update(void){


    /*read size of the array*/
    uint8_t size_arr[2];
    uint8_t idx = 0;
    while(!UARTCharsAvail(UART0_BASE));
    for(idx = 0 ; idx < 2 ; idx++)
    {
        //
        // Get the data received by the UART at its receive FIFO
        // vc
        size_arr[idx] = UARTCharGet(UART0_BASE);
    }

    /*init flash with the required size per block 1k*/
     size= *((uint16_t *)(size_arr));

    /*get data from pc*/
    uint16_t dataCount =0;
        for(dataCount=0;dataCount<size;dataCount++)
        {
            dummy_image_0[dataCount] =  UARTCharGet((uint32_t)UART0_BASE);
        }

        code_downloaded_flag= 1;
}
