//testPiloteCAN: pour le développement de piloteSortie1
//======================================================== HISTORY // 
// 2019-12-14, Yves Roy, creation

//Description:
//Ce programme suppose que la librairie can-utils est installée
//Le programme ouvre une interface et la ferme avant de quitter

//Le programme utilise la définition CAN_VIRTUAL_INTERFACE pour savoir s'il doit utiliser vcan0
//Le programme utilise la définition CAN_REAL_INTERFACE pour savoir s'il doit utiliser can0

//Le programme transmet et reçoit des messages à l'aide du module piloteCAN


//--------------------------- Includes ---------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

#include <string.h>

#include "main.h"
#include "piloteCAN.h"
#include "interfacePipes.h"

//------------------------ Private Defines -----------------------//
#define CONTINUE 1
#define STOP 0
#define MAIN_BUFFER_SIZE 99
#define ERROR -1
#define SUCCESS 0

#define READING 0
#define WRITING 1
//----------------------- Private Functions ----------------------//
int Main_Initialise(void);
void Main_test(void);

void HandleTransmission(void);
void HandleReception(void);

int receptionToTransmission[2];
int transmissionToReception[2];

//----------------------- Private Variables ----------------------//:
//pas de variables privees

//----------------------- Private Functions ----------------------//
int Main_Initialise(void)
{
	CAN_OpenInterface();
	if (CAN_Initialise() != 0)
	{
		CAN_CloseInterface();
		return 1;
	}	
	return 0;
}


//----------------------- Public  Functions ----------------------//
//################################################################//
void HandleTransmission(void)
{
  FILE* file_TX;
  FILE* file_RX;

  char dataBuffer[MAIN_BUFFER_SIZE+1];
  char loop = CONTINUE;
  
  int addressToSend;
  char bytesToSend[8];
  char amountOfByteToSend;	

  unsigned char index;
  char command;  
  close(receptionToTransmission[WRITING]);
  close(transmissionToReception[READING]);
  
  file_RX = fdopen(receptionToTransmission[READING], "r");
  file_TX = fdopen(transmissionToReception[WRITING], "w");  
 
  addressToSend = 0x123;	//Address pour l'exemple
  amountOfByteToSend = 8;	//number pour l'exemple
  for (index = 0; index < amountOfByteToSend; index++)
  {
 	bytesToSend[index] = index*2;
  } 
  
	while (loop == CONTINUE)
	{
		printf("\nEntrez 'Q' et 'Enter' ou 'CTRL+C' pour quitter ou 'Enter' pour transmettre et recevoir un message\n");	
		command = getchar();
		printf("\n Commande recus\n");
		if (command == 'Q' || command == 'q')
		{
			loop = STOP;
		}
		
		// TRANSMIT ON CAN -----------------------------------------------------------------------//
		printf("Envoie du CAN\n");
		CAN_Transmit(addressToSend, bytesToSend, amountOfByteToSend);
		printf("SUCCESS\n");
		
        printf("Message transmis à l'Address 0x%x, longueur : %d, données: ", addressToSend, amountOfByteToSend);
		for (index = 0; index < amountOfByteToSend; index++)
		{
			printf("0x%02X ", bytesToSend[index]);
		}

		//Send command to reception
		dataBuffer[0] = command;
		printf("\nEnvoie vers le fils...");
    	Pipe_BufferToFile(dataBuffer, file_TX);
		printf("\nEnvoie terminée");
		
		// RECEIVE ON CAN -----------------------------------------------------------------------//
		printf("\nEn Attente du fils");
    	Pipe_FileToBuffer(file_RX, dataBuffer, sizeof(dataBuffer));
		printf("\nFils a répondu");    	
    	
    	printf("\nReceived data:\n");
    	for(int i=0; i<sizeof(dataBuffer); ++i)
    	{
			printf("0x%02X ",dataBuffer[i]);    		
    	}
		printf("\n");
		
		if (CAN_ModuleState == CAN_UNAVAILABLE)
		{
			loop = STOP;
		}		
	}
	
  close(receptionToTransmission[WRITING]);  
  close(transmissionToReception[READING]);
  printf("\nTransmission handler exited!");
}
//################################################################//
void HandleReception(void)
{
  FILE* file_TX;
  FILE* file_RX;

  char dataBuffer[MAIN_BUFFER_SIZE+1];
  char loop = CONTINUE;
  
  unsigned long receivedAddress;
  unsigned char bytesReceived[8];
  unsigned char amountOfBytesReceived;
  unsigned char index;
  close(transmissionToReception[WRITING]);
  close(receptionToTransmission[READING]);
  
  file_RX = fdopen(transmissionToReception[READING], "r");
  file_TX = fdopen(receptionToTransmission[WRITING], "w");  
  
	while (loop == CONTINUE)
	{
		// RECEIVE ON CAN ------------------------------------------------------------------------//	
		printf("\nEn Attente du pere");
		fflush(stdout);	
    	Pipe_FileToBuffer(file_RX, dataBuffer, sizeof(dataBuffer));
		printf("\nDonnées recus du pere!");
		fflush(stdout);		
	
		if (dataBuffer[0] == 'Q' || dataBuffer[0] == 'q')
		{
			printf("\nFILS QUIT\n");	
			loop = STOP;
			break;
		}
		
		printf("\nAttente du CAN...\n");		
		if (CAN_ReceiveMessage(&receivedAddress, bytesReceived, &amountOfBytesReceived) < 0)
		{
			CAN_CloseInterface();
			perror("erreur de lecture\n");
		}
		printf("\nSUCCESS de la reception du can...\n");
		
		if (CAN_TypeOfReceivedMessage() == CAN_MESSAGE_EMPTY)
		{
			printf("\npiloteCAN: message reçu sans données\n");
		}
		else
		{
			printf("\nMessage reçu. Address: 0x%x%x, longueur: %d, données: ", (unsigned int)(receivedAddress>>16), (unsigned int)(receivedAddress&0x0000FFFF), amountOfBytesReceived);
			for (index = 0; index < amountOfBytesReceived; index++)
			{
				printf("0x%02X ",bytesReceived[index]);
			}
		}
		
		// Transmit what we received to handler
		printf("\nEnvoie vers le pere");
		fflush(stdout);	
    	Pipe_BufferToFile(dataBuffer, file_TX);
		printf("\nEnvoie reussie");
		fflush(stdout);	
    	
		if (CAN_ModuleState == CAN_UNAVAILABLE)
		{
			loop = STOP;
		}
	}
	
  close(transmissionToReception[WRITING]);  
  close(receptionToTransmission[READING]);
  printf("\nReception handler exited!");	
}

//----------------------- Public  Functions ----------------------//
//pas de fonctions publiques

int main(void)
{
  //int addressToSend;
  //char bytesToSend[8];
  //char amountOfByteToSend;
  //unsigned long receivedAddress;
  //unsigned char bytesReceived[8];
  //unsigned char amountOfBytesReceived;


  pid_t processID;
  pipe(transmissionToReception);
  pipe(receptionToTransmission);
//////////////////////////////////////////////////////////////////////////////////////////////////// - Initialising modules
	system("modprobe vcan");
	system("ip link set vcan0 down");
	system("ip link del dev vcan0");	
	
	system("modprobe can");
	system("ip link set can0 down");
	system("ip link del dev can0");	
	
	if (Main_Initialise() != 0)
	{
		return -1;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////// - Initial quit message	

//////////////////////////////////////////////////////////////////////////////////////////////////// - WHILE LOOP	
	processID = fork();
	if(processID == (pid_t)0)
	{
    	HandleReception();
    	printf("\nReception Handler QUITTED");    
	}
	else
	{
    	HandleTransmission();		
    	wait(0);
    	printf("\nTransmission Handler QUITTED");     
	}

	printf("\nLast stopped program\n");
    CAN_CloseInterface();
	return 0;
}
