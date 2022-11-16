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
#pragma region EXTERN_DECLARATIONS
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
/**
 * @brief Global extern variable which purpose is to indicate to other portions
 * of the code which state this library is currently in. See:\n
 * \ref NO_ERROR .\n
 * \ref ERROR_RX_MODE_DOESNT_EXIST .\n
 * \ref ERROR_RX_STATE_DOESNT_EXIST .\n
 * \ref ERROR_RX_COMMAND_DOESNT_EXIST .\n
 * \ref ERROR_RX_VALUE_DOESNT_EXIST .\n
 * \ref ERROR_TIMEDOUT .\n
 * \ref ERROR_SPECIFIC_TO_MODULE .\n
 */
unsigned char serviceCommunication_ErrorState = NO_ERROR;
#pragma endregion EXTERN_DECLARATIONS
//#############################################################################
#pragma region PRIVATE_VARIABLES
/**
 * @brief Variable keeping track of the amount of interrupt which hapenned
 * since the reception of a \ref stModes by the synchronisation CAN tram.
 */
unsigned char interruptCount = 0;
/**
 * @brief Variable which indicates which slots in the CAN protocol the count
 * is current at. This is used to keep track of which person needs to
 * communicate next.\n
 * 0: Synchronisation\n
 * 1: Sorting center\n
 * 2: Weighting center\n
 * 3: Vehicule\n
 * 4: Reserved\n
 * 5: Reserved
 */
unsigned char currentSlot = 0;
#pragma endregion PRIVATE_VARIABLES
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
void Parse_CanBusTransmission(unsigned char *Buffer)
{

}
/**
* @brief Parsing function decorticating an 8 bytes array into the service's
* structures.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param Buffer Pointer pointing the address of an 8 bytes unsigned char array.
*/
void Parse_CanBusReceptions(unsigned char *Buffer)
{
    //############################################ LOCAL VARS
    static unsigned char oldReceivedMode;
    //############################################
    for(int i=0; i<8; i+=2)
    {
        switch(Buffer[i])
        {
            case('M'):
                        switch(Buffer[i+1])
                        {
                            // Don't forget you need to set your ModuleData.State yourself.
                            // This is done so that other modules can be fully sure that you
                            // successfully entered the desired mode.
                            case(0x00): ModuleData.Mode = Modes.emergencyStop;    break;
                            case(0x01): ModuleData.Mode = Modes.pause;            break;
                            case(0x02): ModuleData.Mode = Modes.testing;          break;
                            case(0x03): ModuleData.Mode = Modes.maintenance;      break;
                            case(0x04): ModuleData.Mode = Modes.operation;        break;
                            case(0x05): ModuleData.Mode = Modes.calibration;      break;
                            case(0x06): ModuleData.Mode = Modes.reinitialisation; break;
                            default:
                                        //If received mode matched nothing, an error occured.
                                        ModuleData.State = States.error;
                                        serviceCommunication_ErrorState = ERROR_RX_MODE_DOESNT_EXIST;
                            break;                  
                        }
                        // The mode changed from the previous one!
                        if(oldReceivedMode != ModuleData.Mode)
                        {
                            oldReceivedMode = ModuleData.Mode;
                            ModuleData_SetAll_ReceivedCommands(NO_DATA);
                            ModuleData_SetAll_StatesReceived(NO_DATA);
                            ModuleData_SetAll_StatesReceived(NO_DATA);
                        }

                        // Reset counts and slots indentifications
                        interruptCount = 0;
                        currentSlot = 0;
            break;
            case('C'):
                        switch(Buffer[i+1])
                        {
                            // Parsing of received commands in a CAN tram
                            case(0x00): ModuleData.CommandsReceived.move_left     = RECEIVED; break;
                            case(0x01): ModuleData.CommandsReceived.move_right    = RECEIVED; break;
                            case(0x02): ModuleData.CommandsReceived.move_forward  = RECEIVED; break;
                            case(0x03): ModuleData.CommandsReceived.move_backward = RECEIVED; break;
                            case(0x04): ModuleData.CommandsReceived.move_up       = RECEIVED; break;
                            case(0x05): ModuleData.CommandsReceived.move_down     = RECEIVED; break;

                            case(0x06): ModuleData.CommandsReceived.suction_ON    = RECEIVED; break;
                            case(0x07): ModuleData.CommandsReceived.suction_OFF   = RECEIVED; break;

                            case(0x08): ModuleData.CommandsReceived.light_A_ON    = RECEIVED; break;
                            case(0x09): ModuleData.CommandsReceived.light_A_OFF   = RECEIVED; break;
                            case(0x0A): ModuleData.CommandsReceived.light_B_ON    = RECEIVED; break;
                            case(0x0B): ModuleData.CommandsReceived.light_B_OFF   = RECEIVED; break;
                            case(0x0C): ModuleData.CommandsReceived.light_C_ON    = RECEIVED; break;
                            case(0x0D): ModuleData.CommandsReceived.light_C_OFF   = RECEIVED; break;
                            case(0x0E): ModuleData.CommandsReceived.light_D_ON    = RECEIVED; break;
                            case(0x0F): ModuleData.CommandsReceived.light_D_OFF   = RECEIVED; break;

                            case(0x10): ModuleData.CommandsReceived.goto_SortingStation = RECEIVED; break;
                            case(0x11): ModuleData.CommandsReceived.goto_WeightStation  = RECEIVED; break;

                            case(0x12): ModuleData.CommandsReceived.start_Sorting       = RECEIVED; break;
                            case(0x13): ModuleData.CommandsReceived.start_Weighting     = RECEIVED; break;

                            case(0x14): ModuleData.CommandsReceived.discharge           = RECEIVED; break;
                            case(0x16): ModuleData.CommandsReceived.units_Metric        = RECEIVED; break;
                            case(0x17): ModuleData.CommandsReceived.units_Imperial      = RECEIVED; break;
                            default:
                                        //If received mode matched nothing, an error occured.
                                        ModuleData.State = States.error;
                                        serviceCommunication_ErrorState = ERROR_RX_COMMAND_DOESNT_EXIST;
                            break;                  
                        }
            break;
            case('V'):
                        switch(Buffer[i+1])
                        {
                            // Parsing of received values in a CAN tram
                            case(0x00): ModuleData.ValuesReceived.disc_Red        = RECEIVED;
                                        ModuleData.ValuesReceived.disc_Black      = NO_DATA;
                                        ModuleData.ValuesReceived.disc_Silver     = NO_DATA;
                                        ModuleData.ValuesReceived.disc_NoColor    = NO_DATA;
                                        break;
                            case(0x01): ModuleData.ValuesReceived.disc_Silver     = RECEIVED;
                                        ModuleData.ValuesReceived.disc_Red        = NO_DATA;
                                        ModuleData.ValuesReceived.disc_Black      = NO_DATA;
                                        ModuleData.ValuesReceived.disc_NoColor    = NO_DATA;
                                        break;
                            case(0x02): ModuleData.ValuesReceived.disc_Black      = RECEIVED;
                                        ModuleData.ValuesReceived.disc_Red        = NO_DATA;
                                        ModuleData.ValuesReceived.disc_Silver     = NO_DATA;
                                        ModuleData.ValuesReceived.disc_NoColor    = NO_DATA;
                                        break;
                            case(0x03): ModuleData.ValuesReceived.disc_NoColor    = RECEIVED;
                                        ModuleData.ValuesReceived.disc_Red        = NO_DATA;
                                        ModuleData.ValuesReceived.disc_Silver     = NO_DATA;
                                        ModuleData.ValuesReceived.disc_Black      = NO_DATA;
                                        break;

                            case(0x04): ModuleData.ValuesReceived.disc_Detected        = RECEIVED;
                                        ModuleData.ValuesReceived.disc_Lost            = NO_DATA;
                                        ModuleData.ValuesReceived.disc_CouldNotBeFound = NO_DATA;
                                        break;
                            case(0x05): ModuleData.ValuesReceived.disc_Lost            = RECEIVED;
                                        ModuleData.ValuesReceived.disc_Detected        = NO_DATA;
                                        ModuleData.ValuesReceived.disc_CouldNotBeFound = NO_DATA;
                                        break;
                            case(0x06): ModuleData.ValuesReceived.disc_CouldNotBeFound = RECEIVED;
                                        ModuleData.ValuesReceived.disc_Detected        = NO_DATA;
                                        ModuleData.ValuesReceived.disc_Lost            = NO_DATA;
                                        break;

                            case(0x07): ModuleData.ValuesReceived.unit_Metric          = RECEIVED;
                                        ModuleData.ValuesReceived.unit_Imperial        = NO_DATA;
                                        break;
                            case(0x08): ModuleData.ValuesReceived.unit_Metric          = NO_DATA;
                                        ModuleData.ValuesReceived.unit_Imperial        = RECEIVED;
                                        break;
                            default:
                                        //If received mode matched nothing, an error occured.
                                        ModuleData.State = States.error;
                                        serviceCommunication_ErrorState = ERROR_RX_VALUE_DOESNT_EXIST;
                            break;                  
                        }
            break;
            case('S'):
                        switch(Buffer[i+1])
                        {
                            // Parsing of received states from the communicating module
                            case(0x00): ModuleData.StatesReceived.emergencyStop               = RECEIVED;
                                        // AUTOMATICALLY SWITCH TO EMERGENCY MODE WHEN A MODULE STATE SAYS IT'S IN THIS STATE
                                        if(ModuleData.Mode != Modes.emergencyStop)
                                        {
                                            ModuleData.Mode = Modes.emergencyStop;
                                        }
                            break;
                            case(0x01): ModuleData.StatesReceived.paused                      = RECEIVED; break;
                            case(0x02): ModuleData.StatesReceived.testing                     = RECEIVED; break;
                            case(0x03): ModuleData.StatesReceived.processing                  = RECEIVED; break;
                            case(0x04):                                                                   break;
                            case(0x05): ModuleData.StatesReceived.calibrating                 = RECEIVED; break;
                            case(0x06): ModuleData.StatesReceived.calibrated                  = RECEIVED; break;
                            case(0x07): ModuleData.StatesReceived.waiting                     = RECEIVED; break;
                            case(0x08): ModuleData.StatesReceived.safe                        = RECEIVED; break;
                            case(0x09): ModuleData.StatesReceived.error                       = RECEIVED; break;

                            case(0x0A): ModuleData.StatesReceived.atSortingFactory            = RECEIVED;
                                        ModuleData.StatesReceived.atWeightStation             = NO_DATA; 
                                        break;
                            case(0x0B): ModuleData.StatesReceived.atWeightStation             = RECEIVED;
                                        ModuleData.StatesReceived.atSortingFactory            = NO_DATA;
                                        break;
                            case(0x0C): ModuleData.StatesReceived.finishedSortingAndHasLoaded = RECEIVED; break;
                            case(0x0D): ModuleData.StatesReceived.waitingToSort               = RECEIVED; break;
                            case(0x0E): ModuleData.StatesReceived.waitingToWeight             = RECEIVED; break;
                            case(0x0F): ModuleData.StatesReceived.finishedWeighting           = RECEIVED; break;
                            case(0x10): ModuleData.StatesReceived.empty                       = RECEIVED; break;
                            default:
                                        //If received mode matched nothing, an error occured.
                                        ModuleData.State = States.error;
                                        serviceCommunication_ErrorState = ERROR_RX_STATE_DOESNT_EXIST;
                            break;                  
                        }
            break;
        }
    }
}
/**
* @brief Function handling the count of interrupts and slot allocations for
* CAN communications made for this project. It is important to properly
* define clock speeds and oscillator speeds in ServiceCommunication.h
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param void
*/
void Parse_Interrupts(void)
{
    
}
/**
* @brief Private function checking if a variable is equal to \ref UNUSED. If not, it
* sets it to a new value.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param checkedValue pointer (&variable) pointing to a data in a structure
* @param wantedNewValue value which the data pointed will be set to if not \ref UNUSED
*/
void CheckIfUnused(unsigned char *checkedValue, unsigned char wantedNewValue)
{
    if(*checkedValue != UNUSED) {*checkedValue = wantedNewValue;}
}
#pragma endregion PRIVATE_FUNCTIONS


//#############################################################################
#pragma region PUBLIC_FUNCTIONS_CODE
//-----------------------------------------------------------------------------
/**
* @brief Sets the received command structure (ModuleData.CommandsReceived) to
* the same input value. Useful to reset any received commands when a new mode
* has been received from the master.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to \ref UNUSED
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
/**
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
/**
* @brief Sets the values to send structure of the ModuleData to the same value.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to UNUSED
*/
void ModuleData_SetAll_ValuesToSend(unsigned char ValueAppliedToAll)
{
    CheckIfUnused(&ModuleData.ValuesToSend.disc_Black,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesToSend.disc_Red,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesToSend.disc_Silver,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesToSend.disc_CouldNotBeFound,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesToSend.disc_NoColor,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesToSend.disc_Detected,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesToSend.unit_Imperial,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesToSend.unit_Metric,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesToSend.disc_Lost,ValueAppliedToAll);
}
/**
* @brief Sets all the received value structure to the same value.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to UNUSED
*/
void ModuleData_SetAll_ValuesReceived(unsigned char ValueAppliedToAll)
{
    CheckIfUnused(&ModuleData.ValuesReceived.disc_Black,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesReceived.disc_Red,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesReceived.disc_Silver,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesReceived.disc_CouldNotBeFound,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesReceived.disc_NoColor,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesReceived.disc_Detected,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesReceived.unit_Imperial,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesReceived.unit_Metric,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.ValuesReceived.disc_Lost,ValueAppliedToAll);
}
/**
* @brief Sets all the states in a \ref stStates structure to the same value.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to \ref UNUSED
*/
void ModuleData_SetAll_StatesReceived(unsigned char ValueAppliedToAll)
{
    CheckIfUnused(&ModuleData.StatesReceived.calibrating,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.calibrated,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.waiting,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.safe,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.error,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.atSortingFactory,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.atWeightStation,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.finishedSortingAndHasLoaded,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.waitingToSort,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.waitingToWeight,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.finishedWeighting,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.empty,ValueAppliedToAll);
}
/**
* @brief Function periodically called via the time base's interruptions. It is
* important to allocate a buffer address in your time base for this function.
* Do this via your main.h file, and ServiceCommunication.h.
* You will need to set \ref SCOMMS_PARSE_RX_BUFFER_ADR to the appropriated number
* in your buffer.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param void Time base functions take no parameters
*/
void ServiceCommunication_RXParsingHandler(void)
{
    //########################################## LOCAL VAR
    //##########################################

    // CAN DATA IS AVAILABLE
    if(CHECK_MODULE_CAN_RECEPTION)
    {
        Parse_CanBusReceptions(MODULE_CAN_RX_BUFFER);
    }

    if(CHECK_MASTER_CAN_RECEPTION)
    {
        Parse_CanBusReceptions(MASTER_CAN_RX_BUFFER);        
    }
}
/**
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
    Count_Interrupts();
}
/**
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
    ModuleData_SetAll_ValuesReceived(NO_DATA);
    ModuleData_SetAll_StatesReceived(NO_DATA);

    ModuleData_SetAll_SentCommands(AVAILABLE);
    ModuleData_SetAll_ValuesToSend(UNUSED);

    // Keep set to unused or the program will constantly send Weight data on
    // the CAN bus.
    ModuleData.Weight = UNUSED;

    // The initial state of modules is "waiting" as they are "waiting" for
    // Synchronisation detection.
    ModuleData.State = States.waiting;

    // The initial state for modules is Initialisation. In this mode, your
    // module simply sets itself to it's initial state.
    ModuleData.Mode = Modes.reinitialisation;
}
//-----------------------------------------------------------------------------
#pragma endregion PUBLIC_FUNCTIONS_CODE




/*
int main(void)
{
    ServiceCommunication_initialise();

    printf("%i",ModuleData.ValuesToSend.disc_Black);
    CheckIfUnused(&ModuleData.CommandsToSend.discharge,7);
    return 0;
}
*/