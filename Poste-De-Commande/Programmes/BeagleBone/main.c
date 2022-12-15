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
/**
 * @brief This function is used to initialise every pilotes or interfaces
 * needed in order to properly execute this program.\n
 * In this particular state, it opens CAN interfaces and initialises the
 * latter properly.
 * @author Yves Roy
 * @date 28/11/2022
 * @return int Error State.
 */
int Main_Initialise(void);
void Main_test(void);
/**
 * @brief Handles the CAN transmission on the CAN bus.\n
 * The command center handles how often SYNCH trams are to be sent.\n
 * Each time a synch tram is sent, [-SYNC-] is shown in the terminal.
 * @author Shawn Couture / LyamBRS
 * @date 24/11/2022
 */
void HandleTransmission(void);
/**
 * @brief handles CAN receptions. Each time a CAN communication is
 * intercepted, it gets printed as integers displayed as ASCII chars
 * in the terminal, with [RX] in front of the data.\n
 * Data is separated via commas to ease parsing on the CommandCenter.
 * @author Shawn Couture / LyamBRS
 * @date 24/11/2022
 */
void HandleReception(void);
/**
 * @brief Returns the real hexadecimal value of the ascii letter which represents
 * said hex value.\n
 * For example, 'F' does not equal to 0x0F.\n
 * Thus this function takes 'F' as the input parameter, and returns 0x0F.
 * @author Shawn Couture / LyamBRS
 * @date 24/11/2022
 * @param character ASCII to transform into hexadecimal. (0x00-0x0F).
 * @return int Represents the hexadecimal value of the ascii letters converted to hex.
 */
int GetHexValue(unsigned char charcter);
unsigned char CheckIfSpecialChar(int special, int* Temporary2LetterBuffer);

int receptionToTransmission[2];
int transmissionToReception[2];

int CAN_IsSending = 0;
int CAN_IsReading = 0;

//----------------------- Private Variables ----------------------//:
/**
 * @brief Tells the program that special characters will be used
 * instead of exact hex values through the terminal.\n
 * In regular operation, the Command Center sends exact hex values
 * properly to the application, but it is impossible for a manual
 * user using this script through a terminal to send exact hex values.\n
 * This this allows just that.
 */
unsigned char ManualExecution = 0;

//----------------------- Private Functions ----------------------//
/**
 * @brief This function is used to initialise every pilotes or interfaces
 * needed in order to properly execute this program.\n
 * In this particular state, it opens CAN interfaces and initialises the
 * latter properly.
 * @author Yves Roy
 * @date 28/11/2022
 * @return int Error State.
 */
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
/**
 * @brief Returns the real hexadecimal value of the ascii letter which represents
 * said hex value.\n
 * For example, 'F' does not equal to 0x0F.\n
 * Thus this function takes 'F' as the input parameter, and returns 0x0F.
 * @author Shawn Couture / LyamBRS
 * @date 24/11/2022
 * @param character ASCII to transform into hexadecimal. (0x00-0x0F).
 * @return int Represents the hexadecimal value of the ascii letters converted to hex.
 */
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
 * @brief Checks if 2 consecutive characters are meant to represent a
 * special character. While this function is far from perfect, considering the structure
 * of the CAN protocol used by this device, it works just fine.\n
 * This function allows values upwards of 0x7F to 0xFF to be sent exclusively through
 * terminal getChar().\n
 * Why? Cuz I was lazy and couldn't be bothered to make the actual USB function.
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
	if(special >= 0xA0 && checking && ManualExecution)
	{
		int output = (Temporary2LetterBuffer[0] << 8) + special;
		output = output - 49856;

		Temporary2LetterBuffer[0] = output;
		Temporary2LetterBuffer[1] = 0xFFF;
		checking = 0x00;
		return READY;
	}

	//Second value has nothing special but the first one did.
	//We return both the letters as is.
	if(checking && special <= 0x7F && ManualExecution)
	{
		Temporary2LetterBuffer[1] = special;
		checking = 0x00;
		return READY;
	}

	// Check if the value is above 0xC1 meaning the potential start of a special character. 
	if(special >= 0xC1 && !checking && ManualExecution)
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
		Temporary2LetterBuffer[1] = 0xFFF;
		return READY;
	}
	return READY;
}


//----------------------- Public  Functions ----------------------//
//################################################################//
/**
 * @brief Handles the CAN transmission on the CAN bus.\n
 * The command center handles how often SYNCH trams are to be sent.\n
 * Each time a synch tram is sent, [-SYNC-] is shown in the terminal.
 * @author Shawn Couture / LyamBRS
 * @date 24/11/2022
 */
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
  unsigned char TransmitCan = 0;

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

	LettersBuffers[0] = 0xFFF;
	LettersBuffers[1] = 0xFFF;
	TransmitCan = 0;
  //------------------------------------------------------------//
	while (loop == CONTINUE)
	{
		dataBuffer[0] = loop;
		write(transmissionToReception[WRITING],dataBuffer,2);

		// GET MASTER CAN -----------------------------------------------------------------------//
		index = 0;
		TransmitCan = 1;
		while(index < 13)
		{
			//Compare letters in groups of 2 if special, groups of 1 when not.
			if(!ManualExecution)
			{
				rawCharacter = getchar();
				//printf("[%i]: %i ",index,rawCharacter);
				
				if(rawCharacter >= 0xDB && rawCharacter <= 0xFA)
				{rawCharacter = rawCharacter - 0xDB;}

				if(rawCharacter == 0xFF)
				{
					printf("\n[-QUIT-]\n");	
					index = 13;
					loop = STOP;
					TransmitCan = 0;
					break;
				}
				else
				{
					if(rawCharacter == 0xFE)
					{
						if(index != 0)
						{
							printf("\n[-AUTO RESET-]");
						}
						index = 0;
						dataFromCommandCenter[index] = ((unsigned char)rawCharacter);
						index = 1;						
					}
					else
					{
						dataFromCommandCenter[index] = ((unsigned char)rawCharacter);
						index++;
						if(index>12)
						{
							TransmitCan = 1;

							//If the last character is not \n or EOF, clear getChar buffer
							if((unsigned char)rawCharacter != '\n' && (unsigned char)rawCharacter != '\r')
							{
								printf("\n[-RESET BUFFER-]\n");	
								char c;
								while ((c = getchar()) != '\n' && c != EOF);
							}
						}					
					}
				}
			}
			else
			{
				for(int i=0; i<2; ++i)
				{
					rawCharacter = getchar();
					printf("[%i]: %i",i,rawCharacter);
					if(index<3 && (rawCharacter == '\n' || rawCharacter == '\r'))
					{
						if(ManualExecution)
						{
							printf("[-MANUAL RESET-]\n");					
						}
						else
						{
							printf("[-AUTO RESET-]\n");
						}
						index = 0;
						i=2;
						LettersBuffers[0] = 0xFFF;
						LettersBuffers[1] = 0xFFF;
						TransmitCan = 0;
					}
					else
					{
						unsigned char gotoNextStep = CheckIfSpecialChar(rawCharacter, LettersBuffers);
						if(gotoNextStep == 0xFF) {i=3;}
					}
				}

				//Check what is within the table
				for(int i=0; i<2; ++i)
				{
					rawCharacter = LettersBuffers[i];
					if(rawCharacter != 0xFFF)
					{
					
						if(rawCharacter == 0xFE)
						{
							printf("[-RESET-]\n");
							index = 0;
							dataFromCommandCenter[index] = ((unsigned char)rawCharacter);
						}
						else
						{
							if(rawCharacter == END_EVERYTHING)
							{
								loop = STOP;
								index = 12;
								i=3;
							}
							else
							{
								fflush(stdout);
								// Store chars in buffer
								dataFromCommandCenter[index] = ((unsigned char)rawCharacter);
								index++;
							}
						}
					}
				}
			}
		}

		if(loop == CONTINUE)
		{
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
				//printf("[%i]: %c",i,bytesToSend[i]);
			}

			if(TransmitCan == 1 && CAN_IsReading == 0)
			{
				printf("[-SYNC-]\n");
				//CAN_IsSending = 1;
				CAN_Transmit(address, bytesToSend, 8);
				//CAN_IsSending = 0;
			}
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
}
//################################################################//
/**
 * @brief handles CAN receptions. Each time a CAN communication is
 * intercepted, it gets printed as integers displayed as ASCII chars
 * in the terminal, with [RX] in front of the data.\n
 * Data is separated via commas to ease parsing on the CommandCenter.
 * @author Shawn Couture / LyamBRS
 * @date 24/11/2022
 */
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
		fflush(stdout);

		if (dataBuffer[0] == STOP)
		{
			printf("[-RX END-]\n");
			fflush(stdout);	
			loop = STOP;
			break;
		}

		if(CAN_IsSending == 0)
		{
			//CAN_IsReading = 1;
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
			//CAN_IsReading = 0;
		}
	}
  	CAN_CloseInterface();	
  	close(transmissionToReception[WRITING]);  
  	close(receptionToTransmission[READING]);
}

//----------------------- Public  Functions ----------------------//
//pas de fonctions publiques
/**
 * @brief Main function of this program. Used to create forks or
 * threads and initialise needed programs.
 * @return int 
 */
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
	sleep(1);
	fflush(stdout);
////////////////////////////////////////////////////////////////////////////////////////////////////
	// Ask user, or program if they are executing this manually or not.
	printf("\n\n[QUESTION]: Is this executed manually? (Y/N)\n");
	unsigned char answer = getchar();

	if(answer == 'Y')
	{
		ManualExecution = 0xFF;
		printf("\n[MANUAL MODE]");
		sleep(3);
		printf("\n");
	}
	else
	{
		ManualExecution = 0x00;
		printf("\n[AUTOMATIC MODE]");
		fflush(stdout);
		sleep(3);
		printf("\n");
		sleep(1);
	}
	fflush(stdout);
//////////////////////////////////////////////////////////////////////////////////////////////////// - WHILE LOOP	
	processID = fork();
	if(processID == (pid_t)0)
	{
    	HandleReception();
    	printf("[-QUITTING-]\n");    
	}
	else
	{
    	HandleTransmission();		
    	wait((int*) 1);
    	printf("[-QUITTING-]\n");     
	}

	printf("\n[-EXECUTION STOPPED-]\n");
    CAN_CloseInterface();
	return 0;
}
