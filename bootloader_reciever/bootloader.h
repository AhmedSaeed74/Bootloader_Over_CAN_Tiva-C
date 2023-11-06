/*
 * bootloader.h
 *
 *  Created on: Sep 20, 2023
 *      Author: Ahned2XD
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

//*****************************************************************************
//
// Includes
//
//*****************************************************************************



//*****************************************************************************
//
// Section : Macro declarations.
//
//*****************************************************************************
#define APP_START_1 0x30000
#define APP_START_2 0x20000
#define FLAG_APP_START 0x10000



//*****************************************************************************
//
//  Section : Macro Functions declarations
//
//*****************************************************************************

#define jump(ADDRESS) ((void (*)(void))(*(int *)(ADDRESS+4)))()

//*****************************************************************************
//
//   Section : Data types declaration
//
//*****************************************************************************



//*****************************************************************************
//
//   Section : Functions declarations
//
//*****************************************************************************


/**
 * This function is used to jump to specific address in flash
 * @param address 32bit address of where to jump
 */

void jump_to_app(uint32_t address);

/**
 * This function is used to check if there is an update bending or not
 *
 */
void check_update(uint32_t waitMelliSeconds);

/**
 * This function is used to download data from uart and burn it on flash
 *
 */
void update (void);


#endif /* BOOTLOADER_H_ */
