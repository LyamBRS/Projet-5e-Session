//#############################################################################
/**
 * @file ServiceCommunication.c
 * @author Lyam / Shawn Couture (cous5830@gmail.com)
 * @brief
 * Program file containing the code defined in ServiceCommunication.h
 * Please refer to this other file for information necessary in order to make this work.
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//#############################################################################

//#############################################################################
#pragma region INCLUDES
//-----------------------------------------------------------------------------
#include "main.h"
#include "ServiceCommunication.h"
#include "serviceBaseDeTemps.h"
#include "piloteCAN1.h"
#pragma endregion INCLUDES

//#############################################################################
#pragma region PRIVATE_FUNCTIONS
//-----------------------------------------------------------------------------
/**
* @brief Parsing function decorticating structures into 8 bytes CAN data to be
* sent later.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param Buffer Pointer pointing the address of an 8 bytes unsigned char array.
*/
void Parse_CanBusTransmission(unsigned char *Buffer);
/**
* @brief Parsing function decorticating an 8 bytes array into the service's
* structures.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param Buffer Pointer pointing the address of an 8 bytes unsigned char array.
*/
void Parse_CanBusReceptions(unsigned char *Buffer);

void Count_Interrupts(void);
#pragma endregion PRIVATE_FUNCTIONS


//#############################################################################
#pragma region PUBLIC_FUNCTIONS_CODE
//-----------------------------------------------------------------------------
/**
* @brief Function periodically called via the time  base's interrupt function 
* pointers buffer.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param void Time base functions take no parameters
*/
void ServiceCommunication_Handler(void)
{

}
//-----------------------------------------------------------------------------
/**
* @brief Function called which initialises all the structures necessary.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param void Initialisation functions take no parameters
*/
void ServiceCommunication_initialise(void)
{
    /**
     * @brief 
     * 
     */
}
//-----------------------------------------------------------------------------
#pragma endregion PUBLIC_FUNCTIONS_CODE