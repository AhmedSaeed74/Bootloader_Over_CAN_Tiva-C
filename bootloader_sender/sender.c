/*
 * sender.c
 *
 *  Created on: Sep 29, 2023
 *      Author: Mohamed Abosreea
 */
#include "sender.h"


volatile uint32_t g_ui32MsgCount = 0;
volatile bool g_bErrFlag = 0;

void sender_init(void)
{
    /*Set system closk*/
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
    /* enable clock for port b*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    /* enable clock for port f*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    /* set green led as output pin*/
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    /* configure alternative function of pin B4 to run as can rx*/
    GPIOPinConfigure(GPIO_PB4_CAN0RX);

    /* configure alternative function of pin B4 to run as can tx*/
    GPIOPinConfigure(GPIO_PB5_CAN0TX);

    /* configure alternative function of pin B4 , B5 to run as can */
    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    /* enable can0 module clock*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

    /* initialize can */
    CANInit(CAN0_BASE);

    /* set clock speed of can*/
    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);

    /* configure can0 interrupt */
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

    /* enable can0 interrupt */
    IntEnable(INT_CAN0);

    /* enable can module*/
    CANEnable(CAN0_BASE);
}

void send_message(uint8_t id , uint8_t *data)
{
    /*create can message object that contains message information */
    tCANMsgObject sCANMessage;

    /* array to hold sent data*/
    uint8_t *pui8MsgData;

    /* set MSG ID Mask to 0 to accept all messages in case of receiving */
    sCANMessage.ui32MsgIDMask = 0;

    /* set can flags to give interrupt when transmission completes*/
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;

    /* set message id length to  4 byte */
    sCANMessage.ui32MsgLen = 4 * sizeof(uint8_t) ;

    /* set message id */
    sCANMessage.ui32MsgID = id;

    /* assign data to the array */
    pui8MsgData = data;

    /* assign array to message array*/
    sCANMessage.pui8MsgData = pui8MsgData;

    /* send message over can bus */
    CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);

    /* delay 10 ms after transmission*/
    SysCtlDelay(16000000 / 300);
}

void CANIntHandler(void)
{
    uint32_t ui32Status;

    /* get status of can module*/
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);


    if(ui32Status == CAN_INT_INTID_STATUS)
    {
        /* set error status flag in case of can bus error*/
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        g_bErrFlag = 1;
    }
    else if(ui32Status == 1)
    {
        /* set flag in case of success transmission then clear can interrupt flag*/
        CANIntClear(CAN0_BASE, 1);

        /* toggle green led as indication for successful transmission*/
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 , ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3));

        /* message counts */
        g_ui32MsgCount++;

        /* clear error flag*/
        g_bErrFlag = 0;
    }
    else
    {
        /*Do Nothing*/
    }
}




