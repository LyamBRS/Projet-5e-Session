//#############################################################################
/**
 * @file ServiceCommunication_TEST.c
 * @author Lyam / Shawn Couture (cous5830@gmail.com)
 * @brief This file's only purpose is to test the compilation and executions
 * of the multiple functions present in ServiceCommunication.c and
 * ServiceCommunication.h This file contains a main function to serve as execution.
 * @version 0.1
 * @date 2022-11-18
 *
 * @copyright Copyright (c) 2022
 *
 */
//#############################################################################

#include <stdio.h>
#include "ServiceCommunication.h"

/**
* @brief TEST Function printing the inside of a buffer on the same line within brackets
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param Buffer Pointer pointing the address of the buffer to print
* @param sizeOfBuffer How big is the buffer referenced.
*/
void TEST_printBuffer(unsigned char* Buffer, unsigned char sizeOfBuffer)
{
    printf("{");
    for(int i=0; i<sizeOfBuffer; ++i)
    {
        if(Buffer[i] < 65)
        {
            printf("%X",Buffer[i]);            
        }
        else
        {
            if(Buffer[i] == AVAILABLE){printf("AV");}
            else
            {
                printf("%c",Buffer[i]);
            }
        }
        if(i<sizeOfBuffer-1)
        {
            printf(",");
        }
    }
    printf("}\n");    
}

/**
* @brief TEST Function printing what a data is equal to.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param data The value to print.
*/
void TEST_printData(unsigned char data)
{
    switch(data)
    {
        case(UNUSED):    printf("UNUSED"); break;
        case(AVAILABLE): printf("AVAILABLE"); break;
        case(PARSED):    printf("PARSED"); break;
        case(QUEUE):     printf("QUEUE"); break;
        case(IN_QUEUE):  printf("IN QUEUE"); break;
        case(NO_DATA):   printf("NO_DATA"); break;
        case(RECEIVED):  printf("RECEIVED"); break;
    }
}
/**
* @brief TEST Function printing the name associated to a command
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param Command The Command to print.
*/
void TEST_printCommandsName(unsigned char Command)
{
    switch(Command)
    {
        // Parsing of received commands in a CAN tram
        case(0x00): printf("Move Left"); break;
        case(0x01): printf("Move Right"); break;
        case(0x02): printf("Move Forwards"); break;
        case(0x03): printf("Move Backwards"); break;
        case(0x04): printf("Move Up"); break;
        case(0x05): printf("Move Down"); break;

        case(0x06): printf("Suction ON"); break;
        case(0x07): printf("Suction OFF");break;

        case(0x08): printf("Lights A ON"); break;
        case(0x09): printf("Lights A OFF"); break;

        case(0x0A): printf("Lights B ON"); break;
        case(0x0B): printf("Lights B OFF"); break;

        case(0x0C): printf("Lights C ON"); break;
        case(0x0D): printf("Lights C OFF"); break;

        case(0x0E): printf("Lights D ON"); break;
        case(0x0F): printf("Lights D OFF"); break;

        case(0x10): printf("Goto sorting station"); break;
        case(0x11): printf("Goto weight station"); break;

        case(0x12): printf("Start Sorting"); break;
        case(0x13): printf("Start Weighting"); break;

        case(0x14): printf("Discharge"); break;

        case(0x16): printf("Use Metric"); break;
        case(0x17): printf("Use Imperial"); break;                
    }    
}
/**
* @brief TEST Function printing the name associated to a command
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param Value The value to print.
*/
void TEST_printValuesName(unsigned char Value)
{
    switch(Value)
    {
        // Parsing of received commands in a CAN tram
        case(0x00): printf("Disc is red"); break;
        case(0x01): printf("Disc is silver"); break;
        case(0x02): printf("Disc is black"); break;
        case(0x03): printf("No Color"); break;
        case(0x04): printf("Disc detected"); break;
        case(0x05): printf("Disc Lost"); break;

        case(0x06): printf("Disc couldnt be found"); break;
        case(0x07): printf("Using Metric units");break;

        case(0x08): printf("using imperial units"); break;              
    }    
}
/**
* @brief Function printing the entire of a Command structure which isnt a reference.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param void
*/
void TEST_printAllSentCommands(void)
{
    printf("------------------------------------ COMMANDS:\n");
    TEST_printCommandsName(Commands.move_left); printf(": \t\t");     TEST_printData(ModuleData.CommandsToSend.move_left); printf("\n");
    TEST_printCommandsName(Commands.move_right); printf(": \t\t");    TEST_printData(ModuleData.CommandsToSend.move_left); printf("\n");
    TEST_printCommandsName(Commands.move_forward); printf(": \t\t");  TEST_printData(ModuleData.CommandsToSend.move_forward); printf("\n");
    TEST_printCommandsName(Commands.move_backward); printf(": \t"); TEST_printData(ModuleData.CommandsToSend.move_backward); printf("\n");
    TEST_printCommandsName(Commands.move_up); printf(": \t\t");       TEST_printData(ModuleData.CommandsToSend.move_up); printf("\n");
    TEST_printCommandsName(Commands.move_down); printf(": \t\t");     TEST_printData(ModuleData.CommandsToSend.move_down); printf("\n");
    TEST_printCommandsName(Commands.suction_ON); printf(": \t\t");    TEST_printData(ModuleData.CommandsToSend.suction_ON); printf("\n");
    TEST_printCommandsName(Commands.suction_OFF); printf(": \t\t");   TEST_printData(ModuleData.CommandsToSend.suction_OFF); printf("\n");
    TEST_printCommandsName(Commands.light_A_ON); printf(": \t\t");    TEST_printData(ModuleData.CommandsToSend.light_A_ON); printf("\n");
    TEST_printCommandsName(Commands.light_A_OFF); printf(": \t\t");   TEST_printData(ModuleData.CommandsToSend.light_A_OFF); printf("\n");
    TEST_printCommandsName(Commands.light_B_ON); printf(": \t\t");    TEST_printData(ModuleData.CommandsToSend.light_B_ON); printf("\n");
    TEST_printCommandsName(Commands.light_B_OFF); printf(": \t\t");   TEST_printData(ModuleData.CommandsToSend.light_B_OFF); printf("\n");
    TEST_printCommandsName(Commands.light_C_ON); printf(": \t\t");    TEST_printData(ModuleData.CommandsToSend.light_C_ON); printf("\n");
    TEST_printCommandsName(Commands.light_C_OFF); printf(": \t\t");   TEST_printData(ModuleData.CommandsToSend.light_C_OFF); printf("\n");
    TEST_printCommandsName(Commands.light_D_ON); printf(": \t\t");    TEST_printData(ModuleData.CommandsToSend.light_D_ON); printf("\n");
    TEST_printCommandsName(Commands.light_D_OFF); printf(": \t\t");   TEST_printData(ModuleData.CommandsToSend.light_D_OFF); printf("\n");
    TEST_printCommandsName(Commands.goto_SortingStation); printf(": \t");   TEST_printData(ModuleData.CommandsToSend.goto_SortingStation); printf("\n");
    TEST_printCommandsName(Commands.goto_WeightStation); printf(": \t");   TEST_printData(ModuleData.CommandsToSend.goto_WeightStation); printf("\n");
    TEST_printCommandsName(Commands.start_Sorting); printf(": \t\t");   TEST_printData(ModuleData.CommandsToSend.start_Sorting); printf("\n");
    TEST_printCommandsName(Commands.start_Weighting); printf(": \t");   TEST_printData(ModuleData.CommandsToSend.start_Weighting); printf("\n");
    TEST_printCommandsName(Commands.discharge); printf(": \t\t");   TEST_printData(ModuleData.CommandsToSend.discharge); printf("\n");
    TEST_printCommandsName(Commands.units_Metric); printf(": \t\t");   TEST_printData(ModuleData.CommandsToSend.units_Metric); printf("\n");
    TEST_printCommandsName(Commands.units_Imperial); printf(": \t\t");   TEST_printData(ModuleData.CommandsToSend.units_Imperial); printf("\n");
}
/**
* @brief Function printing the entirety of a Value structure which isnt a reference.
* @author Lyam / Shawn Couture
* @date 18/11/2022
* @param void
*/
void TEST_printAllSentValues(void)
{
    printf("------------------------------------ VALUES:\n");
    TEST_printValuesName(Values.disc_Red); printf(": \t\t");     TEST_printData(ModuleData.ValuesToSend.disc_Red); printf("\n");
    TEST_printValuesName(Values.disc_Black); printf(": \t\t");    TEST_printData(ModuleData.ValuesToSend.disc_Black); printf("\n");
    TEST_printValuesName(Values.disc_Silver); printf(": \t");  TEST_printData(ModuleData.ValuesToSend.disc_Silver); printf("\n");
    TEST_printValuesName(Values.disc_NoColor); printf(": \t\t"); TEST_printData(ModuleData.ValuesToSend.disc_NoColor); printf("\n");
    TEST_printValuesName(Values.disc_Detected); printf(": \t\t");       TEST_printData(ModuleData.ValuesToSend.disc_Detected); printf("\n");
    TEST_printValuesName(Values.disc_Lost); printf(": \t\t");     TEST_printData(ModuleData.ValuesToSend.disc_Lost); printf("\n");
    TEST_printValuesName(Values.disc_CouldNotBeFound); printf(": \t");    TEST_printData(ModuleData.ValuesToSend.disc_CouldNotBeFound); printf("\n");
    TEST_printValuesName(Values.unit_Metric); printf(": \t");   TEST_printData(ModuleData.ValuesToSend.unit_Metric); printf("\n");
    TEST_printValuesName(Values.unit_Imperial); printf(": \t");    TEST_printData(ModuleData.ValuesToSend.unit_Imperial); printf("\n");
}
int main()
{
    ServiceCommunication_initialise();

    unsigned char interruptCount = 0;
    for(int i=0; i<100; ++i)
    {
        //Count active interrupts
        interruptCount++;
    
        printf("################################ Buffer Cycle No%i\n",interruptCount);

        //How long is an interrupt --> how long is a full buffer cycle.
        float interruptDuration = ((1/TIME_BASE_FREQUENCY_HZ) * 1000) * TIME_BASE_BUFFER_SIZE;
        printf("Interrupt duration is: %f\n",interruptDuration);

        //How long we've been running.
        float timeSinceReset = interruptDuration * ((float)(interruptCount));
        printf("Time since reset is: %f\n",timeSinceReset);

        //Current slot.
        unsigned currentSlot = ((unsigned char)(timeSinceReset)) / CAN_SLOT_DURATION_MS;
        printf("Current CAN slot is: %i\n",currentSlot);
        if(currentSlot > 6)
        {
            // fuck
        }
    }
    return 0;
}

