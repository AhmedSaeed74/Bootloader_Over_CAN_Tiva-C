
/**
 * main.c
 */

#include <stdbool.h>
#include <stdint.h>
#include "Flash_can.h"
#include "uart_download.h"
#include "sender.h"

uint8_t dummy_image_0[15000];

uint8_t code_downloaded_flag;
/*recieved code size*/
extern uint16_t size ;
void main(void)
{
    init_timer();
    init_uart();
    sender_init();
    while(1)
    {
        /*check if there is an update pending*/
        check_download_request(20000);
        if(code_downloaded_flag){
            Download_array_to_can(dummy_image_0 , size);
            code_downloaded_flag= 0;
        }
    }
}
