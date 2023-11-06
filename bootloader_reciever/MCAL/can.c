//*****************************************************************************
//
// temperature_sensor.c - Example demonstrating the internal ADC temperature
//                        sensor.
//
// Copyright (c) 2010-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 2.1.0.12573 of the Tiva Firmware Development Package.
//
//*****************************************************************************
/*
 *  This code was made to show a simple ADC read.
 *
 *  It was made from the example provided by TivaWare but it was a some modifications
 * like the math
 *
 *
 * Luís Afonso
 *
 *
 */

#include "can.h"
#include "uart.h"


volatile uint32_t g_ui32MsgCount = 0;
extern volatile bool g_bRXFlag;
extern volatile bool g_bErrFlag;


tCANMsgObject sCANMessage;
uint8_t pui8MsgData[8];



/* This function is the interrupt handler for the CAN peripheral.  It checks
   for the cause of the interrupt, and maintains a count of all messages that
   have been transmitted.*/
void CANIntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
    if(ui32Status == CAN_INT_INTID_STATUS)
    {
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        g_bErrFlag = 1;
    }
    else if(ui32Status == 1)
    {
        CANIntClear(CAN0_BASE, 1);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2 , ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2));
        g_bRXFlag=1;
        g_bErrFlag = 0;
    }
    else
    {
        /*Do Nothing*/
    }
}



void
init_can(void)
{



    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB4_CAN0RX);
    GPIOPinConfigure(GPIO_PB5_CAN0TX);

    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

    CANInit(CAN0_BASE);

    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

    IntEnable(INT_CAN0);
    CANEnable(CAN0_BASE);
    CANIntRegister(CAN0_BASE, CANIntHandler);


    sCANMessage.ui32MsgID = 0;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage.ui32MsgLen = sizeof(uint32_t);


    CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_RX);

}

uint8_t data[8] = {0};
uint32_t Recieve_word(uint8_t MessageId)
{

    uint32_t Recived_data = 0;
    while(!g_bRXFlag);
    sCANMessage.pui8MsgData = data;
    CANMessageGet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_RX);
    if(sCANMessage.ui32MsgID == MessageId)
    {
        Recived_data = *((uint32_t*)(data));
        g_bRXFlag = 0;
        return Recived_data;

    }
    else{
        /*Do Nothing*/
    }
    g_bRXFlag = 0;
    //it shouldn't reach here
    return 0;
}


void Recieve_word_arr(uint8_t MessageId , uint32_t * array , uint32_t size)
{

    //uint32_t Recived_data = 0;
    uint32_t dataCount =0;
    while(dataCount < size/4){

        if(g_bRXFlag)
        {

            sCANMessage.pui8MsgData = data;
            CANMessageGet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_RX);
            if(sCANMessage.ui32MsgID == MessageId)
            {
                array[dataCount] = *((uint32_t*)(data));
                dataCount++;
                if(!(dataCount % 50)){
                    UARTCharPut(UART0_BASE, '.');
                }

            }
            else{
                /*Do Nothing*/
            }
            g_bRXFlag = 0;

        }

    }
}
