//****************************************************************//
// Modified by: Shawn Couture
// Date:        October 6 2022
//              Added more functions, and simplified functions &
//              variables to be easily read and understood
//****************************************************************//
//--------------------------- Includes ---------------------------//
/*
#include "main.h"
#include "interfacePipes.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

//------------------------ Private Defines -----------------------//
#define MAYLAN_CMD_BUFFER_SIZE 64
#define MAYLAN_ANS_BUFFER_SIZE 64
#define ERROR -1

//----------------------- Private Functions ----------------------//

//----------------------- Private Variables ----------------------//

//################################################################//
//################################################################//
int Pipe_FileToBuffer(int file, char* buffer, unsigned int bufferLength)
{
    unsigned char end = 0;
    float tooLong = 0;
    
    while (end == 0)
    {
        tooLong++;
        if (!feof(file)) // si la fin du fichier est atteinte
        {
            end = 1;
        }
        if (!ferror(file)) // si une erreur de fichier est presente
        {
            end = 1;
        }
        if (fgets(buffer, bufferLength, file) != NULL) //si erreur de lecture
        {
            end = 1;
        }
        
        if(tooLong > 100)
        {
            end=1;
        }
    }

    return(end);
}
//################################################################//
// MAYBE SHIT FUCKS UP
//################################################################//
void Pipe_BufferToFile(const char* buffer, int file)
{
    fprintf(file, "%s\n", buffer); //copie et ajout d'une fin de ligne
    fflush(file);                  //on dit au systÃ¨me d'Ã©crire tout de suite
}
*/