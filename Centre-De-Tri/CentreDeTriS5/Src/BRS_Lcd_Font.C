/*************************************************************************************************
**************************************************************************************************
**************************************************************************************************

    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

***************************************************************************************************
** New:  BRS_Lcd_Font.c --- By Shawn Couture   ****************************************************
** Date: 04/04/2022               *****************************************************************
***************************************************************************************************/
//================================================================================================//
//	Include
//================================================================================================//
//#include "stm32f4xx_hal.h"                       //Définition pour le KIT ARM
//#include "IO_BUS.h"       
//#include "main.h"
//
//#include "GLcd.h"
//#include "math.h"
#include "BRS_Lcd_Font.h"


// 1234 
void Line4(unsigned char x, unsigned char y, unsigned char Hex, unsigned char state)
{
 BRS_LCD_Draw_Pixel(x+3,y, ((Hex & 0x01))    == state); 
 BRS_LCD_Draw_Pixel(x+2,y, ((Hex & 0x02)>>1) == state); 
 BRS_LCD_Draw_Pixel(x+1,y, ((Hex & 0x04)>>2) == state); 
 BRS_LCD_Draw_Pixel(x  ,y, ((Hex & 0x08)>>3) == state);   
}


//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_Lcd_Font4(unsigned char x, unsigned char y, unsigned char Char, unsigned char state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 04/04/2022
//__________________________________________________________________________________________________
//	Function:	| Rectangle coordinates necessary to draw certain 3 wide letters
//__________________________________________________________________________________________________
//	Entry:		| x,y, state of the character 1=On, 0=Inverted
//                      | 
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  switch(Char)
  {
    case(' ')://---------------------------------------------------------------------------------[ ]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x00, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x00, state);         
    break;

    case('!')://---------------------------------------------------------------------------------[!]
        Line4(x, y,   0x04, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x04, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x04, state); 
    break;    
    
    case('"')://---------------------------------------------------------------------------------["]
        Line4(x, y,   0x0A, state);
        Line4(x, y+1, 0x0A, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x00, state);         
    break;
    
    case('#')://---------------------------------------------------------------------------------[#]
        Line4(x, y,   0x05, state);
        Line4(x, y+1, 0x0F, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x0F, state);   
        Line4(x, y+4, 0x0A, state);        
    break;   

    case('$')://---------------------------------------------------------------------------------[$]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x0C, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x0C, state);   
        Line4(x, y+4, 0x04, state);        
    break;
    
    case('%')://---------------------------------------------------------------------------------[%]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x0D, state);
        Line4(x, y+2, 0x0A, state);    
        Line4(x, y+3, 0x05, state);   
        Line4(x, y+4, 0x0B, state);        
    break;
    
    case('&')://---------------------------------------------------------------------------------[&]
        Line4(x, y,   0x04, state);
        Line4(x, y+1, 0x0A, state);
        Line4(x, y+2, 0x04, state);    
        Line4(x, y+3, 0x0A, state);   
        Line4(x, y+4, 0x05, state);        
    break;
    
    case(39)://----------------------------------------------------------------------------------[']
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x06, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x00, state);        
    break;   
    
    case('(')://---------------------------------------------------------------------------------[(]
        Line4(x, y,   0x02, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x04, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x02, state);        
    break;      

    case(')')://---------------------------------------------------------------------------------[)]
        Line4(x, y,   0x04, state);
        Line4(x, y+1, 0x02, state);
        Line4(x, y+2, 0x02, state);    
        Line4(x, y+3, 0x02, state);   
        Line4(x, y+4, 0x04, state);        
    break;
    
    case('*')://---------------------------------------------------------------------------------[*]
        Line4(x, y,   0x0A, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x0A, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x00, state);        
    break;
    
    case('+')://---------------------------------------------------------------------------------[+]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x0E, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x00, state);        
    break;

    case(',')://---------------------------------------------------------------------------------[,]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x00, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x02, state);   
        Line4(x, y+4, 0x04, state);        
    break;
    
    case('-')://---------------------------------------------------------------------------------[-]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x00, state);
        Line4(x, y+2, 0x0E, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x00, state);        
    break;
    
    case('.')://---------------------------------------------------------------------------------[.]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x00, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x04, state);        
    break;

    case('/')://---------------------------------------------------------------------------------[/]
        Line4(x, y,   0x01, state);
        Line4(x, y+1, 0x02, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x08, state);        
    break;
    
    case('0')://---------------------------------------------------------------------------------[0]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x0B, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x0D, state);   
        Line4(x, y+4, 0x06, state);        
    break;
    
    case('1')://---------------------------------------------------------------------------------[1]
        Line4(x, y,   0x04, state);
        Line4(x, y+1, 0x0C, state);
        Line4(x, y+2, 0x04, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x0E, state);        
    break;
    
    case('2')://---------------------------------------------------------------------------------[2]
        Line4(x, y,   0x0E, state);
        Line4(x, y+1, 0x01, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x08, state);   
        Line4(x, y+4, 0x0F, state);        
    break;    
    
    case('3')://---------------------------------------------------------------------------------[3]
        Line4(x, y,   0x0E, state);
        Line4(x, y+1, 0x01, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x01, state);   
        Line4(x, y+4, 0x0E, state);        
    break;
    
    case('4')://---------------------------------------------------------------------------------[4]
        Line4(x, y,   0x09, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x07, state);    
        Line4(x, y+3, 0x01, state);   
        Line4(x, y+4, 0x01, state);        
    break;
    
    case('5')://---------------------------------------------------------------------------------[5]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x08, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x01, state);   
        Line4(x, y+4, 0x0E, state);        
    break;  
    
    case('6')://---------------------------------------------------------------------------------[6]
        Line4(x, y,   0x07, state);
        Line4(x, y+1, 0x08, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x0E, state);        
    break;
    
    case('7')://---------------------------------------------------------------------------------[7]
        Line4(x, y,   0x0E, state);
        Line4(x, y+1, 0x01, state);
        Line4(x, y+2, 0x01, state);    
        Line4(x, y+3, 0x01, state);   
        Line4(x, y+4, 0x01, state);        
    break;
    
    case('8')://---------------------------------------------------------------------------------[8]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x0F, state);        
    break;
    
    case('9')://---------------------------------------------------------------------------------[9]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x08, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x01, state);   
        Line4(x, y+4, 0x01, state);        
    break;
    
    case(':')://---------------------------------------------------------------------------------[:]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x00, state);        
    break;
    
    case(';')://---------------------------------------------------------------------------------[;]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x08, state);        
    break;
    
    case('<')://---------------------------------------------------------------------------------[<]
        Line4(x, y,   0x03, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x08, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x03, state);        
    break;
    
    case('=')://---------------------------------------------------------------------------------[=]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x0F, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x0F, state);   
        Line4(x, y+4, 0x00, state);        
    break;
    
    case('>')://---------------------------------------------------------------------------------[>]
        Line4(x, y,   0x0C, state);
        Line4(x, y+1, 0x02, state);
        Line4(x, y+2, 0x01, state);    
        Line4(x, y+3, 0x02, state);   
        Line4(x, y+4, 0x0C, state);        
    break;
    
    case('?')://---------------------------------------------------------------------------------[?]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x01, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x04, state);        
    break;
    
    case('@')://---------------------------------------------------------------------------------[@]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x0D, state);    
        Line4(x, y+3, 0x0F, state);   
        Line4(x, y+4, 0x06, state);        
    break;

    case('a'):    
    case('A')://---------------------------------------------------------------------------------[A]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x00, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x09, state);        
    break;

    case('b'):    
    case('B')://---------------------------------------------------------------------------------[B]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x01, state);
        Line4(x, y+2, 0x0A, state);    
        Line4(x, y+3, 0x01, state);   
        Line4(x, y+4, 0x0F, state);        
    break;

    case('c'):    
    case('C')://---------------------------------------------------------------------------------[C]
        Line4(x, y,   0x07, state);
        Line4(x, y+1, 0x08, state);
        Line4(x, y+2, 0x08, state);    
        Line4(x, y+3, 0x08, state);   
        Line4(x, y+4, 0x0F, state);        
    break;

    case('d'):    
    case('D')://---------------------------------------------------------------------------------[D]
        Line4(x, y,   0x0E, state);
        Line4(x, y+1, 0x01, state);
        Line4(x, y+2, 0x09, state);    
        Line4(x, y+3, 0x01, state);   
        Line4(x, y+4, 0x0E, state);        
    break;

    case('e'):    
    case('E')://---------------------------------------------------------------------------------[E]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x00, state);
        Line4(x, y+2, 0x0E, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x0F, state);        
    break;

    case('f'):    
    case('F')://---------------------------------------------------------------------------------[F]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x00, state);
        Line4(x, y+2, 0x0E, state);    
        Line4(x, y+3, 0x08, state);   
        Line4(x, y+4, 0x08, state);        
    break;

    case('g'):    
    case('G')://---------------------------------------------------------------------------------[G]
        Line4(x, y,   0x07, state);
        Line4(x, y+1, 0x08, state);
        Line4(x, y+2, 0x0B, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x0E, state);        
    break;

    case('h'):    
    case('H')://---------------------------------------------------------------------------------[H]
        Line4(x, y,   0x09, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x09, state);        
    break;

    case('i'):    
    case('I')://---------------------------------------------------------------------------------[I]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x06, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x06, state);   
        Line4(x, y+4, 0x0F, state);        
    break;

    case('j'):    
    case('J')://---------------------------------------------------------------------------------[J]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x02, state);
        Line4(x, y+2, 0x02, state);    
        Line4(x, y+3, 0x0A, state);   
        Line4(x, y+4, 0x06, state);        
    break;

    case('k'):    
    case('K')://---------------------------------------------------------------------------------[K]
        Line4(x, y,   0x09, state);
        Line4(x, y+1, 0x02, state);
        Line4(x, y+2, 0x0C, state);    
        Line4(x, y+3, 0x02, state);   
        Line4(x, y+4, 0x09, state);        
    break;

    case('l'):    
    case('L')://---------------------------------------------------------------------------------[L]
        Line4(x, y,   0x08, state);
        Line4(x, y+1, 0x08, state);
        Line4(x, y+2, 0x08, state);    
        Line4(x, y+3, 0x08, state);   
        Line4(x, y+4, 0x0F, state);        
    break;

    case('m'):    
    case('M')://---------------------------------------------------------------------------------[M]
        Line4(x, y,   0x09, state);
        Line4(x, y+1, 0x0F, state);
        Line4(x, y+2, 0x09, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x09, state);        
    break;

    case('n'):    
    case('N')://---------------------------------------------------------------------------------[N]
        Line4(x, y,   0x09, state);
        Line4(x, y+1, 0x0D, state);
        Line4(x, y+2, 0x0B, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x09, state);        
    break;

    case('o'):    
    case('O')://---------------------------------------------------------------------------------[O]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x09, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x06, state);        
    break;

    case('p'):    
    case('P')://---------------------------------------------------------------------------------[P]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x01, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x08, state);   
        Line4(x, y+4, 0x08, state);        
    break;

    case('q'):    
    case('Q')://---------------------------------------------------------------------------------[P]
        Line4(x, y,   0x0E, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x09, state);    
        Line4(x, y+3, 0x0B, state);   
        Line4(x, y+4, 0x07, state);        
    break;

    case('r'):    
    case('R')://---------------------------------------------------------------------------------[R]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x01, state);
        Line4(x, y+2, 0x0A, state);    
        Line4(x, y+3, 0x01, state);   
        Line4(x, y+4, 0x09, state);        
    break;

    case('s'):    
    case('S')://---------------------------------------------------------------------------------[S]
        Line4(x, y,   0x07, state);
        Line4(x, y+1, 0x08, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x01, state);   
        Line4(x, y+4, 0x0E, state);        
    break;

    case('t'):    
    case('T')://---------------------------------------------------------------------------------[T]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x06, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x06, state);   
        Line4(x, y+4, 0x06, state);        
    break;     

    case('u'):
    case('U')://---------------------------------------------------------------------------------[U]
        Line4(x, y,   0x09, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x09, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x0F, state);        
    break;

    case('v'):    
    case('V')://---------------------------------------------------------------------------------[V]
        Line4(x, y,   0x09, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x09, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x06, state);        
    break;

    case('w'):    
    case('W')://---------------------------------------------------------------------------------[W]
        Line4(x, y,   0x09, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x09, state);    
        Line4(x, y+3, 0x0F, state);   
        Line4(x, y+4, 0x09, state);        
    break; 

    case('x'):    
    case('X')://---------------------------------------------------------------------------------[X]
        Line4(x, y,   0x09, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x09, state);   
        Line4(x, y+4, 0x09, state);        
    break;

    case('y'):
    case('Y')://---------------------------------------------------------------------------------[Y]
        Line4(x, y,   0x09, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x06, state);   
        Line4(x, y+4, 0x06, state);        
    break;

    case('z'):
    case('Z')://---------------------------------------------------------------------------------[Z]
        Line4(x, y,   0x0F, state);
        Line4(x, y+1, 0x01, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x08, state);   
        Line4(x, y+4, 0x0F, state);        
    break;

    case('[')://---------------------------------------------------------------------------------[[]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x04, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x06, state);        
    break;

    case('\\')://---------------------------------------------------------------------------------[\]
        Line4(x, y,   0x08, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x06, state);    
        Line4(x, y+3, 0x02, state);   
        Line4(x, y+4, 0x01, state);        
    break;
    
    case(']')://---------------------------------------------------------------------------------[]]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x02, state);
        Line4(x, y+2, 0x02, state);    
        Line4(x, y+3, 0x02, state);   
        Line4(x, y+4, 0x06, state);        
    break;
    
    case('^')://---------------------------------------------------------------------------------[^]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x09, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x00, state);        
    break;
    
    case('_')://---------------------------------------------------------------------------------[_]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x00, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x0F, state);        
    break;
    
    case('`')://---------------------------------------------------------------------------------[`]
        Line4(x, y,   0x04, state);
        Line4(x, y+1, 0x02, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x00, state);        
    break;
    
    case('{')://---------------------------------------------------------------------------------[{]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x08, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x06, state);        
    break;
    
    case('|')://---------------------------------------------------------------------------------[|]
        Line4(x, y,   0x04, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x04, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x04, state);        
    break;
    
    case('}')://---------------------------------------------------------------------------------[|]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x02, state);
        Line4(x, y+2, 0x01, state);    
        Line4(x, y+3, 0x02, state);   
        Line4(x, y+4, 0x06, state);        
    break;

    case('~')://---------------------------------------------------------------------------------[~]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x02, state);
        Line4(x, y+2, 0x01, state);    
        Line4(x, y+3, 0x02, state);   
        Line4(x, y+4, 0x06, state);
    break;
    
    case('¬')://---------------------------------------------------------------------------------[¬]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x00, state);
        Line4(x, y+2, 0x0F, state);    
        Line4(x, y+3, 0x01, state);   
        Line4(x, y+4, 0x00, state);
    break;

    case('µ')://---------------------------------------------------------------------------------[µ]
        Line4(x, y,   0x00, state);
        Line4(x, y+1, 0x0A, state);
        Line4(x, y+2, 0x0A, state);    
        Line4(x, y+3, 0x0D, state);   
        Line4(x, y+4, 0x08, state);
    break;
    
    case('¦')://---------------------------------------------------------------------------------[¦]
        Line4(x, y,   0x04, state);
        Line4(x, y+1, 0x04, state);
        Line4(x, y+2, 0x00, state);    
        Line4(x, y+3, 0x04, state);   
        Line4(x, y+4, 0x04, state);
    break;
    
    case('°')://---------------------------------------------------------------------------------[°]
        Line4(x, y,   0x06, state);
        Line4(x, y+1, 0x0A, state);
        Line4(x, y+2, 0x0C, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x00, state);
    break;
    
    case('±')://---------------------------------------------------------------------------------[±]
        Line4(x, y,   0x04, state);
        Line4(x, y+1, 0x0E, state);
        Line4(x, y+2, 0x04, state);    
        Line4(x, y+3, 0x00, state);   
        Line4(x, y+4, 0x0E, state);
    break;    
  }
}