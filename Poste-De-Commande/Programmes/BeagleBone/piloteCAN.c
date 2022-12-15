/**
 * @file piloteCAN.c
 * @author Yves Roy
 * @brief Contains the code necessary to interface with the CAN stuff of a beagleBoneBlue.\n
 * Modified by Shawn Couture:\n
 * - File is now coded with an universally accessible language (english)\n
 * - 
 * @version 2.0
 * @date 2022-11-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//piloteCAN
//======================================================== HISTORY //  
// 2021-10-28, Yves Roy, creation

//--------------------------- Includes ---------------------------//
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h> 
#include <linux/can/raw.h>
#include <net/if.h>
#include <fcntl.h>

#include "piloteCAN.h"

//------------------------ Private Defines -----------------------//
#define PF_CAN 29
#ifdef CAN_VIRTUAL_INTERFACE
	#define CAN_INTERFACE "vcan0"
#endif

#ifdef CAN_REAL_INTERFACE
	#define CAN_INTERFACE "can0"
#endif

#ifdef CAN_REAL_WITH_LOOPBACK
	#define CAN_INTERFACE "can0"
#endif


//----------------------- Private Functions ----------------------//
void CAN_HandleSignal(int signo);

//----------------------- Private Variables ----------------------//:
int CAN_socket;
struct sockaddr_can CAN_Address;//structure pour la mise en place du socket CAN
struct ifreq CAN_ifr;			 //pour l'ouverture du socket CAN
struct can_frame CAN_messageToSend; //contient l'Address, les données et le number de données
struct can_frame CAN_receivedMessage; //contient l'Address, les données et le number de données
struct can_filter CAN_rFilter; //contient le filtre à utiliser en réception
//----------------------- Private Functions ----------------------//
void CAN_HandleSignal(int signo)
{
	printf("piloteCAN: signal reçu %d\n", signo);
	CAN_ModuleState = CAN_UNAVAILABLE;
}

//----------------------- Public  Functions ----------------------//
int CAN_ModuleState;

//----------------------- Public  Functions ----------------------//
void CAN_OpenInterface(void)
{
#ifdef CAN_VIRTUAL_INTERFACE
	printf("CAN_VIRTUAL_INTERFACE\n");
	fflush(stdout);
	system("sudo modprobe can");
	system("sudo modprobe can-dev");
	system("sudo modprobe can-raw");
	system("sudo ip link add dev vcan0 type vcan");
	system("sudo ip link set vcan0 up");
#endif
#ifdef CAN_REAL_INTERFACE
	printf("CAN_REAL_INTERFACE\n");
	fflush(stdout);
	system("sudo modprobe can");
	system("sudo modprobe can-dev");
	system("sudo modprobe can-raw");
	system("sudo ip link set can0 type can restart-ms 5");
	system("sudo ip link set can0 type can loopback off");	
	system("sudo ip link set can0 up type can bitrate 50000");
	system("sudo ip link set can0 type can restart-ms 20");
	system("sudo ip link set can0 type can restart-ms 20");
	system("sudo ip link set can0 type can restart-ms 20");
#endif
#ifdef CAN_REAL_WITH_LOOPBACK

	printf("PILOTECAN_INTERFACE_VIRTUELLE_AVEC_LOOPBACK\n");
	fflush(stdout);
	system("modprobe can");
	system("modprobe can-dev");
	system("modprobe can-raw");
	system("ip link set can0 type can loopback on");
	system("ip link set can0 up type can bitrate 50000");//adaptez le "bitrate" au besoin

#endif
}

void CAN_CloseInterface(void)
{
#ifdef CAN_VIRTUAL_INTERFACE
	system("sudo modprobe vcan");
	system("sudo ip link set vcan0 down");
	system("sudo ip link del dev vcan0");
#endif
#ifdef CAN_REAL_INTERFACE
	system("sudo modprobe can");
	system("sudo ip link set can0 down");
	system("sudo ip link del dev can0");
#endif
#ifdef CAN_REAL_WITH_LOOPBACK
	system("sudo modprobe can");
	system("sudo ip link set can0 down");
	system("sudo ip link del dev can0");
#endif
}
//################################################################//
/**
* @brief Function setting all values in an array to the same input value.
* @author Yves Roy
* @date 24/11/2022
 * @param Address Can address to use 11 bits
 * @param transmitBuffer char buffer of 8 bytes
 * @param NumberToSend 8
 * @return int 
*/
int CAN_Transmit(unsigned long Address, unsigned char *transmitBuffer, unsigned char NumberToSend)
{
unsigned char index;

	CAN_messageToSend.can_id = Address;
	CAN_messageToSend.can_dlc = NumberToSend;
	for (index = 0; index < NumberToSend; index++)
	{
		CAN_messageToSend.data[index] = transmitBuffer[index];
	}
	return write(CAN_socket, &CAN_messageToSend, sizeof(CAN_messageToSend));
}
//################################################################//
/**
 * @brief Function returning data if a CAN message was sent to this
 * specified address
 * @author Yves Roy
 * @date 24/11/2022
 * @param Address 11 bits CAN address to check for RX messages
 * @param receiveBuffer char buffer of 8 bytes
 * @param amountOfBytesReceived 8
 * @return int 
 */
int CAN_ReceiveMessage(unsigned long *Address, unsigned char *receiveBuffer, unsigned char *amountOfBytesReceived)
{
unsigned char index;
int number;
	
	number = read(CAN_socket, &CAN_receivedMessage, sizeof(CAN_receivedMessage));

	if (number < 0)
	{
		return -1;
	}

	*Address = CAN_receivedMessage.can_id;
	*amountOfBytesReceived = CAN_receivedMessage.can_dlc;
	for (index = 0; index < CAN_receivedMessage.can_dlc; index++)
	{
		receiveBuffer[index] = CAN_receivedMessage.data[index];
	}
	return number;
}
//################################################################//
//################################################################//
int CAN_TypeOfReceivedMessage(void)
{
	if (CAN_receivedMessage.can_id & CAN_RTR_FLAG)
	{
		return CAN_MESSAGE_EMPTY;
	}
	return CAN_MESSAGE_WITH_DATA;
}
//################################################################//
/**
 * @brief Initialises the pilote for BeagleBoneBlue code.
 * @author Yves Roy
 * @date 24/11/2022
 * @return int 
 */
int CAN_Initialise(void)
{
	signal(SIGTERM, CAN_HandleSignal);
	signal(SIGHUP, CAN_HandleSignal);
	
	CAN_rFilter.can_id   = CAN_RECEIVING_ADDRESS;
    CAN_rFilter.can_mask = CAN_RECEIVING_MASK;
	

	if ((CAN_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) //ouverture du socket
	{
		perror("piloteCAN: erreur lors de la création du socket CAN");
		return 1;
	}
	
	setsockopt(CAN_socket, SOL_CAN_RAW, CAN_RAW_FILTER, &CAN_rFilter, sizeof(CAN_rFilter));	
	
	CAN_Address.can_family = PF_CAN; //on indique qu'on veut ouvrir un socket de type CAN
	strcpy(CAN_ifr.ifr_name, CAN_INTERFACE); //on indique le nom de l'interface à utiliser
	ioctl(CAN_socket, SIOCGIFINDEX, &CAN_ifr); //création du socket
	CAN_Address.can_ifindex = CAN_ifr.ifr_ifindex; //sauvegarde de l'information qui découle de l'ouverture

	if (bind(CAN_socket, (struct sockaddr *)&CAN_Address, sizeof(CAN_Address)) < 0) //association du socket
	{
		perror("piloteCAN: erreur lors de l'association (bind) du socket CAN");
		return 1;
	}
	CAN_ModuleState = CAN_WORKING;

  	fcntl(CAN_socket, F_SETFL, fcntl(CAN_socket, F_GETFL) | O_NONBLOCK); 

	////////////////////////////////////////////////////////////////////////////////////// - STACKOVERFLOW
	//can_err_mask_t optval = CAN_ERR_MASK;
	//setsockopt(CAN_socket, SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &optval, sizeof(optval));
	/////////////////////////////////////////////////////////////////////////////////////

	return 0;
}

