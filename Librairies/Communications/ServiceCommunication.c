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
//#include "main.h"
#include "ServiceCommunication.h"
#include <stdio.h>
//#include "serviceBaseDeTemps.h"
//#include "piloteCAN1.h"
#pragma endregion INCLUDES
//#############################################################################
#pragma region STRUCTURES
/** @brief Declaration of the Modes structure defined in ServiceCommunication.h */
stModes Modes;
/** @brief Declaration of the States structure defined in ServiceCommunication.h */
stStates States;
/** @brief Declaration of the Commands structure defined in ServiceCommunication.h */
stCommands Commands;
/** @brief Declaration of the Value structure defined in ServiceCommunication.h */
stValues Values;
/** @brief Declaration of the ModuleData structure defined in ServiceCommunication.h */
stModuleData ModuleData;
#pragma endregion STRUCTURES
//#############################################################################
#pragma region PRIVATE_FUNCTIONS
//-----------------------------------------------------------------------------
/******************************************************************************
* @brief Parsing function decorticating structures into 8 bytes CAN data to be
* sent later.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param Buffer Pointer pointing the address of an 8 bytes unsigned char array.
*/
void Parse_CanBusTransmission(unsigned char *Buffer);
/******************************************************************************
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
/******************************************************************************
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
/******************************************************************************
* @brief Function called which initialises all the structures necessary. it is
* important to call this function before main execution of the program starts
* as it is necessary to initialise all the data structure used by this service.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param void Initialisation functions take no parameters
*/
void ServiceCommunication_initialise(void)
{
    // Initialisation of reference structure values (DO NOT CHANGE THESE)
    Modes.emergencyStop                = 0x00;
    Modes.pause                        = 0x01;
    Modes.testing                      = 0x02;
    Modes.maintenance                  = 0x03;
    Modes.operation                    = 0x04;
    Modes.calibration                  = 0x05;
    Modes.reinitialisation             = 0x06;

    States.emergencyStop               = 0x00;
    States.paused                      = 0x01;
    States.testing                     = 0x02;
    States.processing                  = 0x03;
    // RESERVED                        = 0x04;
    States.calibrating                 = 0x05;
    States.calibrated                  = 0x06;
    States.waiting                     = 0x07;
    States.safe                        = 0x08;
    States.error                       = 0x09;
    States.atSortingFactory            = 0x0A;
    States.atWeightStation             = 0x0B;
    States.finishedSortingAndHasLoaded = 0x0C;
    States.waitingToSort               = 0x0D;
    States.waitingToWeight             = 0x0E;
    States.finishedWeighting           = 0x0F;
    States.empty                       = 0x10;

    Commands.move_left                 = 0x00;
    Commands.move_right                = 0x01;
    Commands.move_forward              = 0x02;
    Commands.move_backward             = 0x03;
    Commands.move_up                   = 0x04;
    Commands.move_down                 = 0x05;
    Commands.suction_ON                = 0x06;
    Commands.suction_OFF               = 0x07;
    Commands.light_A_ON                = 0x08;
    Commands.light_A_OFF               = 0x09;
    Commands.light_B_ON                = 0x0A;
    Commands.light_B_OFF               = 0x0B;
    Commands.light_C_ON                = 0x0C;
    Commands.light_C_OFF               = 0x0D;
    Commands.light_D_ON                = 0x0E;
    Commands.light_D_OFF               = 0x0F;
    Commands.goto_SortingStation       = 0x10;
    Commands.goto_WeightStation        = 0x11;
    Commands.start_Sorting             = 0x12;
    Commands.start_Weighting           = 0x13;
    Commands.discharge                 = 0x14;
    // RESERVED                        = 0x15;
    Commands.units_Metric              = 0x16;
    Commands.units_Imperial            = 0x17;

    Values.disc_Red                    = 0x00;
    Values.disc_Silver                 = 0x01;
    Values.disc_Black                  = 0x02;
    Values.disc_NoColor                = 0x03;
    Values.disc_Detected               = 0x04;
    Values.disc_Lost                   = 0x05;
    Values.disc_CouldNotBeFound        = 0x06;
    Values.unit_Metric                 = 0x07;
    Values.unit_Imperial               = 0x08;
}
//-----------------------------------------------------------------------------
#pragma endregion PUBLIC_FUNCTIONS_CODE





int main(void)
{

    return 0;
}