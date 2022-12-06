#ifndef Service_Communication_H
#define Service_Communication_H
/**
 * @file ServiceCommunication.h
 * @author Lyam / Shawn Couture (cous5830@gmail.com)
 * @brief
 * This service is a c library which goal is to parse data sent or data received for a school project.
 * This file requires premade functions and buffers which are labeled and described in this document in order to work properly or at all.
 * This service's goal is to allow the user to solely use structures in order to check for received info or send info.
 * The communication protocol range from UART to CAN. However, you will need ot parse UART data a bit more.
 * @version 0.1
 * @date 2022-11-14
 * @copyright Copyright (c) 2022
 * 
 */
//#############################################################################
#pragma region SERVICECOMMUNICATION_ERROR_DEFINES
//-----------------------------------------------------------------------------
/**
 * @brief Indicates that the library is not currently in any errors.
 */
#define NO_ERROR 0
/**
 * @brief Indicates that there was an error when parsing a received \ref stModes
 * from a communicating module. The received \ref stModes didn't match availables
 * \ref stModes and couldn't be put in \ref ModuleData
 */
#define ERROR_RX_MODE_DOESNT_EXIST 1
/**
 * @brief Indicates that there was an error when parsing a received \ref stStates
 * from a communicating module. The received \ref stStates didn't match availables
 * \ref stStates and couldn't be put in \ref ModuleData
 */
#define ERROR_RX_STATE_DOESNT_EXIST 2
/**
 * @brief Indicates that there was an error when parsing a received \ref stCommands
 * from a communicating module. The received \ref stCommands didn't match availables
 * \ref stCommands and couldn't be put in \ref ModuleData
 */
#define ERROR_RX_COMMAND_DOESNT_EXIST 3
/**
 * @brief Indicates that there was an error when parsing a received \ref stValues
 * from a communicating module. The received \ref stValues didn't match availables
 * \ref stValues and couldn't be put in \ref stValues
 */
#define ERROR_RX_VALUE_DOESNT_EXIST 4
/**
 * @brief The library timed out and could not receive an \ref stModes from a CAN
 * slot in the given time.
 */
#define ERROR_TIMEDOUT 5
/**
 * @brief Indicates that the module using this library encountered an error due to
 * factors outside of this library.
 */
#define ERROR_SPECIFIC_TO_MODULE 6
//-----------------------------------------------------------------------------
/**
 * @brief Indicates that there was an error when trying to parse \ref stModuleData
 * into the CAN transmission buffer \ref MODULE_CAN_TX. The command \ref IN_QUEUE  
 * did not exist in the @c switch @c case found in TX_PutCommandQueueInBuffer()
 */
#define ERROR_TX_COMMAND_DOESNT_EXIST 7
/**
 * @brief Indicates that there was an error when trying to parse \ref stModuleData
 * into the CAN transmission buffer \ref MODULE_CAN_TX. The value \ref IN_QUEUE  
 * did not exist in the @c switch @c case found in TX_PutValueQueueInBuffer()
 */
#define ERROR_TX_VALUE_DOESNT_EXIST 8

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
extern unsigned char serviceCommunication_ErrorState;

#pragma endregion SERVICECOMMUNICATION_ERROR_DEFINES
//#############################################################################
#pragma region SERVICECOMMUNICATION_DEFINES
//-----------------------------------------------------------------------------
/**
 * @brief Means that the value or commands is not used by this specific module.
 * This is important as the functions use this to figure out which data needs
 * to be send when a CAN slot is \ref AVAILABLE for the module
 */
#define UNUSED 0xFF
//-----------------------------------------------------------------------------
/**
 * @brief Specifies that you want a specific command inside \ref stCommands 
 * queued for the next CAN transmission
 */
#define QUEUE 0xFE
/**
 * @brief Indicates that the \ref stCommands is already in queue for a transmission.
 * @warning Do not put your \ref stCommands back to \ref QUEUE while it is equal to
 * this.
 */
#define IN_QUEUE 0xFD
/**
 * @brief tells you that this \ref stCommands is AVAILABLE for a \ref QUEUE request.
 */
#define AVAILABLE 0xAA
//-----------------------------------------------------------------------------
/**
 * @brief Tells you that you received a request to execute this
 * specific \ref stCommands.
 */
#define RECEIVED 0xBB
/**
 * @brief Tells the program that you parsed the \ref RECEIVED command in 
 * \ref stModuleData
 */
#define PARSED 0xCC
/**
 * @brief Tells you that no requests have been received for this specific
 * command. If there was a request, the command would be equal to \ref RECEIVED.
 */
#define NO_DATA 0x00
//-----------------------------------------------------------------------------
/**
 * @brief Defines the character needed to parse \ref stModes during 
 * transmission or reception of data. Refer to P-S5_Communications for more 
 * details.
 */
#define CHAR_MODE 'M'
/**
 * @brief Defines the character needed to parse \ref stStates during 
 * transmission or reception of data. Refer to P-S5_Communications for more 
 * details.
 */
#define CHAR_STATE 'S'
/**
 * @brief Defines the character needed to parse \ref stValues during 
 * transmission or reception of data. Refer to P-S5_Communications for more 
 * details.
 */
#define CHAR_VALUE 'V'
/**
 * @brief Defines the character needed to parse \ref stCommands during 
 * transmission or reception of data. Refer to P-S5_Communications for more 
 * details.
 */
#define CHAR_COMMAND 'C'
/**
 * @brief Defines the character needed to parse Weight during 
 * transmission or reception of data. Refer to P-S5_Communications for more 
 * details.
 */
#define CHAR_WEIGHT 'W'
/**
 * @brief Defines the character needed to parse a data tram during 
 * transmission or reception of data when CAN isn't the medium used for the
 * latter.
 */
#define CHAR_START '$'
//-----------------------------------------------------------------------------
#pragma endregion CAN_BUFFERS
//#############################################################################
#pragma region MAIN_REDEFINES

unsigned char TemporaryFunctionBuffer[7];
//-----------------------------------------------------------------------------
/**
 * @brief The time base frequency. Usually defined in main.h
 * Used to automatically calculate CAN slots allocations.
 */
#define TIME_BASE_FREQUENCY_HZ SERVICEBASEDETEMPS_FREQUENCE_EN_HZ
/**
 * @brief The time base's functions buffer size. Usually defined in main.h.
 * Used to figure out the intervals at which the execute function is called
 * to calculate slot's time frames for the CAN protocol.
 */
#define TIME_BASE_BUFFER_SIZE SERVICEBASEDETEMPS_NOMBRE_DE_PHASES
/**
 * @brief The time base's functions buffer size. Usually defined in main.h.
 * Used to figure out the intervals at which the execute function is called
 * to calculate slot's time frames for the CAN protocol.
 * @warning Don't put semi-colons after your define.
 */
#define TIME_BASE_BUFFER serviceBaseDeTemps_execute
/**
 * @brief The address from the timebase buffer (index) which will be used to put
 * \ref ServiceCommunication_RXParsingHandler() in
 */
#define SCOMMS_PARSE_RX_BUFFER_ADR 0
/**
 * @brief The address from the timebase buffer (index) which will be used to put
 * \ref ServiceCommunication_TXParsingHandler() in
 */
#define SCOMMS_PARSE_TX_BUFFER_ADR 1
/**
 * @brief The allocated slot for your module considering that the 
 * synchronisation slot is 0. Please refer to the datasheet available on
 * google drive in order to figure out your module's time frame.
 */
#define CAN_ALLOCATED_SLOT 3 // Pour véhicule
/**
 * @brief Specifies the duration in milliseconds of a slot. See Google drive
 * documentation to put the right value in this.
 */
#define CAN_SLOT_DURATION_MS 20
#pragma endregion MAIN_REDEFINES
//#############################################################################
#pragma region CAN_DEFINE
//-----------------------------------------------------------------------------
unsigned char bufferUDPtransmet[8];
unsigned char temporaryModuleBuffer[8];
unsigned char temporaryMasterBuffer[8];
/**
 * @brief Specify how to access the unsigned char array of 8 bytes which
 * contains your module's received CAN data.\n
 * this unique buffer must contain whatever info was received by your module's.
 * address
 */
#define MODULE_CAN_RX_BUFFER piloteUDP.readBuffer
/**
 * @brief Specify how to access the unsigned char array of 8 bytes which
 * contains received CAN data from the MASTER's address\n
 * this unique buffer must contain whatever info was received from the master's
 * address
 */
#define MASTER_CAN_RX_BUFFER piloteUDP.readBuffer
/**
 * @brief Specify how to access the unsigned char array of 8 bytes which
 * is used to send CAN data during the allocated time frame for your
 * module.\n
 * Example:
 * @code
 * #define MODULE_CAN_TX CANToTransmit
 * @endcode
 * @warning DO NOT PUT SEMI-COLONS IN THIS DEFINE
 */
#define MODULE_CAN_TX piloteUDP.replyBuffer
/**
 * @brief Specify how to request a CAN transmission to the other TimeBase
 * functions. This is either a flag or a function which tells other TimeBase
 * functions that their \ref MODULE_CAN_TX buffer is ready to be sent.\n
 * This can also be a function which sends the CAN directly through pilots
 * made for it. the disadvantage of using a dedicated function, is the lack
 * of address changing possibilities.
 * @code
 * // Example of Flag style:
 * #define MODULE_SEND_CAN CAN.Requete = REQUETE_ACTIVE
 * // Example of Function style:
 * #define MODULE_SEND_CAN pCAN1_transmetDesDonnes(0x111, MODULE_CAN_TX, 8)
 * @endcode
 * @warning DO NOT PUT SEMI-COLONS IN THIS DEFINE
 * @
 */
#define MODULE_SEND_CAN
#pragma endregion CAN_BUFFERS
//#############################################################################
#pragma region CODE_DEFINES
//-----------------------------------------------------------------------------
/**
 * @brief Statement which is true only if a CAN message addressed to your
 * module is available.
 * It is false if no messages have been received.
 * MUST CORRESPOND TO \ref MODULE_CAN_RX_BUFFER
 */
#define CHECK_MODULE_CAN_RECEPTION GetUDPSize()  // Doit etre a
/**
 * @brief Statement which is true only if a CAN message addressed to your
 * module is available.
 * It is false if no messages have been received.
 * MUST CORRESPOND TO \ref MASTER_CAN_RX_BUFFER
 */
#define CHECK_MASTER_CAN_RECEPTION 0xFF
#pragma endregion CODE_DEFINES
//#############################################################################
#pragma region PUBLIC_FUNCTIONS
//-----------------------------------------------------------------------------
/**
* @brief Function compressing data downwards in a buffer. It slides data downwards
* by 1 index if the one below the data is equal to 0xFF.
* @author Lyam / Shawn Couture
* @date 17/11/2022
* @param Buffer Pointer pointing the address of the buffer to update.
* @param sizeOfBuffer How big is the buffer referenced.
*/
void CB_UpdateBuffer(unsigned char* Buffer, unsigned char sizeOfBuffer);
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
void CB_QueueDataInBuffer(unsigned char* Buffer, unsigned char sizeOfBuffer, unsigned char* DataToCheck, unsigned char DataValueFromRefStruct);
/**
* @brief Function periodically called via the time base's interruptions. It is
* important to allocate a buffer address in your time base for this function.
* Do this via your main.h file, and ServiceCommunication.h.
* You will need to set SCOMMS_PARSE_RX_BUFFER_ADR to the appropriated number
* in your buffer.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param void Time base functions take no parameters
*/
void ServiceCommunication_RXParsingHandler(void);
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
void ServiceCommunication_TXParsingHandler(void);
/**
* @brief Function called which initialises all the structures necessary. it is
* important to call this function before main execution of the program starts
* as it is necessary to initialise all the data structure used by this service.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param void Initialisation functions take no parameters
*/
void ServiceCommunication_initialise(void);
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
void ModuleData_SetAll_ReceivedCommands(unsigned char ValueAppliedToAll);
/**
* @brief Sets the queued command structure (ModuleData.CommandsToSend) to
* the same input value. Useful to reset any queued commands when a new mode
* has been received from the master.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to UNUSED
*/
void ModuleData_SetAll_SentCommands(unsigned char ValueAppliedToAll);
/**
* @brief Sets the values to send structure of the ModuleData to the same value.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to UNUSED
*/
void ModuleData_SetAll_ValuesToSend(unsigned char ValueAppliedToAll);
/**
* @brief Sets all the received value structure to the same value.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to UNUSED
*/
void ModuleData_SetAll_ValuesReceived(unsigned char ValueAppliedToAll);
/**
* @brief Sets all the states in a \ref stStates structure to the same value.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param ValueAppliedToAll Value which will be applied to all commands not
* equal to \ref UNUSED
*/
void ModuleData_SetAll_StatesReceived(unsigned char ValueAppliedToAll);
/**
* @brief handles the units value sending for you to avoid sending 2 at the time
* and to automatically remove from QUEUE previous values.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param UnitsToPutInValues reference from \ref stValues Can also be \ref UNUSED
*/
void ModuleData_SetUnits(unsigned char UnitsToPutInValues);
/**
* @brief handles the disc color value sending for you to avoid sending 2 at the time
* and to automatically remove from QUEUE previous values.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param UnitsToPutInValues reference from \ref stValues Can also be \ref UNUSED
*/
void ModuleData_SetDiscColor(unsigned char ColorToPutInValues);
/**
* @brief handles the disc detection value sending for you to avoid sending 2 at the time
* and to automatically remove from QUEUE previous values.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param UnitsToPutInValues reference from \ref stValues Can also be \ref UNUSED
*/
void ModuleData_SetDiscDetection(unsigned char ColorToPutInValues);

void CheckIfUnused(unsigned char *checkedValue, unsigned char wantedNewValue);
/**
* @brief Function handling the count of interrupts and slot allocations for
* CAN communications made for this project. It is important to properly
* define clock speeds and oscillator speeds in ServiceCommunication.h
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param void
*/
void Parse_Interrupts(void);
#pragma endregion PUBLIC_FUNCTIONS
//#############################################################################
#pragma region REFERENCE_STRUCTURES
//-----------------------------------------------------------------------------
/**
 * @brief Struct containing all the possible states that a module can have.
 * This is a list of states and must not be changed, but only refered to.
 */
typedef struct
{
    /**
     * @brief Mode sent by the master when in need of an emergency stop proceedure. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D6 @endlink
     */
    unsigned char emergencyStop;
    /**
     * @brief Mode sent by the master to initiate a pause during operations. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D7 @endlink
     */
    unsigned char pause;
    /**
     * @brief Mode sent by the master to initiate the testing mode of modules. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D8 @endlink
     */
    unsigned char testing;
    /**
     * @brief Mode sent by the master to initiate the maintance proceedure. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D9 @endlink
     */
    unsigned char maintenance;
    /**
     * @brief Mode sent by the master to initiate the autonomous operation mode. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D10 @endlink
     */
    unsigned char operation;
    /**
     * @brief Mode sent by the master to initiate a calibration processus. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D11 @endlink
     */    
    unsigned char calibration;
    /**
     * @brief Mode sent by the master to reinitialise modules. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D12 @endlink
     */
    unsigned char reinitialisation;
}stModes;
/**
 * @brief Struct containing all the possible states that a module can have.
 * This is a list of states and must not be changed, but only referred to.
 */
typedef struct
{
    /**
     * @brief Indicates that the module is in an emergency stop proceedure. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D18 @endlink
     */
    unsigned char emergencyStop;
    /**
     * @brief Indicates that the module is paused during autonomous operations. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D19 @endlink
     */
    unsigned char paused;
    /**
     * @brief Indicates that the module is in a testing proceedure. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D20 @endlink
     */
    unsigned char testing;
    /**
     * @brief Indicates that the module is processing an action. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D21 @endlink
     */
    unsigned char processing;
    /**
     * @brief Indicates that the module is currently calibating itself. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D22 @endlink
     */
    unsigned char calibrating;
    /**
     * @brief Indicates that the module has finished the calibrating proceedure. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D23 @endlink
     */
    unsigned char calibrated;
    /**
     * @brief Indicates that the module is waiting for a command, without being in a peculiar state. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D24 @endlink
     */
    unsigned char waiting;
    /**
     * @brief Indicates that the module is safe to handle (maintenancemode). Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D25 @endlink
     */
    unsigned char safe;
    /**
     * @brief Indicates that the module is in an error state. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D26 @endlink
     */
    unsigned char error;
    /**
     * @brief Indicates that the module has arrived at the sorting factory. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D27 @endlink
     */
    unsigned char atSortingFactory;
    /**
     * @brief Indicates that the module has arrived at the weight station. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D28 @endlink
     */
    unsigned char atWeightStation;
    /**
     * @brief Indicates that the module has finished sorting and loaded the moving module with the disc it sorted. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D29 @endlink
     */
    unsigned char finishedSortingAndHasLoaded;
    /**
     * @brief Indicates that the module is waiting to begin the sorting proceeduer. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D30 @endlink
     */
    unsigned char waitingToSort;
    /**
     * @brief Indicates that the module is waiting to start the weighting process. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D31 @endlink
     */
    unsigned char waitingToWeight;
    /**
     * @brief Indicates that the module finished it's weighing process. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D32 @endlink
     */
    unsigned char finishedWeighting;
    /**
     * @brief Indicates that the module is empty. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D33 @endlink
     */
    unsigned char empty;
}stStates;
/**
 * @brief Struct containing all the possible commands that a module can have.
 * This is a list of commands and must not be changed, but only referred to.
 */
typedef struct
{
    /**
     * @brief Commands which makes a supportive module move supported hardware to the left. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D36 @endlink
     */
    unsigned char move_left;
    /**
     * @brief Commands which makes a supportive module move supported hardware to the right. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D37 @endlink
     */
    unsigned char move_right;
    /**
     * @brief Commands which makes a supportive module move supported hardware forwards. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D38 @endlink
     */
    unsigned char move_forward;
    /**
     * @brief Commands which makes a supportive module move supported hardware backwards. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D39 @endlink
     */
    unsigned char move_backward;
    /**
     * @brief Commands which makes a supportive module move supported hardware upwards. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D40 @endlink
     */
    unsigned char move_up;
    /**
     * @brief Commands which makes a supportive module move supported hardware downwards. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D41 @endlink
     */
    unsigned char move_down;
    /**
     * @brief Commands which makes a supportive module s u c c. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D42 @endlink
     */
    unsigned char suction_ON;
    /**
     * @brief Commands which makes a supportive module stop sucking. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D43 @endlink
     */
    unsigned char suction_OFF;
    /**
     * @brief Commands which makes a supportive module turn on it's light A. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D44 @endlink
     */
    unsigned char light_A_ON;
    /**
     * @brief Commands which makes a supportive module turn off it's light A. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D45 @endlink
     */
    unsigned char light_A_OFF;
    /**
     * @brief Commands which makes a supportive module turn on it's light B. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D46 @endlink
     */
    unsigned char light_B_ON;
    /**
     * @brief Commands which makes a supportive module turn off it's light B. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D47 @endlink
     */
    unsigned char light_B_OFF;
    /**
     * @brief Commands which makes a supportive module turn on it's light C. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D48 @endlink
     */
    unsigned char light_C_ON;
    /**
     * @brief Commands which makes a supportive module turn off it's light C. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D49 @endlink
     */
    unsigned char light_C_OFF;
    /**
     * @brief Commands which makes a supportive module turn on it's light D. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D50 @endlink
     */
    unsigned char light_D_ON;
    /**
     * @brief Commands which makes a supportive module turn off it's light D. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D51 @endlink
     */
    unsigned char light_D_OFF;
    /**
     * @brief Commands which makes a supportive module go to the sorting station. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D52 @endlink
     */
    unsigned char goto_SortingStation;
    /**
     * @brief Commands which makes a supportive module go to the weight station. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D53 @endlink
     */
    unsigned char goto_WeightStation;
    /**
     * @brief Commands which makes a supportive module force start it's sorting proceedure. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D54 @endlink
     */
    unsigned char start_Sorting;
    /**
     * @brief Commands which makes a supportive module force start it's weighting proceedure. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D55 @endlink
     */
    unsigned char start_Weighting;
    /**
     * @brief Commands which makes a supportive module force discharge it's containers. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D56 @endlink
     */
    unsigned char discharge;
    /**
     * @brief Commands which makes a supportive module switch to outputting values in metric. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D57 @endlink
     */
    unsigned char units_Metric;
    /**
     * @brief Commands which makes a supportive module switch to outputting values in imperial. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D58 @endlink
     */
    unsigned char units_Imperial;
}stCommands;
/**
 * @brief Struct containing all the possible values that a module can transmit.
 * This is a list of values and must not be changed, Only refer to it when you
 * need to set or change your module's structure values.
 */
typedef struct
{
    /**
     * @brief Value outputed on the bus to indicate the detection of a red disc. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D63 @endlink
     */
    unsigned char disc_Red;
    /**
     * @brief Value outputed on the bus to indicate the detection of a silver disc. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D64 @endlink
     */
    unsigned char disc_Silver;
    /**
     * @brief Value outputed on the bus to indicate the detection of a black disc. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D65 @endlink
     */
    unsigned char disc_Black;
    /**
     * @brief Value outputed on the bus to indicate that there is no colour data available. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D66 @endlink
     */
    unsigned char disc_NoColor;
    /**
     * @brief Value outputed on the bus to indicate the detection of a disc by the module. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D67 @endlink
     */
    unsigned char disc_Detected;
    /**
     * @brief Value outputed on the bus to indicate the loss of a previously detected disc. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D68 @endlink
     */
    unsigned char disc_Lost;
    /**
     * @brief Value outputed on the bus to indicate the detection of a disc went wrong as no disc could be detected when needed. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D69 @endlink
     */
    unsigned char disc_CouldNotBeFound;
    /**
     * @brief Value outputed on the bus to indicate that the module is currently using metric units for it's values. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D70 @endlink
     */
    unsigned char unit_Metric;
    /**
     * @brief Value outputed on the bus to indicate that the module is currently using imperial units for it's values. Full detailed description available at : 
     * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D71 @endlink
     */
    unsigned char unit_Imperial;
}stValues;
//#############################################################################
#pragma region EXTERNS
//-----------------------------------------------------------------------------
extern stModes Modes;
extern stStates States;
extern stCommands Commands;
extern stValues Values;
#pragma endregion EXTERNS
//-----------------------------------------------------------------------------
#pragma endregion REFERENCE_STRUCTURES
//#############################################################################
#pragma region MODULE_STRUCTURES
//-----------------------------------------------------------------------------
/**
 * @brief The actual structure used by the module. Used to get/set different
 * values and commands. For example, reading the Mode that the master sent.
 * Checking if receiving info from the CAN etc. Use DEFINES present in this
 * file in order to set Commands or values of such.
 */
typedef struct
{
    /**
     * @brief Structure which contains all the values a module can support
     * in a transmission. To specify you want to send a value, set it to
     * \ref QUEUE. Only set it to \ref QUEUE if you read that it is \ref AVAILABLE.
     */
    stValues ValuesToSend;
    /**
     * @brief Structure of all the commands a module can send.
     * To specify you want to send a command, set it to
     * \ref QUEUE. Only set it to \ref QUEUE if you read that it is \ref AVAILABLE.
     * If a command is set to \ref RECEIVED, it means a module communicated a
     * command request to you. If you support the command, before you start
     * to execute it, set it to \ref PARSED to tell the system that you parsed it.
     * If a command is equal to \ref NO_DATA, it means it has not been received.
     */
    stCommands CommandsToSend;
    /**
     * @brief Structure which contains all the values your module has received
     * If a specific value was received, you'll read \ref RECEIVED. If this is 
     * the case, and you needed to read this value, set it to \ref PARSED once 
     * you executed whatever was needed. These are set to \ref NO_DATA by 
     * default.
     */
    stValues ValuesReceived;
    /**
     * @brief Structure of all the commands a module can receive.
     * A command set to \ref RECEIVED means a module communicated a
     * command request to you. If you support the command, before you start
     * to execute it, set it to \ref PARSED to tell the system that you 
     * executed it. If the command is equal to \ref NO_DATA, it means 
     * it wasn't received.
     */
    stCommands CommandsReceived;
    /**
     * @brief Structure containing all the states that your module has received
     * from other modules or from the MASTER. These are reset to \ref NO_DATA 
     * when the \ref stModes received from the MASTER changes.
     */
    stStates StatesReceived;
    /**
     * @brief Indication of this module's state according to the communication
     * data sheet. This is sent each communication no matter what's
     * happening.
     */
    unsigned char State;
    /**
     * @brief Contains the received Mode from the MASTER synchronisation
     * slot. DO NOT CHANGE THIS VALUE. The code changes it by itself
     * upon receptions.
     */
    unsigned char Mode;
    /**
     * @brief Value from 0 to 254 either in KG or in Lbs. Set to \ref UNUSED
     * by default. If not set to \ref UNUSED, it will be sent each available
     * CAN slots.
     */
    unsigned char WeightToSend;
    /**
     * @brief Value from 0 to 254 either in KG or in Lbs. Set to \ref NO_DATA
     * by default. It will keep the last received weight in store until a new
     * Weight was received from an other module.
     */
    unsigned char ReceivedWeight;

    /**
    * @brief if this is set to anything else than 0x00 it means that the module
    * could not establish a connection with the synchronisation tram.
    * To detect a connection, you need to receive a \ref stModes.\n
    * When you receive an \ref stModes interrupt counts are reset to 0.
    */
    unsigned char CantConnect;

}stModuleData;
//#############################################################################
#pragma region MODULE_EXTERNS
//-----------------------------------------------------------------------------
extern stModuleData ModuleData;
#pragma endregion MODULE_EXTERNS
//-----------------------------------------------------------------------------
#pragma endregion MODULE_STRUCTURES

#endif