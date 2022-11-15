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
#pragma region SERVICECOMMUNICATION_DEFINES
//-----------------------------------------------------------------------------
/**
 * @brief Means that the value or commands is not used by this specific module.
 * This is important as the functions use this to figure out which data needs
 * to be send when a CAN slot is available for the module
 */
#define UNUSED 0xFF
//-----------------------------------------------------------------------------
/**
 * @brief Specifies that you want this specific command queued for transmission
 */
#define QUEUE 0xFE
/**
 * @brief Specifies that the command is already in queue for transmission.
 * DO NOT PUT IT BACK IN QUEUE WHEN THE COMMAND IS EQUAL TO THIS.
 */
#define IN_QUEUE 0xFD
/**
 * @brief tells you that this command is AVAILABLE for a QUEUE request.
 */
#define AVAILABLE 0xAA
//-----------------------------------------------------------------------------
/**
 * @brief Tells you that you received a request for the execution of this
 * specific command.
 */
#define RECEIVED 0xBB
/**
 * @brief Tells the program that you parsed the RECEIVED command
 */
#define PARSED 0xAA
/**
 * @brief Tells you that no requests have been received for this specific
 * command.
 */
#define NO_DATA 0x00
//-----------------------------------------------------------------------------
#pragma endregion CAN_BUFFERS
//#############################################################################
#pragma region MAIN_REDEFINES
//-----------------------------------------------------------------------------
/**
 * @brief The time base frequency. Usually defined in main.h
 * Used to automatically calculate CAN slots allocations.
 */
#define TIME_BASE_FREQUENCY_HZ 2000
/**
 * @brief The time base's functions buffer size. Usually defined in main.h.
 * Used to figure out the intervals at which the execute function is called
 * to calculate slot's time frames for the CAN protocol.
 */
#define TIME_BASE_BUFFER_SIZE 7
/**
 * @brief The address allocated in the Time Base's execution buffer used by
 * this library for receptions parsings.
 */
#define SCOMMS_PARSE_RX_BUFFER_ADR
/**
 * @brief The address allocated in the Time Base's execution buffer used by
 * this library for Transmitting checks.
 */
#define SCOMMS_PARSE_TX_BUFFER_ADR
/**
 * @brief The allocated slot for your module considering that the 
 * synchronisation slot is 0. Please refer to the datasheet available on
 * google drive in order to figure out your module's time frame.
 */
#define CAN_TIME_FRAME
#pragma endregion MAIN_REDEFINES
//#############################################################################
#pragma region CAN_DEFINE
//-----------------------------------------------------------------------------
/**
 * @brief Specify how to access the unsigned char array of 8 bytes which
 * contains the received CAN data from the global SYNCHRONISATION address.
 */
#define SYNC_CAN_RX_BUFFER
/**
 * @brief Specify how to access the unsigned char array of 8 bytes which
 * contains the received CAN data from the your module's own address
 */
#define MODULE_CAN_RX_BUFFER
/**
 * @brief Specify how to access the unsigned char array of 8 bytes which
 * is used to send CAN data during the allocated time frame for your
 * module
 */
#define MODULE_CAN_TX_BUFFER
#pragma endregion CAN_BUFFERS
//#############################################################################
#pragma region CODE_DEFINES
//-----------------------------------------------------------------------------
/**
 * @brief Defines a statement which is true only if a CAN message coming from
 * supported addresses is available. This is true if a message coming from
 * any supported addresses by the module is available. It is false if no
 * messages have been received.
 * MUST CORRESPOND TO SYNC_CAN_RX_BUFFER
 */
#define CHECK_CAN_RECEPTION pCAN1_messageDisponible()
#pragma endregion CODE_DEFINES
//#############################################################################
#pragma region PUBLIC_FUNCTIONS
//-----------------------------------------------------------------------------
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
* equal to UNUSED
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
* @brief Function checking if a variable is equal to UNUSED. If not, it
* sets it to a new value.
* @author Lyam / Shawn Couture
* @date 15/11/2022
* @param checkedValue pointer (&variable) pointing to a data in a structure
* @param wantedNewValue value which the data pointed will be set to if not UNUSED
*/
void CheckIfUnused(unsigned char *checkedValue, unsigned char wantedNewValue);
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
     * QUEUE. Only set it to QUEUE if you read that it is AVAILABLE.
     */
    stValues ValuesToSend;
    /**
     * @brief Structure of all the commands a module can send.
     * To specify you want to send a command, set it to
     * QUEUE. Only set it to QUEUE if you read that it is AVAILABLE.
     * If a command is set to RECEIVED, it means a module communicated a
     * command request to you. If you support the command, before you start
     * to execute it, set it to PARSED to tell the system that you parsed it.
     * If a command is equal to NO_DATA, it means it has not been received.
     */
    stCommands CommandsToSend;
    /**
     * @brief Structure which contains all the values your module has received
     * If a specific value was received, you'll read RECEIVED. If this is the
     * case, and you needed to read this value, set it to PARSED once you
     * executed whatever was needed. These are set to NO_DATA by default.
     */
    stValues ValuesReceived;
    /**
     * @brief Structure of all the commands a module can receive.
     * A command set to RECEIVED means a module communicated a
     * command request to you. If you support the command, before you start
     * to execute it, set it to PARSED to tell the system that you executed it.
     * If the command is equal to NO_DATA, it means it wasn't received.
     */
    stCommands CommandsReceived;
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
     * @brief Value from 0 to 254 either in KG or in Lbs. Set to UNUSED
     * by default. If not set to UNUSED, it will be sent each available
     * CAN slots.
     */
    unsigned char Weight;
}stModuleData;
//#############################################################################
#pragma region MODULE_EXTERNS
//-----------------------------------------------------------------------------
extern stModuleData ModuleData;
#pragma endregion MODULE_EXTERNS
//-----------------------------------------------------------------------------
#pragma endregion MODULE_STRUCTURES

#endif