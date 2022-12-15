//piloteCAN
//Historique: 
// 2021-10-28, Yves Roy, creation

//INCLUSIONS
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
#include <fcntl.h>
#include <net/if.h>

#include "piloteCAN.h"

//Definitions privees
#define PF_CAN 29
#ifdef PILOTECAN_INTERFACE_VIRTUELLE
	#define PILOTECAN_INTERFACE "vcan0"
#endif

#ifdef PILOTECAN_INTERFACE_REELLE
	#define PILOTECAN_INTERFACE "can0"
#endif

#ifdef PILOTECAN_INTERFACE_REELLE_AVEC_LOOPBACK
	#define PILOTECAN_INTERFACE "can0"
#endif


//Declarations de fonctions privees:
void piloteCAN_gereUnSignal(int signo);

//Definitions de variables privees:
int piloteCAN_socket;
struct sockaddr_can piloteCAN_addr;//structure pour la mise en place du socket CAN
struct ifreq piloteCAN_ifr;			 //pour l'ouverture du socket CAN
struct can_frame piloteCAN_messageATransmettre; //contient l'adresse, les données et le nombre de données
struct can_frame piloteCAN_messageRecu; //contient l'adresse, les données et le nombre de données
struct can_filter piloteCAN_rfilter; //contient le filtre à utiliser en réception


//Definitions de fonctions privees:
void piloteCAN_gereUnSignal(int signo)
{
	printf("piloteCAN: signal reçu %d\n", signo);
	piloteCAN_etatDuModule = PILOTECAN_PAS_EN_FONCTION;
}

//Definitions de variables publiques:
int piloteCAN_etatDuModule;

//Definitions de fonctions publiques:
void piloteCAN_ouvreUneInterface(void)
{
#ifdef PILOTECAN_INTERFACE_VIRTUELLE
	printf("PILOTECAN_INTERFACE_VIRTUELLE\n");
	fflush(stdout);
	system("modprobe can");
	system("modprobe can-dev");
	system("modprobe can-raw");
	system("ip link add dev vcan0 type vcan");
	system("ip link set vcan0 up");
#endif
#ifdef PILOTECAN_INTERFACE_REELLE
	printf("sudo PILOTECAN_INTERFACE_REELLE\n");
	fflush(stdout);
	system("sudo modprobe can");
	system("sudo modprobe can-dev");
	system("sudo modprobe can-raw");
	system("sudo ip link set can0 type can restart-ms 5");
	system("sudo ip link set can0 up type can bitrate 50000");
	system("sudo ip link set can0 type can loopback off");
	
#endif
#ifdef PILOTECAN_INTERFACE_REELLE_AVEC_LOOPBACK
	printf("PILOTECAN_INTERFACE_VIRTUELLE_AVEC_LOOPBACK\n");
	fflush(stdout);
	system("modprobe can");
	system("modprobe can-dev");
	system("modprobe can-raw");
	system("ip link set can0 type can loopback on");
	system("ip link set can0 up type can bitrate 50000");//adaptez le "bitrate" au besoin
#endif
}

void piloteCAN_fermeUneInterface(void)
{
#ifdef PILOTECAN_INTERFACE_VIRTUELLE
	system("modprobe vcan");
	system("ip link set vcan0 down");
	system("ip link del dev vcan0");
#endif
#ifdef PILOTECAN_INTERFACE_REELLE
	system("sudo modprobe can");
	system("sudo ip link set can0 down");
	system("sudo ip link del dev can0");
#endif
#ifdef PILOTECAN_INTERFACE_REELLE_AVEC_LOOPBACK
	system("modprobe can");
	system("ip link set can0 down");
	system("ip link del dev can0");
#endif
}

int piloteCAN_transmet(unsigned long Adresse, unsigned char *TamponDeTransmission, unsigned char NombreATransmettre)
{
	unsigned char indice;
	
	piloteCAN_messageATransmettre.can_id = 0x401;
	piloteCAN_messageATransmettre.can_dlc = 8;
	for (indice = 0; indice < 8; indice++)
	{
		piloteCAN_messageATransmettre.data[indice] = TamponDeTransmission[indice];
	}
	return write(piloteCAN_socket, &piloteCAN_messageATransmettre, sizeof(piloteCAN_messageATransmettre));
}

int piloteCAN_recoitUnMessage(unsigned long *Adresse, unsigned char *TamponDeReception, unsigned char *NombreRecu)
{
unsigned char indice;
unsigned char nombre;
	
	//printf("RX\n");
	//fflush(stdout);	
	
	nombre = read(piloteCAN_socket, &piloteCAN_messageRecu, sizeof(piloteCAN_messageRecu));
	if (nombre < 0)
	{
		return -1;
	}
	
	*Adresse = piloteCAN_messageRecu.can_id;
	*NombreRecu = piloteCAN_messageRecu.can_dlc;
	for (indice = 0; indice < piloteCAN_messageRecu.can_dlc; indice++)
	{
		TamponDeReception[indice] = piloteCAN_messageRecu.data[indice];
		piloteCAN_messageRecu.data[indice] = 0;
		//printf("[%i]",TamponDeReception[indice]);
	}
	return nombre;
}

int piloteCAN_typeDeMessageRecu(void)
{
	if (piloteCAN_messageRecu.can_id & CAN_RTR_FLAG)
	{
		return PILOTECAN_MESSAGE_SANS_DONNEES;
	}
	return PILOTECAN_MESSAGE_AVEC_DONNEES;
}






int piloteCAN_initialise(void)
{
	signal(SIGTERM, piloteCAN_gereUnSignal);
	signal(SIGHUP, piloteCAN_gereUnSignal);
	
	piloteCAN_rfilter.can_id   = PILOTECAN_ADRESSE_EN_RECEPTION;
    piloteCAN_rfilter.can_mask = PILOTECAN_MASQUE_EN_RECEPTION;
	

	if ((piloteCAN_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) //ouverture du socket
	{
		perror("piloteCAN: erreur lors de la création du socket CAN");
		return 1;
	}
	
	setsockopt(piloteCAN_socket, SOL_CAN_RAW, CAN_RAW_FILTER, &piloteCAN_rfilter, sizeof(piloteCAN_rfilter));	
	
	piloteCAN_addr.can_family = PF_CAN; //on indique qu'on veut ouvrir un socket de type CAN
	strcpy(piloteCAN_ifr.ifr_name, PILOTECAN_INTERFACE); //on indique le nom de l'interface à utiliser
	ioctl(piloteCAN_socket, SIOCGIFINDEX, &piloteCAN_ifr); //création du socket
	piloteCAN_addr.can_ifindex = piloteCAN_ifr.ifr_ifindex; //sauvegarde de l'information qui découle de l'ouverture

	if (bind(piloteCAN_socket, (struct sockaddr *)&piloteCAN_addr, sizeof(piloteCAN_addr)) < 0) //association du socket
	{
		perror("piloteCAN: erreur lors de l'association (bind) du socket CAN");
		return 1;
	}
	piloteCAN_etatDuModule = PILOTECAN_EN_FONCTION;	
	
	fcntl(piloteCAN_socket, F_SETFL, fcntl(piloteCAN_socket, F_GETFL) | O_NONBLOCK);
	
	return 0;
}

