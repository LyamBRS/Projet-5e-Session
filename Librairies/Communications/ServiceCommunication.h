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
#define SCOMMS_BUFFER_ADR_PARSE_RX
/**
 * @brief The address allocated in the Time Base's execution buffer used by
 * this library for Transmitting checks.
 */
#define SCOMMS_BUFFER_ADR_PARSE_TX
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
 * @brief Defines a statement which is true only if a CAN message comming from
 * supported addresses is available. This is true if a message comming from
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
* @brief Function periodically called via the time  base's interrupt function 
* pointers buffer.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param void Time base functions take no parameters
*/
void ServiceCommunication_Handler(void);
/**
* @brief Function called which initialises all the structures necessary.
* @author Lyam / Shawn Couture
* @date 14/11/2022
* @param void Initialisation functions take no parameters
*/
void ServiceCommunication_initialise(void);
#pragma endregion PUBLIC_FUNCTIONS
//#############################################################################
#pragma region REFERENCE_STRUCTURES
//-----------------------------------------------------------------------------
/**
 * @brief Struct containing all the possible states that a module can have.
 * This is a list of states and must not be changed, but only refered to.
 */
typedef struct Modes
{
    unsigned char emergencyStop;               // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D6
    unsigned char pause;                       // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D7
    unsigned char testing;                     // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D8
    unsigned char maintnance;                  // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D9
    unsigned char operation;                   // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D10
    unsigned char calibration;                 // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D11
    unsigned char reinitialisation;            // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D12
};

/**
 * @brief Struct containing all the possible states that a module can have.
 * This is a list of states and must not be changed, but only refered to.
 */
typedef struct States
{
    unsigned char emergencyStop;               // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D18
    unsigned char stopped;                     // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D19
    unsigned char testing;                     // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D20
    unsigned char processing;                  // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D21
    unsigned char calibrating;                 // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D22
    unsigned char calibrated;                  // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D23
    unsigned char waiting;                     // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D24
    unsigned char safe;                        // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D25
    unsigned char error;                       // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D26
    unsigned char atSortingFactory;            // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D27
    unsigned char atWeightStation;             // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D28
    unsigned char finishedSortingAndHasLoaded; // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D29
    unsigned char waitingToSort;               // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D30
    unsigned char waitingToWeight;             // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D31
    unsigned char finishedWeighting;           // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D32
    unsigned char empty;                       // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D33
};
/**
 * @brief Struct containing all the possible commands that a module can have.
 * This is a list of commands and must not be changed, but only refered to.
 */
typedef struct Commands
{
    unsigned char move_left;                   // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D36
    unsigned char move_right;                  // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D37
    unsigned char move_forward;                // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D38
    unsigned char move_backward;               // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D39
    unsigned char move_up;                     // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D40
    unsigned char move_down;                   // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D41
    unsigned char suction_ON;                  // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D42
    unsigned char suction_OFF;                 // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D43
    unsigned char light_A_ON;                  // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D44
    unsigned char light_A_OFF;                 // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D45
    unsigned char light_B_ON;                  // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D46
    unsigned char light_B_OFF;                 // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D47
    unsigned char light_C_ON;                  // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D48
    unsigned char light_C_OFF;                 // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D49
    unsigned char light_D_ON;                  // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D50
    unsigned char light_D_OFF;                 // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D51
    unsigned char goto_SortingStation;         // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D52
    unsigned char goto_WeightStation;          // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D53
    unsigned char start_Sorting;               // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D54
    unsigned char start_Weighting;             // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D55
    unsigned char discharge;                   // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D56
    unsigned char units_Metric;                // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D57
    unsigned char units_Imperial;              // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D58
};
/**
 * @brief Struct containing all the possible values that a module can transmit.
 * This is a list of values and must not be changed, Only refer to it when you
 * need to set or change your module's structure values.
 */
typedef struct Values
{
    unsigned char disc_Red;                    // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D63
    unsigned char disc_Silver;                 // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D64
    unsigned char disc_Black;                  // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D65
    unsigned char disc_NoData;                 // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D66
    unsigned char disc_Detected;               // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D67
    unsigned char disc_Lost;                   // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D68
    unsigned char disc_CouldNotBeFound;        // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D69
    unsigned char unit_Metric;                 // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D70
    unsigned char unit_Imperial;               // https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D71
};
#pragma endregion REFERENCE_STRUCTURES
#endif