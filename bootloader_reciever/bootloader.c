/*
 * bootloader.c
 *
 *  Created on: Sep 20, 2023
 *      Author: Ahned2XD
 */
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
#include "bootloader.h"
#include "can.h"


#define CMD_UPDATE 0x13


uint32_t myData=0;/*{0x20000200,  0x000204E7, 0x000204ED, 0x000204EF, 0x000204F1, 0x000204F1, 0x000204F1, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000204F1, 0x000204F1, 0x00000000, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1,
                   0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1,
                   0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x00000000, 0x00000000, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1,
                   0x000204F1, 0x000204F1, 0x000204F1, 0x00000000, 0x00000000, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1,
                   0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000204F1, 0x000204F1, 0x000204F1,
                   0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x00000000, 0x00000000, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x00000000, 0x00000000, 0x000204F1, 0x000204F1,
                   0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x000204F1, 0x47F0E92D, 0x461F4684,
                   0xF8DF4856, 0xF8DF9154, 0x68038158, 0x0303EA09, 0xD01B4598, 0xF04F2400, 0xF04F0A01, 0xFA0A0E03, 0x4219F304, 0xF8DCD00F, 0x00663FC4, 0xF506FA0E, 0xF8CC43AB, 0xF8DC3FC4, 0xF3C25FC4, 0x40B31341, 0xF8CC432B, 0x1C643FC4, 0xDBE82C08, 0xBF270853, 0x3500F8DC, 0xF8DC430B, 0x438B3500,
                   0x3500F8CC, 0xBF270893, 0x3504F8DC, 0xF8DC430B, 0x438B3504, 0x3504F8CC, 0xBF2708D3, 0x3508F8DC, 0xF8DC430B, 0x438B3508, 0x3508F8CC, 0xBF270913, 0x3518F8DC, 0xF8DC430B, 0x438B3518, 0x3518F8CC, 0x464C6803, 0x40234645, 0xD009429D, 0xBF270952, 0x253CF8DC, 0xF8DC430A, 0x438A253C,
                   0x253CF8CC, 0xBF27087A, 0x250CF8DC, 0xF8DC430A, 0x438A250C, 0x250CF8CC, 0xBF2708BA, 0x2510F8DC, 0xF8DC430A, 0x438A2510, 0x2510F8CC, 0xBF2708FA, 0x2514F8DC, 0xF8DC430A, 0x438A2514, 0x2514F8CC, 0xBF27093A, 0x251CF8DC, 0xF8DC430A, 0x438A251C, 0x251CF8CC, 0x40046800, 0xD01442A5,
                   0xBF270AB8, 0x0544F8DC, 0xF8DC4308, 0x43880544, 0x7F40F417, 0x0544F8CC, 0xF8DCBF19, 0x43080540, 0x0540F8DC, 0xF8CC4388, 0x2F000540, 0xF8DCBF19, 0xEA200528, 0xF8DC0101, 0x43010528, 0x1528F8CC, 0x87F0E8BD, 0x70FF0000, 0x400FE000, 0x10050000, 0x4815B50E, 0xF830F000, 0x210E4814,
                   0xF872F000, 0x210E4812, 0xF0002200, 0x4811F880, 0xF8AD8800, 0x20000000, 0x0004F88D, 0x0004F89D, 0x71D0EB00, 0x0101F021, 0xF88D1A40, 0xF89D0004, 0xF8100004, 0x1C41200D, 0xF88D4805, 0x210E1004, 0xF865F000, 0xF0004804, 0xE7E7F865, 0xF0000805, 0x40025000, 0x00020506, 0x004C4B40,
                   0x08C14A0B, 0x2307F3C0, 0x51FFF401, 0x00FFF000, 0x3150F5A1, 0xF02118D2, 0x0F12417E, 0x7102EA41, 0xEA412201, 0xF0410180, 0x60027000, 0x46C04770, 0x400FE600, 0xBF270853, 0x3400F8D0, 0xF8D0430B, 0x438B3400, 0xF8C00892, 0xBF273400, 0x2420F8D0, 0xF8D04311, 0xEA222420, 0xF8C00101,
                   0x47701420, 0xF3804808, 0x49088808, 0xF4406808, 0x60080070, 0xBF00BF00, 0xF823F000, 0xF7FF2000, 0x2001FF8D, 0xF81FF000, 0x20000200, 0xE000ED88, 0x2201B538, 0x4605460C, 0xF7FF2308, 0x2201FEC9, 0x46284621, 0xFFC8F7FF, 0xF7FFBD38, 0x4770BFDB, 0xE7FEE7FE, 0xF840E7FE, 0x47702021,
                   0xD1FD1E40, 0x20014770, 0xBF004770, 0x0008E7FE};*/


uint8_t dummy_image_0[3000];
uint32_t dummy_image_1[5000];




bool TimerOverFlowFlag = false;
volatile bool g_bRXFlag = 0;
volatile bool g_bErrFlag = 0;


void jump_to_app(uint32_t address) {
    // disable interrupts
    IntMasterDisable();
    // redirect the vector table
    HWREG(NVIC_VTABLE) = address;
    //jump(address);
    // Load the stack pointer from the application's vector table.
    __asm(" ldr r1, [r0, #0]\n"
          " mov sp, r1\n");
    // Load the initial PC from the application's vector table and branch to
    // the application's entry point.
    __asm(" ldr r0, [r0, #4]\n"
          " blx r0\n");
}


void check_update(uint32_t waitMelliSeconds){

    /*wait for some time for any thing from uart*/
    start_timer_ms(waitMelliSeconds);

    UARTprintf("Waiting for code to start flashing\n\r");

    while(!TimerOverFlowFlag)
    {
        /*read data from Uart*/

        /* Check if data is available to read */



        if (g_bRXFlag)
        {
            /* Read and process incoming data */
            uint32_t receivedChar = Recieve_word(3);
            /* Check if the received character is the update command*/
            if((receivedChar == CMD_UPDATE))
            {
                /*Send ok and start update process*/
                UARTprintf("Start flashing \n\r");
                update();
                break;
            }
            else{
                UARTprintf("Wrong Start command\n\r");
            }
        }
    }
    TimerOverFlowFlag =false;

}




void update(void){




    /*get current flag value if any*/
    uint32_t* flag_pointer =  (uint32_t*)FLAG_APP_START;
    uint32_t temp = flag_pointer[0] + 1;
    uint32_t address;

    /*make sure it doesn't exceed 1*/
    temp %= 2;
    /*depending of the flag value check which address & data we will write to*/
    if(temp == 0){

        address = APP_START_1;
    }else{
        address = APP_START_2;
    }

    /*read size of the array*/
    uint32_t size_of_data = Recieve_word(1);
    UARTprintf("Code to Flash size : %d\n\r" , size_of_data);

    /*init flash with the required size per block 1k*/
    uint16_t block =0;

    for(block = 0 ; block < size_of_data/1024 ; block++)
    {
        FlashErase(address+block*1024);
    }

    /*get data from pc*/
//    uint32_t dataCount =0;

    UARTprintf("Flashing > ");
    Recieve_word_arr(2, dummy_image_1, size_of_data);


    /*convert u8 to u32*/

    FlashProgram(dummy_image_1,address ,size_of_data);


    UARTprintf("Finished flashing code \n\r");
    /*write flag*/
    FlashErase(FLAG_APP_START);

    FlashProgram(&temp,FLAG_APP_START,sizeof(temp));

}
