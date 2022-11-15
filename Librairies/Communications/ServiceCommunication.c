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
/**
 * @brief Struct containing all the possible states that a module can have.
 * This is a list of states and must not be changed, but only referred to.
 */
stModes Modes;
/**
 * @brief Struct containing all the possible states that a module can have.
 * This is a list of states and must not be changed, but only referred to.
 */
stStates States;
/**
 * @brief Struct containing all the possible commands that a module can have.
 * This is a list of commands and must not be changed, but only referred to.
 */
stCommands Commands;
/**
 * @brief Struct containing all the possible values that a module can transmit.
 * This is a list of values and must not be changed, Only refer to it when you
 * need to set or change your module's structure values.
 */
stValues Values;
/**
 * @brief The actual structure used by the module. Used to get/set different
 * values and commands. For example, reading the Mode that the master sent.
 * Checking if receiving info from the CAN etc. Use DEFINES present in this
 * file in order to set Commands or values of such.
 */
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
/******************************************************************************
* @brief Function handling the count of interrupts and slot allocations for
* CAN communications made for this project. It is important to properly
* define clock speeds and oscillator speeds in ServiceCommunication.h
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param void
*/
void Count_Interrupts(void);
/******************************************************************************
* @brief Private function checking if a variable is equal to UNUSED. If not, it
* sets it to a new value.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param void
*/
void CheckIfUnused(unsigned char *checkedValue, unsigned char wantedNewValue)
{
    if(*checkedValue != UNUSED) {*checkedValue = wantedNewValue;}
}
#pragma endregion PRIVATE_FUNCTIONS


//#############################################################################
#pragma region PUBLIC_FUNCTIONS_CODE
//-----------------------------------------------------------------------------
/******************************************************************************
* @brief Sets the received command structure (ModuleData.CommandsReceived) to
* the same input value. Useful to reset any received commands when a new mode
* has been received from the master.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to UNUSED
*/
void ModuleData_SetAll_ReceivedCommands(unsigned char ValueAppliedToAll)
{
    CheckIfUnused(&ModuleData.CommandsReceived.discharge, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.goto_SortingStation, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.goto_WeightStation, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.light_A_OFF, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.light_A_ON, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.light_B_OFF, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.light_B_ON, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.light_C_OFF, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.light_C_ON, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.light_D_OFF, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.light_D_ON, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.move_left, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.move_right, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.move_forward, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.move_backward, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.move_up, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.move_down, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.start_Sorting, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.start_Weighting, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.suction_OFF, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.suction_ON, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.units_Imperial, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsReceived.units_Metric, ValueAppliedToAll);
}
/******************************************************************************
* @brief Sets the queued command structure (ModuleData.CommandsToSend) to
* the same input value. Useful to reset any queued commands when a new mode
* has been received from the master.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to UNUSED
*/
void ModuleData_SetAll_SentCommands(unsigned char ValueAppliedToAll)
{
    CheckIfUnused(&ModuleData.CommandsToSend.discharge, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.goto_SortingStation, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.goto_WeightStation, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.light_A_OFF, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.light_A_ON, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.light_B_OFF, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.light_B_ON, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.light_C_OFF, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.light_C_ON, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.light_D_OFF, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.light_D_ON, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.move_left, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.move_right, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.move_forward, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.move_backward, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.move_up, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.move_down, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.start_Sorting, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.start_Weighting, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.suction_OFF, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.suction_ON, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.units_Imperial, ValueAppliedToAll);
    CheckIfUnused(&ModuleData.CommandsToSend.units_Metric, ValueAppliedToAll);
}
/******************************************************************************
* @brief Function periodically called via the time base's interruptions. It is
* important to allocate a buffer address in your time base for this function.
* Do this via your main.h file, and ServiceCommunication.h.
* You will need to set SCOMMS_PARSE_RX_BUFFER_ADR to the appropriated number
* in your buffer.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param void Time base functions take no parameters
*/
void ServiceCommunication_RXParsingHandler(void)
{

}
/******************************************************************************
* @brief Function periodically called via the time base's interruptions. It is
* important to allocate a buffer address in your time base for this function.
* Do this via your main.h file, and ServiceCommunication.h.
* You will need to set SCOMMS_PARSE_TX_BUFFER_ADR to the appropriated number
* in your buffer.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param void Time base functions take no parameters
*/
void ServiceCommunication_TXParsingHandler(void)
{

}
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

    //Initialization of ModuleData. This will change depending on your module.
    ModuleData_SetAll_ReceivedCommands(NO_DATA);
    ModuleData_SetAll_SentCommands(AVAILABLE);
}
//-----------------------------------------------------------------------------
#pragma endregion PUBLIC_FUNCTIONS_CODE




/*
int main(void)
{
    printf("%i",ModuleData.CommandsToSend.discharge);
    CheckIfUnused(&ModuleData.CommandsToSend.discharge,7);
    return 0;
}
*/