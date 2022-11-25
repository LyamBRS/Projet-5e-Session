/**
 * @file main.c
 * @author Shawn Couture / LyamBRS
 * @brief This file's purpose is to handle a terminal communication
 * between the CommandCenter.exe program and a beagleBoneBlue.
 * it parses what is received in the terminal and outputs CAN once
 * a proper data tram is received.\n\n
 * Data trams are as followed:\n
 * 0xFE/ADR1/ADR2/ADR3/'M'/Mode/C1/command1/C2/command2/'S'/State\n
 * Each time a data tram is sent, [-SYNC-] is shown on the terminal.
 * @version 2.1
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */


//--------------------------- Includes ---------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "main.h"
#include "piloteCAN.h"

//------------------------ Private Defines -----------------------//
#define CONTINUE 1
#define STOP 0
#define MAIN_BUFFER_SIZE 99
#define ERROR -1
#define SUCCESS 0
#define END_EVERYTHING 0xFF // 50111

#define READING 0
#define WRITING 1
#define NOT_READY 0x00
#define READY 0xFF
//----------------------- Private Functions ----------------------//
int Main_Initialise(void);
void Main_test(void);

void HandleTransmission(void);
void HandleReception(void);

int GetHexValue(unsigned char charcter);
unsigned char CheckIfSpecialChar(int special, int* Temporary2LetterBuffer);

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

int GetHexValue(unsigned char character)
{
	switch(character)
	{
		case('0'): return 0; break;
		case('1'): return 1; break;
		case('2'): return 2; break;
		case('3'): return 3; break;
		case('4'): return 4; break;
		case('5'): return 5; break;
		case('6'): return 6; break;
		case('7'): return 7; break;
		case('8'): return 8; break;
		case('9'): return 9; break;
		case('A'): return 0x0A; break;
		case('B'): return 0x0B; break;
		case('C'): return 0x0C; break;
		case('D'): return 0x0D; break;
		case('E'): return 0x0E; break;
		case('F'): return 0x0F; break;
	}

	return(0xFF);
}
/**
 * @brief 
 * 
 * @author Shawn Couture / LyamBRS
 * @date 24/11/2022
 * @param special current gotten getChar (int)
 * @param Temporary2LetterBuffer 2 letters int buffer which corresponds to the output of this functions.
 * @return unsigned char: 0xFF = Buffer ready for parsing, 0x00 Buffer processing.
 */
unsigned char CheckIfSpecialChar(int special, int* Temporary2LetterBuffer)
{
	static unsigned char checking = 0;

	// If the second character is above regular characters, it means we received a special one.
	if(special >= 0xA0 && checking)
	{
		int output = (Temporary2LetterBuffer[0] << 8) + special;
		output = output - 49873;

		Temporary2LetterBuffer[0] = output;
		Temporary2LetterBuffer[1] = 0xFFF;
		checking = 0x00;
		return READY;
	}

	//Second value has nothing special but the first one did.
	//We return both the letters as is.
	if(checking && special <= 0x7F)
	{
		Temporary2LetterBuffer[1] = special;
		checking = 0x00;
		return READY;
	}

	// Check if the value is above 0xC1 meaning the potential start of a special character. 
	if(special >= 0xC1 && !checking)
	{
		checking = 0xFF;
		Temporary2LetterBuffer[0] = special;
		return NOT_READY;
	}

	// We are not checking for special values and the current one isn't special.
	if(special < 0xA0)
	{
		checking = 0x00;
		Temporary2LetterBuffer[0] = special;
		Temporary2LetterBuffer[1] = 0xFF;
		return READY;
	}
	return READY;
}


//----------------------- Public  Functions ----------------------//
//################################################################//
void HandleTransmission(void)
{
  //int file_TX;
  //int file_RX;

  unsigned char dataBuffer[MAIN_BUFFER_SIZE+1];
  unsigned char loop = CONTINUE;
  
  //------------------------------------------------------------// CAN ADDRESS
  unsigned char bytesToSend[8];
  unsigned char dataFromCommandCenter[12];
  int LettersBuffers[2];
  char amountOfByteToSend;

  int rawCharacter = 0;

  unsigned char index = 0;
  close(receptionToTransmission[WRITING]);
  close(transmissionToReception[READING]);
  
  //file_RX = fdopen(receptionToTransmission[READING], "r");
  //file_TX = fdopen(transmissionToReception[WRITING], "w");
  fcntl(transmissionToReception[READING], F_SETFL, fcntl(transmissionToReception[READING], F_GETFL) | O_NONBLOCK);
 

  amountOfByteToSend = 8;	//number pour l'exemple
  for (index = 0; index < amountOfByteToSend; index++)
  {
 	bytesToSend[index] = index*2;
  } 
  //------------------------------------------------------------//
	while (loop == CONTINUE)
	{
		dataBuffer[0] = loop;
		write(transmissionToReception[WRITING],dataBuffer,2);

		// TRANSMIT ON CAN -----------------------------------------------------------------------//
		index = 0;
		while(index < 13)
		{
			//Compare letters in groups of 2 if special, groups of 1 when not.
			for(int i=0; i<2; ++i)
			{
				rawCharacter = getchar();
				unsigned char gotoNextStep = CheckIfSpecialChar(rawCharacter, LettersBuffers);

				if(gotoNextStep == 0xFF) {break;}
			}

			//Check what is within the table
			for(int i=0; i<2; ++i)
			{
				rawCharacter = LettersBuffers[i];
				if(rawCharacter != 0xFFF)
				{

					if(rawCharacter == 0xFE)
					{
						index = 0;
					}
					else
					{
						if(rawCharacter == END_EVERYTHING)
						{
							loop = END_EVERYTHING;
							index = 12;
							break;
						}
						printf("[%i]: %i\n",index,rawCharacter);
						fflush(stdout);
						// Store chars in buffer
						dataFromCommandCenter[index] = ((unsigned char)rawCharacter);
						index++;
					}
				}
			}
			sleep(0.01);
		}

		if(loop == CONTINUE)
		{
			printf("[-SYNC-]\n");
			// PARSE ADDRESS TO USE -----------------------------------------------------------------------//	
			int address = 0;
			int hundreds = GetHexValue(dataFromCommandCenter[1]);
			int tens     = GetHexValue(dataFromCommandCenter[2]);
			int units    = GetHexValue(dataFromCommandCenter[3]);

			address = address + (hundreds << 8);
			address = address + (tens << 4);
			address = address + units;

			// Prep Can -----------------------------------------------------------------------//
			for(int i=0;i<8;++i)
			{
				bytesToSend[i] = dataFromCommandCenter[4+i];
			}
			CAN_Transmit(address, bytesToSend, 8);
		}
		else
		{
			printf("[-TX END-]\n");			
		}

		if (CAN_ModuleState == CAN_UNAVAILABLE)
		{
			loop = STOP;
			printf("[-TX CAN ERROR-]\n");
		}		

		//Send command to reception
		for(int i=0; i<MAIN_BUFFER_SIZE; ++i)
		{
			dataBuffer[i] = loop;
		}
		write(transmissionToReception[WRITING],dataBuffer,2);
    	//Pipe_BufferToFile(dataBuffer, file_TX);
		fflush(stdout);	
	}	
	close(receptionToTransmission[WRITING]);  
	close(transmissionToReception[READING]);
	printf("\nTransmission handler exited!\n");
}
//################################################################//
void HandleReception(void)
{
  //int file_TX;
  //int file_RX;

  unsigned char dataBuffer[MAIN_BUFFER_SIZE+1];
  unsigned char loop = CONTINUE;
  
  unsigned long receivedAddress;
  unsigned char bytesReceived[8];
  unsigned char amountOfBytesReceived;
  unsigned char index;
  close(transmissionToReception[WRITING]);
  close(receptionToTransmission[READING]);
  
  //file_RX = fdopen(transmissionToReception[READING], "r");
  //file_TX = fdopen(receptionToTransmission[WRITING], "w"); 
  fcntl(transmissionToReception[READING], F_SETFL, fcntl(transmissionToReception[READING], F_GETFL) | O_NONBLOCK); 
  


	while (loop == CONTINUE)
	{
		// RECEIVE ON CAN ------------------------------------------------------------------------//	
    	read(transmissionToReception[READING],dataBuffer,2);
	
		sleep(1);
		printf("\nRX: %i\n",dataBuffer[0]);
		fflush(stdout);

		if (dataBuffer[0] == STOP)
		{
			printf("[-RX END-]\n");
			fflush(stdout);	
			loop = STOP;
			break;
		}

		int number = CAN_ReceiveMessage(&receivedAddress, bytesReceived, &amountOfBytesReceived);
		if (number < 0)
		{
			//printf("[-RX CAN ERROR-]\n");
		}
		if(number > 0)
		{
			printf("[RX]:,");
			printf("%li,",receivedAddress);
			for (index = 0; index < amountOfBytesReceived; index++)
			{
				printf("%i,",bytesReceived[index]);
			}
			printf("\n");
			fflush(stdout);		
		}
	}
  	CAN_CloseInterface();	
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
	system("sudo modprobe vcan");
	system("sudo ip link set vcan0 down");
	system("sudo ip link del dev vcan0");	
	
	system("sudo modprobe can");
	system("sudo ip link set can0 down");
	system("sudo ip link del dev can0");	
	
	if (Main_Initialise() != 0)
	{
		return -1;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////// - Initial quit message	
	printf("\n[-STARTING-]");
	fflush(stdout);	
	sleep(1);
	printf("\n");
	fflush(stdout);	
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
    	wait((int*) 1);
    	printf("\nTransmission Handler QUITTED");     
	}

	printf("\n[-EXECUTION STOPPED-]\n");
    CAN_CloseInterface();
	return 0;
}
