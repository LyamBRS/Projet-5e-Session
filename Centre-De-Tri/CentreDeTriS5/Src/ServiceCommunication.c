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
#include "ServiceCommunication.h"
#include "main.h"
#include <stdio.h>
#include "serviceBaseDeTemps.h"
#include "interfaceCAN1.h"
#pragma endregion INCLUDES

//#############################################################################
#pragma region EXTERN_DECLARATIONS
extern unsigned char TemporaryFunctionBuffer[7];
unsigned char temporaryCANTXBuffer[8];
unsigned char temporaryModuleBuffer[8];
unsigned char temporaryMasterBuffer[8];
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
/**
 * @brief This buffer is used to store which commands or values were \ref QUEUE
 * by he program, to send them x by x amount each time the CAN slot is equal to
 * your module's appropriated slot.\n
 * Do not use this buffer outside of this file. The program handles it by itself.\n
 * You need 24 bytes of memory to store this buffer.\n\n
 * If no value is stored in at an index, it will be 0xFF.\n
 * Otherwise, the value of the \ref stCommands is stored in it.
 */
unsigned char CircularCommandsBuffer[24];
/**
 * @brief This buffer is used to store which valus were \ref QUEUE
 * by he program, to send them x by x amount each time the CAN slot is equal to
 * your module's appropriated slot.\n
 * Do not use this buffer outside of this file. The program handles it by itself.\n
 * You need 10 bytes of memory to store this buffer.\n\n
 * If no value is stored in at an index, it will be 0xFF.\n
 * Otherwise, the value of the \ref stValues is stored in it.
 */
unsigned char CircularValuesBuffer[10];
#pragma endregion PRIVATE_VARIABLES
//#############################################################################
#pragma region PRIVATE_FUNCTIONS
//-----------------------------------------------------------------------------
/**
* @brief Function setting all values in an array to the same input value.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param Buffer Pointer pointing the address of the buffer to set.
* @param sizeOfBuffer How big is the buffer referenced.
* @param ValueAppliedToAll What value should the buffer have.
*/
void Utils_SetAll_Buffer(unsigned char *Buffer, unsigned char sizeOfBuffer, unsigned char ValueAppliedToAll)
{
    for(int i=0; i<sizeOfBuffer; ++i) {Buffer[i] = ValueAppliedToAll;}
}

/**
* @brief Function compressing data downwards in a buffer. It slides data downwards
* by 1 index if the one below the data is equal to 0xFF.
* @author Lyam / Shawn Couture
* @date 17/11/2022
* @param Buffer Pointer pointing the address of the buffer to update.
* @param sizeOfBuffer How big is the buffer referenced.
*/
void CB_UpdateBuffer(unsigned char* Buffer, unsigned char sizeOfBuffer)
{
    unsigned char dataNeedsShifting = 2;
    while(dataNeedsShifting==2)
    {
        dataNeedsShifting = 0;
        for(int i=sizeOfBuffer-1;i>0;i--)
        {
            if(Buffer[i-1] == 0xFF)
            {
                if(dataNeedsShifting==0) {dataNeedsShifting=1;}
            }
            else
            {
                if(dataNeedsShifting==1) {dataNeedsShifting=2;}
            }            
            
            //If the current address is empty.
            if(Buffer[i] == 0xFF)
            {
                //Set this buffer index to be equal to the one before it.
                Buffer[i] = Buffer[i-1];
                //Set slot to empty as it was moved to this one.
                Buffer[i-1] = 0xFF;
            }        
        }
    }
}
/**
* @brief Adds an unsigned char to the referenced buffer at whichever index is
* first available for it (0xFF). If it's all 0xFF, it will be added at the
* bottom of the buffer.
* @author Lyam / Shawn Couture
* @date 17/11/2022
* @param Buffer Pointer pointing the address of the buffer to queue.
* @param sizeOfBuffer How big is the buffer referenced.
* @param DataToCheck Pointer to the data that potentially needs queuing. (in ModuleData)
* @param DataValueFromRefStruct Value associated to this commands or value (\ref stCommands or \ref stValues)
*/
void CB_QueueDataInBuffer(unsigned char* Buffer, unsigned char sizeOfBuffer, unsigned char* DataToCheck, unsigned char DataValueFromRefStruct)
{
    if(*DataToCheck != UNUSED_ && *DataToCheck == QUEUE)
    {
        for(int i=sizeOfBuffer-1;i>0;--i)
        {
            //If the current address is empty.
            if(Buffer[i] == 0xFF)
            {
                //Store the structure reference at that address
                Buffer[i] = DataValueFromRefStruct;
                *DataToCheck = IN_QUEUE;
                i=0;
            }
        }
    }
}
/**
* @brief Takes \ref CircularValuesBuffer and parses it into the CAN transmission
* buffer. It checks for the first \ref AVAILABLE slots in the latter and puts the
* first element \ref IN_QUEUE in it. Each elements added to the referenced buffer
* is automatically set back to \ref AVAILABLE to be ready for the next placement
* in \ref CircularValuesBuffer.
* @author Lyam / Shawn Couture
* @date 17/11/2022
* @param Buffer Pointer to the CAN transmission buffer.
*/
void TX_PutValueQueueInBuffer(unsigned char* Buffer)
{
    //############################################ LOCAL VARS
    unsigned char QueueIndex = 9;
    //############################################

    //Doesn't bother doing anything if there is no values in the queue buffer
    if(CircularValuesBuffer[QueueIndex] != UNUSED_)
    {
        for(int i=0; i<8;i+=2)
        {
            //check if Command slot is AVAILABLE
            if(Buffer[i] == AVAILABLE)
            {
                //If data at the index location isn't equal to 0xFF, it gets placed in the CAN tram to be sent.
                if(CircularValuesBuffer[QueueIndex] != UNUSED_)
                {
                    Buffer[i] = CHAR_VALUE;
                    Buffer[i+1] = CircularValuesBuffer[QueueIndex];

                    switch(CircularValuesBuffer[QueueIndex])
                    {
                        case(0x00): ModuleData.ValuesToSend.disc_Red             = AVAILABLE; break;
                        case(0x01): ModuleData.ValuesToSend.disc_Silver          = AVAILABLE; break;
                        case(0x02): ModuleData.ValuesToSend.disc_Black           = AVAILABLE; break;
                        case(0x03): ModuleData.ValuesToSend.disc_NoColor         = AVAILABLE; break;
                        case(0x04): ModuleData.ValuesToSend.disc_Detected        = AVAILABLE; break;
                        case(0x05): ModuleData.ValuesToSend.disc_Lost            = AVAILABLE; break;
                        case(0x06): ModuleData.ValuesToSend.disc_CouldNotBeFound = AVAILABLE; break;
                        case(0x07): ModuleData.ValuesToSend.unit_Metric          = AVAILABLE; break;
                        case(0x08): ModuleData.ValuesToSend.unit_Imperial        = AVAILABLE; break;
                    }
                    CircularValuesBuffer[QueueIndex] = UNUSED_;
                    QueueIndex--;
                }
            }
        }
    }
}
/**
* @brief Takes \ref CircularCommandsBuffer and parses it into the CAN transmission
* buffer. It checks for the first \ref AVAILABLE slots in the latter and puts the
* first element \ref IN_QUEUE at that index. Each elements added to the Buffer
* is automatically set back to \ref AVAILABLE to be ready for the next placement
* in \ref CircularCommandsBuffer.\n
* This function is bypassed internally if \ref CircularCommandsBuffer first
* element is empty. (Meaning no commands are \ref IN_QUEUE for transmission).
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param Buffer Pointer to the CAN transmission buffer.
*/
void TX_PutCommandQueueInBuffer(unsigned char* Buffer)
{
    //############################################ LOCAL VARS
    unsigned char QueueIndex = 23;
    //############################################

    //Doesn't bother doing anything if there is no values in the queue buffer
    if(CircularCommandsBuffer[QueueIndex] != UNUSED_)
    {
        for(int i=0; i<8;i+=2)
        {
            //check if Command slot is AVAILABLE
            if(Buffer[i] == AVAILABLE)
            {
                //If data at the index location isn't equal to 0xFF, it gets placed in the CAN tram to be sent.
                if(CircularCommandsBuffer[QueueIndex] != UNUSED_)
                {
                    Buffer[i] = CHAR_COMMAND;
                    Buffer[i+1] = CircularCommandsBuffer[QueueIndex];

                    switch(CircularCommandsBuffer[QueueIndex])
                    {
                        case(0x00): ModuleData.CommandsToSend.move_left            = AVAILABLE; break;
                        case(0x01): ModuleData.CommandsToSend.move_right           = AVAILABLE; break;
                        case(0x02): ModuleData.CommandsToSend.move_forward         = AVAILABLE; break;
                        case(0x03): ModuleData.CommandsToSend.move_backward        = AVAILABLE; break;
                        case(0x04): ModuleData.CommandsToSend.move_up              = AVAILABLE; break;
                        case(0x05): ModuleData.CommandsToSend.move_down            = AVAILABLE; break;
                        case(0x06): ModuleData.CommandsToSend.suction_ON           = AVAILABLE; break;
                        case(0x07): ModuleData.CommandsToSend.suction_OFF          = AVAILABLE; break;
                        case(0x08): ModuleData.CommandsToSend.light_A_ON           = AVAILABLE; break;
                        case(0x09): ModuleData.CommandsToSend.light_A_OFF          = AVAILABLE; break;
                        case(0x0A): ModuleData.CommandsToSend.light_B_ON           = AVAILABLE; break;
                        case(0x0B): ModuleData.CommandsToSend.light_B_OFF          = AVAILABLE; break;
                        case(0x0C): ModuleData.CommandsToSend.light_C_ON           = AVAILABLE; break;
                        case(0x0D): ModuleData.CommandsToSend.light_C_OFF          = AVAILABLE; break;
                        case(0x0E): ModuleData.CommandsToSend.light_D_ON           = AVAILABLE; break;
                        case(0x0F): ModuleData.CommandsToSend.light_D_OFF          = AVAILABLE; break;
                        case(0x10): ModuleData.CommandsToSend.goto_SortingStation  = AVAILABLE; break;
                        case(0x11): ModuleData.CommandsToSend.goto_WeightStation   = AVAILABLE; break;
                        case(0x12): ModuleData.CommandsToSend.start_Sorting        = AVAILABLE; break;
                        case(0x13): ModuleData.CommandsToSend.start_Weighting      = AVAILABLE; break;
                        case(0x14): ModuleData.CommandsToSend.discharge            = AVAILABLE; break;
                        //case(0x15): ModuleData.CommandsToSend.RESERVED           = AVAILABLE; break;
                        case(0x16): ModuleData.CommandsToSend.units_Metric         = AVAILABLE; break;
                        case(0x17): ModuleData.CommandsToSend.units_Imperial       = AVAILABLE; break;
                    }
                    CircularCommandsBuffer[QueueIndex] = UNUSED_;
                    QueueIndex--;
                }
            }
        }
    }
}
/**
* @brief Function compressing data downwards in a buffer. It slides data downwards
* by 1 index if the one below the data is equal to 0xFF.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param Buffer Pointer to the address of \ref MODULE_CAN_TX
*/
void TX_BuildCANBuffer(unsigned char* Buffer)
{
    //Reset of buffer's data.
    Utils_SetAll_Buffer(Buffer,8,AVAILABLE);

    //Put module state in the buffer
    Buffer[6] = CHAR_STATE;
    Buffer[7] = ModuleData.State;

    //Put weight in buffer.
    if(ModuleData.WeightToSend != UNUSED_)
    {
        Buffer[4] = CHAR_WEIGHT;
        Buffer[5] =  ModuleData.WeightToSend;
    }

    //Put QUEUE in buffer
    TX_PutValueQueueInBuffer(Buffer);
    TX_PutCommandQueueInBuffer(Buffer);
}
/**
* @brief Function putting \ref IN_QUEUE datas from \ref stModuleData whenever
* it is called.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param void
*/
void Parse_ModuleDataForTransmission(void)
{
    //############################################ LOCAL VARS
    //static unsigned char oldReceivedMode;
    //############################################

    // Updating circular buffers
    CB_UpdateBuffer(CircularCommandsBuffer,24);
    CB_UpdateBuffer(CircularValuesBuffer,10);

    // Check for values equal to QUEUE and add them to a circular buffer.
    // To optimise the code, put unused commands in comments.
    #pragma region VALUE_TX
    // Disc color specific values
    CB_QueueDataInBuffer(CircularValuesBuffer,10,&ModuleData.ValuesToSend.disc_Black,              Values.disc_Black);
    CB_QueueDataInBuffer(CircularValuesBuffer,10,&ModuleData.ValuesToSend.disc_Red,                Values.disc_Red);
    CB_QueueDataInBuffer(CircularValuesBuffer,10,&ModuleData.ValuesToSend.disc_Silver,             Values.disc_Silver);
    CB_QueueDataInBuffer(CircularValuesBuffer,10,&ModuleData.ValuesToSend.disc_NoColor,            Values.disc_NoColor);
    // Colorless disc detection specific values
    CB_QueueDataInBuffer(CircularValuesBuffer,10,&ModuleData.ValuesToSend.disc_Detected,           Values.disc_Detected);
    CB_QueueDataInBuffer(CircularValuesBuffer,10,&ModuleData.ValuesToSend.disc_Lost,               Values.disc_Lost);
    CB_QueueDataInBuffer(CircularValuesBuffer,10,&ModuleData.ValuesToSend.disc_CouldNotBeFound,    Values.disc_CouldNotBeFound);
    // Balance specific units used values.
    CB_QueueDataInBuffer(CircularValuesBuffer,10,&ModuleData.ValuesToSend.unit_Imperial,           Values.unit_Imperial);
    CB_QueueDataInBuffer(CircularValuesBuffer,10,&ModuleData.ValuesToSend.unit_Metric,             Values.unit_Metric);
    #pragma endregion VALUE_TX

    #pragma region COMMANDS_TX
    // Vehicle specific commands 
    // To optimise the code, put unused commands in comments.
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.goto_SortingStation,   Commands.goto_SortingStation);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.goto_WeightStation,    Commands.goto_WeightStation);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.discharge,             Commands.discharge);
    // Lights generic commands
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.light_A_OFF,           Commands.light_A_OFF);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.light_A_ON,            Commands.light_A_ON);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.light_B_OFF,           Commands.light_B_OFF);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.light_B_ON,            Commands.light_B_ON);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.light_C_OFF,           Commands.light_C_OFF);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.light_C_ON,            Commands.light_C_ON);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.light_D_OFF,           Commands.light_D_OFF);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.light_D_ON,            Commands.light_D_ON);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.light_D_ON,            Commands.light_D_ON);
    // Movement generic commands
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.move_left,             Commands.move_left);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.move_right,            Commands.move_right); 
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.move_forward,          Commands.move_forward); 
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.move_backward,         Commands.move_backward); 
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.move_up,               Commands.move_up); 
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.move_down,             Commands.move_down);
    // Pneumatic specific commands
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.suction_ON,            Commands.suction_ON);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.suction_OFF,           Commands.suction_OFF);
    // Stations specific commands
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.start_Sorting,         Commands.start_Sorting);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.start_Weighting,       Commands.start_Weighting);
    // Weight specific commands
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.units_Imperial,        Commands.units_Imperial);
    CB_QueueDataInBuffer(CircularCommandsBuffer,24,&ModuleData.CommandsToSend.units_Metric,          Commands.units_Metric);
    #pragma endregion COMMANDS_TX
}
/**
* @brief Parsing function decorticating an 8 bytes array into the service's
* structures \ref stModuleData
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param Buffer Pointer pointing the address of a CAN RX 8 bytes unsigned char array.
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
            case(CHAR_MODE):
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
                            ModuleData_SetAll_ValuesReceived(NO_DATA);
                        }

                        // Reset counts and slots indentifications
                        interruptCount = 0;
                        currentSlot = 0;
                        ModuleData.CantConnect = 0x00;
            break;
            case(CHAR_COMMAND):
                        switch(Buffer[i+1])
                        {
                            // Parsing of received commands in a CAN tram
                            case(0x00): ModuleData.CommandsReceived.move_left     = RECEIVED; break;
                            case(0x01): ModuleData.CommandsReceived.move_right    = RECEIVED; break;
                            case(0x02): ModuleData.CommandsReceived.move_forward  = RECEIVED; break;
                            case(0x03): ModuleData.CommandsReceived.move_backward = RECEIVED; break;
                            case(0x04): ModuleData.CommandsReceived.move_up       = RECEIVED; break;
                            case(0x05): ModuleData.CommandsReceived.move_down     = RECEIVED; break;

                            case(0x06): ModuleData.CommandsReceived.suction_ON    = RECEIVED;
                                        ModuleData.CommandsReceived.suction_OFF   = NO_DATA; 
                                        break;
                            case(0x07): ModuleData.CommandsReceived.suction_OFF   = RECEIVED;
                                        ModuleData.CommandsReceived.suction_ON    = NO_DATA; 
                                        break;

                            case(0x08): ModuleData.CommandsReceived.light_A_ON    = RECEIVED;
                                        ModuleData.CommandsReceived.light_A_OFF   = NO_DATA;
                                        break;
                            case(0x09): ModuleData.CommandsReceived.light_A_OFF   = RECEIVED;
                                        ModuleData.CommandsReceived.light_A_ON    = NO_DATA;
                                        break;

                            case(0x0A): ModuleData.CommandsReceived.light_B_ON    = RECEIVED;
                                        ModuleData.CommandsReceived.light_B_OFF   = NO_DATA;
                                        break;
                            case(0x0B): ModuleData.CommandsReceived.light_B_OFF   = RECEIVED;
                                        ModuleData.CommandsReceived.light_B_ON    = NO_DATA;
                                        break;

                            case(0x0C): ModuleData.CommandsReceived.light_C_ON    = RECEIVED;
                                        ModuleData.CommandsReceived.light_C_OFF   = NO_DATA;
                                        break;
                            case(0x0D): ModuleData.CommandsReceived.light_C_OFF   = RECEIVED;
                                        ModuleData.CommandsReceived.light_C_ON    = NO_DATA;
                                        break;

                            case(0x0E): ModuleData.CommandsReceived.light_D_ON    = RECEIVED;
                                        ModuleData.CommandsReceived.light_D_OFF   = NO_DATA;
                                        break;
                            case(0x0F): ModuleData.CommandsReceived.light_D_OFF   = RECEIVED;
                                        ModuleData.CommandsReceived.light_D_ON    = NO_DATA;
                                        break;

                            case(0x10): ModuleData.CommandsReceived.goto_SortingStation = RECEIVED;
                                        ModuleData.CommandsReceived.goto_WeightStation  = NO_DATA;
                                        break;
                            case(0x11): ModuleData.CommandsReceived.goto_WeightStation  = RECEIVED;
                                        ModuleData.CommandsReceived.goto_SortingStation = NO_DATA;
                                        break;

                            case(0x12): ModuleData.CommandsReceived.start_Sorting       = RECEIVED; break;
                            case(0x13): ModuleData.CommandsReceived.start_Weighting     = RECEIVED; break;

                            case(0x14): ModuleData.CommandsReceived.discharge           = RECEIVED; break;

                            case(0x16): ModuleData.CommandsReceived.units_Metric        = RECEIVED;
                                        ModuleData.CommandsReceived.units_Imperial      = NO_DATA;  
                                        break;
                            case(0x17): ModuleData.CommandsReceived.units_Imperial      = RECEIVED;
                                        ModuleData.CommandsReceived.units_Metric        = NO_DATA;  
                                        break;
                            default:
                                        //If received mode matched nothing, an error occured.
                                        ModuleData.State = States.error;
                                        serviceCommunication_ErrorState = ERROR_RX_COMMAND_DOESNT_EXIST;
                                        break;                  
                        }
            break;
            case(CHAR_VALUE):
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
            case(CHAR_STATE):
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
            case(CHAR_WEIGHT):  // A weight was received.
                        ModuleData.ReceivedWeight = Buffer[i+1];
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
    //Count active interrupts
    interruptCount++;

    //How long is an interrupt --> how long is a full buffer cycle.
    float interruptDuration = ((((float)1)/((float)TIME_BASE_FREQUENCY_HZ)) * ((float)1000)) * ((float)TIME_BASE_BUFFER_SIZE);

    //How long we've been running.
    float timeSinceReset = interruptDuration * ((float)(interruptCount));

    //Current slot.
    if(ModuleData.CantConnect == 0x00)
    {
        currentSlot = ((unsigned char)(timeSinceReset)) / CAN_SLOT_DURATION_MS;
    }

    if(currentSlot > 10)
    {
        ModuleData.CantConnect = 0xFF;
    }
}
/**
* @brief Private function checking if a variable is equal to \ref UNUSED_. If not, it
* sets it to a new value.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param checkedValue pointer (&variable) pointing to a data in a structure
* @param wantedNewValue value which the data pointed will be set to if not \ref UNUSED_
*/
void CheckIfUnused(unsigned char *checkedValue, unsigned char wantedNewValue)
{
    if(*checkedValue != UNUSED_) {*checkedValue = wantedNewValue;}
}
#pragma endregion PRIVATE_FUNCTIONS


//#############################################################################
#pragma region PUBLIC_FUNCTIONS_CODE
//-----------------------------------------------------------------------------
/**
* @brief handles the units value sending for you to avoid sending 2 at the time
* and to automatically remove from QUEUE previous values.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param UnitsToPutInValues reference from \ref stValues Can also be \ref UNUSED_
*/
void ModuleData_SetUnits(unsigned char UnitsToPutInValues)
{
    // Prevents sending and optimises the process of QUEUE
    if(UnitsToPutInValues == UNUSED_)
    {
        //Remove both from the circular buffer.
        if(ModuleData.ValuesToSend.unit_Metric == IN_QUEUE || ModuleData.ValuesToSend.unit_Imperial == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.unit_Metric) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.unit_Imperial) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        ModuleData.ValuesToSend.unit_Imperial = UNUSED_;
        ModuleData.ValuesToSend.unit_Metric = UNUSED_;
    }
    ////////////////////////////////////////////////////////////////////////////
    if(UnitsToPutInValues == Values.unit_Imperial)
    {
        if(ModuleData.ValuesToSend.unit_Metric == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.unit_Metric) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        // Set Imperial to appropriated value
        if(ModuleData.ValuesToSend.unit_Imperial != IN_QUEUE)
        {
            ModuleData.ValuesToSend.unit_Imperial = QUEUE;
        }
        ModuleData.ValuesToSend.unit_Metric = NO_DATA;
    }
    ////////////////////////////////////////////////////////////////////////////
    if(UnitsToPutInValues == Values.unit_Metric)
    {
        if(ModuleData.ValuesToSend.unit_Imperial == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.unit_Imperial) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        // Set Metric to appropriated value
        if(ModuleData.ValuesToSend.unit_Metric != IN_QUEUE)
        {
            ModuleData.ValuesToSend.unit_Metric = QUEUE;
        }
        ModuleData.ValuesToSend.unit_Imperial = NO_DATA;
    }
}
/**
* @brief handles the disc color value sending for you to avoid sending 2 at the time
* and to automatically remove from QUEUE previous values.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param UnitsToPutInValues reference from \ref stValues Can also be \ref UNUSED_
*/
void ModuleData_SetDiscColor(unsigned char ColorToPutInValues)
{
    // Prevents sending and optimises the process of QUEUE
    if(ColorToPutInValues == UNUSED_)
    {
        //Remove both from the circular buffer.
        if(ModuleData.ValuesToSend.disc_Black == IN_QUEUE || ModuleData.ValuesToSend.disc_Red == IN_QUEUE || ModuleData.ValuesToSend.disc_Silver == IN_QUEUE || ModuleData.ValuesToSend.disc_NoColor == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.disc_Black) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_Red) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_Silver) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_NoColor) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        ModuleData.ValuesToSend.disc_Black = UNUSED_;
        ModuleData.ValuesToSend.disc_Red = UNUSED_;
        ModuleData.ValuesToSend.disc_Silver = UNUSED_;
        ModuleData.ValuesToSend.disc_NoColor = UNUSED_;
    }
    //////////////////////////////////////////////////////////////////////////// RED DISC
    if(ColorToPutInValues == Values.disc_Red)
    {
        if(ModuleData.ValuesToSend.disc_Black == IN_QUEUE || ModuleData.ValuesToSend.disc_Silver == IN_QUEUE || ModuleData.ValuesToSend.disc_NoColor == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.disc_Black) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_Silver) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_NoColor) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        // Set Imperial to appropriated value
        if(ModuleData.ValuesToSend.disc_Red != IN_QUEUE)
        {
            ModuleData.ValuesToSend.disc_Red = QUEUE;
        }
        ModuleData.ValuesToSend.disc_Black = NO_DATA;
        ModuleData.ValuesToSend.disc_Silver = NO_DATA;
        ModuleData.ValuesToSend.disc_NoColor = NO_DATA;
    }
    //////////////////////////////////////////////////////////////////////////// BLACK DISC
    if(ColorToPutInValues == Values.disc_Black)
    {
        if(ModuleData.ValuesToSend.disc_Red == IN_QUEUE || ModuleData.ValuesToSend.disc_Silver == IN_QUEUE || ModuleData.ValuesToSend.disc_NoColor == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.disc_Red) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_Silver) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_NoColor) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        // Set Imperial to appropriated value
        if(ModuleData.ValuesToSend.disc_Black != IN_QUEUE)
        {
            ModuleData.ValuesToSend.disc_Black = QUEUE;
        }
        ModuleData.ValuesToSend.disc_Red = NO_DATA;
        ModuleData.ValuesToSend.disc_Silver = NO_DATA;
        ModuleData.ValuesToSend.disc_NoColor = NO_DATA;
    }
    //////////////////////////////////////////////////////////////////////////// SILVER DISC
    if(ColorToPutInValues == Values.disc_Silver)
    {
        if(ModuleData.ValuesToSend.disc_Red == IN_QUEUE || ModuleData.ValuesToSend.disc_Black == IN_QUEUE || ModuleData.ValuesToSend.disc_NoColor == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.disc_Red) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_Black) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_NoColor) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        // Set Imperial to appropriated value
        if(ModuleData.ValuesToSend.disc_Silver != IN_QUEUE)
        {
            ModuleData.ValuesToSend.disc_Silver = QUEUE;
        }
        ModuleData.ValuesToSend.disc_Red = NO_DATA;
        ModuleData.ValuesToSend.disc_Black = NO_DATA;
        ModuleData.ValuesToSend.disc_NoColor = NO_DATA;
    }
    //////////////////////////////////////////////////////////////////////////// NO COLOR DISC
    if(ColorToPutInValues == Values.disc_NoColor)
    {
        if(ModuleData.ValuesToSend.disc_Red == IN_QUEUE || ModuleData.ValuesToSend.disc_Black == IN_QUEUE || ModuleData.ValuesToSend.disc_Silver == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.disc_Red) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_Black) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_Silver) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        // Set Imperial to appropriated value
        if(ModuleData.ValuesToSend.disc_NoColor != IN_QUEUE)
        {
            ModuleData.ValuesToSend.disc_NoColor = QUEUE;
        }
        ModuleData.ValuesToSend.disc_Red = NO_DATA;
        ModuleData.ValuesToSend.disc_Black = NO_DATA;
        ModuleData.ValuesToSend.disc_NoColor = NO_DATA;
    }
}
/**
* @brief handles the disc detection value sending for you to avoid sending 2 at the time
* and to automatically remove from QUEUE previous values.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param DetectionToPutInValues reference from \ref stValues Can also be \ref UNUSED_
*/
void ModuleData_SetDiscDetection(unsigned char DetectionToPutInValues)
{
    // Prevents sending and optimises the process of QUEUE
    if(DetectionToPutInValues == UNUSED_)
    {
        //Remove both from the circular buffer.
        if(ModuleData.ValuesToSend.disc_Detected == IN_QUEUE || ModuleData.ValuesToSend.disc_Lost == IN_QUEUE || ModuleData.ValuesToSend.disc_CouldNotBeFound == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.disc_Detected) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_Lost) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_CouldNotBeFound) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        ModuleData.ValuesToSend.disc_Detected = UNUSED_;
        ModuleData.ValuesToSend.disc_Lost = UNUSED_;
        ModuleData.ValuesToSend.disc_CouldNotBeFound = UNUSED_;
    }
    //////////////////////////////////////////////////////////////////////////// DETECTED DISC
    if(DetectionToPutInValues == Values.disc_Detected)
    {
        if(ModuleData.ValuesToSend.disc_Lost == IN_QUEUE || ModuleData.ValuesToSend.disc_CouldNotBeFound == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.disc_Lost) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_CouldNotBeFound) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        // Set Imperial to appropriated value
        if(ModuleData.ValuesToSend.disc_Detected != IN_QUEUE)
        {
            ModuleData.ValuesToSend.disc_Detected = QUEUE;
        }
        ModuleData.ValuesToSend.disc_Lost = NO_DATA;
        ModuleData.ValuesToSend.disc_CouldNotBeFound = NO_DATA;
    }
    //////////////////////////////////////////////////////////////////////////// LOST DISC
    if(DetectionToPutInValues == Values.disc_Lost)
    {
        if(ModuleData.ValuesToSend.disc_Detected == IN_QUEUE || ModuleData.ValuesToSend.disc_CouldNotBeFound == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.disc_Detected) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_CouldNotBeFound) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        // Set Imperial to appropriated value
        if(ModuleData.ValuesToSend.disc_Lost != IN_QUEUE)
        {
            ModuleData.ValuesToSend.disc_Lost = QUEUE;
        }
        ModuleData.ValuesToSend.disc_Detected = NO_DATA;
        ModuleData.ValuesToSend.disc_CouldNotBeFound = NO_DATA;
    }
    //////////////////////////////////////////////////////////////////////////// LOST DISC
    if(DetectionToPutInValues == Values.disc_CouldNotBeFound)
    {
        if(ModuleData.ValuesToSend.disc_Detected == IN_QUEUE || ModuleData.ValuesToSend.disc_Lost == IN_QUEUE)
        {
            for(int i=0; i<10; ++i)
            {
                //QUEUE reset.
                if(CircularValuesBuffer[i] == Values.disc_Detected) {CircularValuesBuffer[i] = UNUSED_;}
                if(CircularValuesBuffer[i] == Values.disc_Lost) {CircularValuesBuffer[i] = UNUSED_;}
            }
        }
        // Set Imperial to appropriated value
        if(ModuleData.ValuesToSend.disc_CouldNotBeFound != IN_QUEUE)
        {
            ModuleData.ValuesToSend.disc_CouldNotBeFound = QUEUE;
        }
        ModuleData.ValuesToSend.disc_Detected = NO_DATA;
        ModuleData.ValuesToSend.disc_Lost = NO_DATA;
    }
}
/**
* @brief Sets the received command structure (ModuleData.CommandsReceived) to
* the same input value. Useful to reset any received commands when a new mode
* has been received from the master.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to \ref UNUSED_
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
* equal to UNUSED_
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
* equal to UNUSED_
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
* equal to UNUSED_
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
* equal to \ref UNUSED_
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
    CheckIfUnused(&ModuleData.StatesReceived.processing,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.paused,ValueAppliedToAll);
    CheckIfUnused(&ModuleData.StatesReceived.emergencyStop,ValueAppliedToAll);
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
        interfaceCAN1_litUnMessageRecu(MODULE_CAN_RX_BUFFER);
        Parse_CanBusReceptions(MODULE_CAN_RX_BUFFER);
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
    //Check where we are in the CAN stuff.
    Parse_Interrupts();

    if(currentSlot == CAN_ALLOCATED_SLOT)
    {
        //Parses QUEUE into transmittable buffer
        TX_BuildCANBuffer(MODULE_CAN_TX);
        interfaceCAN1_transmetDesDonnes(0x200,MODULE_CAN_TX,8);
    }
    else
    {
        //Put structure in QUEUE buffers to transmit faster once the CAN slot is ours.
        Parse_ModuleDataForTransmission();
    }
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

    ModuleData_SetAll_SentCommands(UNUSED_);
    ModuleData_SetAll_ValuesToSend(UNUSED_);

    // Keep set to unused or the program will constantly send Weight data on
    // the CAN bus.
    ModuleData.WeightToSend = UNUSED_;

    // If equal to NO_DATA, no weights were received from the module.
    ModuleData.ReceivedWeight = NO_DATA;

    // The initial state of modules is "waiting" as they are "waiting" for
    // Synchronisation detection.
    ModuleData.State = States.waiting;

    // The initial state for modules is Initialisation. In this mode, your
    // module simply sets itself to it's initial state.
    ModuleData.Mode = Modes.reinitialisation;

    ModuleData.CantConnect = 0x00;

    Utils_SetAll_Buffer(MODULE_CAN_TX, 8, AVAILABLE);
    Utils_SetAll_Buffer(CircularCommandsBuffer, 24, UNUSED_);
    Utils_SetAll_Buffer(CircularValuesBuffer, 10, UNUSED_);

    TIME_BASE_BUFFER[SCOMMS_PARSE_RX_BUFFER_ADR] = ServiceCommunication_RXParsingHandler;
    TIME_BASE_BUFFER[SCOMMS_PARSE_TX_BUFFER_ADR] = ServiceCommunication_TXParsingHandler;
}
//-----------------------------------------------------------------------------
#pragma endregion PUBLIC_FUNCTIONS_CODE
/*
int main(void)
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n SUS");
    ServiceCommunication_initialise();
    printf("%i",ModuleData.ValuesToSend.disc_Black);
    CheckIfUnused(&ModuleData.CommandsToSend.discharge,7);
    printf("%i",ModuleData.ValuesToSend.disc_Black);

    while(1)
    {
        printf("Bruh");
    }

    return 0;
}
*/