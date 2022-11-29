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
** New:      BRS_Lcd.c --- By Shawn Couture   *****************************************************
** Original: GLcd.c    --- By Alain Champagne *****************************************************
** Date: 24/03/2022               *****************************************************************
***************************************************************************************************/
//================================================================================================//
//	Include
//================================================================================================//
#include "BRS_Lcd.h"


//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Pixel(double x, double y, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 24/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a pixel on or off using a single function instead of 2.
//			| coordinates range from x(0-127) and y(0-127). Then input on/off (1/0)
//__________________________________________________________________________________________________
//	Entry:		| coordinates (x,y) wanted state (state)
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  //checks
  if((x>=0) && (y>=0) && (y<64) && (x<128))
  {
    if(state > 0)
      {
        vPutPixelGLcd((unsigned char)x, (unsigned char)y);
      }
    else
      {
        vClearPixelGLcd((unsigned char)x, (unsigned char)y);
      }
  }
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Line(double x1, double y1, double x2, double y2, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 24/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a line inbetween 2 coordinates.
//			| coordinates range from x(0-127) and y(0-127). Then input on/off (1/0) 
//__________________________________________________________________________________________________
//	Entry:		| start coordinates (x,y) end coordinates (x,y) wanted state (state)
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
 //##########################################//####################################_Local Variables_ 
   double lenght      = 0;                   // distance inbetween the 2 coordinates
   double ratioX      = 0.0;                 // difference between x1 and x2 divided by lenght.
   double ratioY      = 0.0;                 // difference between y1 and y2 divided by lenght.
 //##########################################//####################################_Local Variables_    
  
//////////////////////////////////////////////////////////////////////////////////////////////[MATH]
// Distance in between the 2 pixels.   
   lenght = (sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))));

// Difference in between the 2 X coordinates.   
   ratioX = (x2-x1)/lenght;// -0.71
   ratioY = (y2-y1)/lenght;// -0.71
 
//////////////////////////////////////////////////////////////////////////////////////////////[LOOP]
// loop form 0 to the distance inbetween the 2 points
   for(unsigned char i = 0; i<=ceil(lenght); i++)
      {
        BRS_LCD_Draw_Pixel((x1 + (i*ratioX)), (y1 + (i*ratioY)),   state);
      }
}



//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Shape_Rect(unsigned char x, unsigned char y, unsigned char width, unsigned char height, bool state)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture
//	Date made:	| 07/04/2022
//__________________________________________________________________________________________________
//	Function:	| Draws or clears a rectangle borders
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) width, height, state(0-1)
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
 width  = width  - 1;
 height = height - 1; 
  
 //Top line
 BRS_LCD_Draw_Line(x, y, x+width, y, state); 
  
 //Bottom line
 BRS_LCD_Draw_Line(x, y+height, x+width, y+height, state);  
  
 //Right line
 BRS_LCD_Draw_Line(x+width, y, x+width, y+height, state); 
 
 //Left line
 BRS_LCD_Draw_Line(x, y, x, y+height, state);   
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Shape_RectF(unsigned char x, unsigned char y, unsigned char width, unsigned char height, bool state)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture
//	Date made:	| 28/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a rectangle or clears a rectangle
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) width, height, state(0-1)
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  
  //Test if width and height are beyond the LCD grid
  if((width+x)-1 > 128) {width = 127-x;}
  if((height+y)-1 > 63) {height = 63-y;}

  if(width >= 0)
  {
  //draw the full rectangle
  for(int i=x; i<(x+width); i++)
     {
      for(int e=y; e<(y+height); e++)  
         {
          BRS_LCD_Draw_Pixel(i,e,state);
         }
     }
  }
  else
  {
      //draw the full rectangle
  for(int i=x+width; i<x; i++)
     {
      for(int e=y; e<(y+height); e++)  
         {
          BRS_LCD_Draw_Pixel(i,e,state);
         }
     }
  }
}





//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_CirclePixel(unsigned char x, unsigned char y, double radius, double radian, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 31/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a pixel at a wanted radian value
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) radius, angle(radian), state
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{  
   BRS_LCD_Draw_Pixel(ceil((sin(radian)*radius)+x),ceil((cos(radian)*radius)+y),state);
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_OvalPixel(unsigned char x, unsigned char y, double radiusX, double radiusY, double radian, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 04/04/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a pixel at a wanted radian value deformed by a X radius and a Y radius
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) radiusX,radiusY, angle(radian), state
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{  
  // draws the pixel deformed by 2 different radius value.
     BRS_LCD_Draw_Pixel(ceil((sin(radian)*(radiusX))+x),ceil((cos(radian)*(radiusY))+y),state);
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_CircleLine(unsigned char x, unsigned char y, double InsideRadius, double OutsideRadius, double radian, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 31/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a line from the given coordinate, to the edge of a "circle" given
//                      | by the input radius.
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) radius, angle, state
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{  
  // draws the line of pixel starting from the center radius, to the outer radius
     BRS_LCD_Draw_Line(ceil((sin(radian)*InsideRadius)+x),ceil((cos(radian)*InsideRadius)+y),ceil((sin(radian)*OutsideRadius)+x),ceil((cos(radian)*OutsideRadius)+y),state);
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Shape_Circle(unsigned char x, unsigned char y, double radius, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 31/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a circle border from a starting radian, to an ending radian
//                      | To draw a complete circle, simply put (x,y,radius,0,6.28,1)
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) radius, state
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  
  //Find the increment necessary in order to avoid  holes or overlapping pixels for no reasons
  double increment = (12.56/(2*3.1*(radius*radius)));
  
  //For loop from starting radian to ending radian incrementing in 0.01
  for(double i = 0; i <= 6.28; i += increment)
     {
        BRS_LCD_Draw_Pixel(floor(sin(i)*radius)+x, floor(cos(i)*radius)+y, state);
     }
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Shape_CircleF(unsigned char x, unsigned char y, double radius, bool state)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture
//	Date made:	| 19/04/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a full circle without using sin or cos
//                      | 
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) radius, state
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  unsigned char leftTopX = ((unsigned char) x) - (unsigned char) radius;
  unsigned char leftTopY = ((unsigned char) y) - (unsigned char) radius;
  
  unsigned char widthCoord = (leftTopX+((unsigned char)radius*2));
  unsigned char heigthCoord = (leftTopY+((unsigned char)radius*2));
  
  //Save memory by reusing input parameters
  unsigned int RadiusSquared = (radius*radius);        //Avoids doing exponents of radius
    
  //Fill in a circle inside a rectangle area of diameter width starting at the coords defined above
  for(unsigned char checkX = leftTopX; checkX <= widthCoord; checkX++)
     {
      for(unsigned char checkY = leftTopY; checkY <= heigthCoord; checkY++)
         {
           if(RadiusSquared < (((checkX - x)*(checkX - x)) + ((checkY - y)*(checkY - y))))
             {
               //BRS_LCD_Draw_Pixel(checkX, checkY, !state);
             }
           else
             {
               BRS_LCD_Draw_Pixel(checkX, checkY, state);             
             }
         }
     }
}




//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Misc_ScalableBRS(unsigned char x, unsigned char y, unsigned char scale, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 28/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws scalable BRS logo of a desired size
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) scale, state(0-1)
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
    BRS_LCD_Draw_Shape_RectF(x,         y,             6*scale,scale,state);
    BRS_LCD_Draw_Shape_RectF(x+5*scale, y+scale,       scale,  scale,state);    
    BRS_LCD_Draw_Shape_RectF(x+4 *scale,y+2*scale,     scale,  scale,state);
    BRS_LCD_Draw_Shape_RectF(x+5 *scale,y+3*scale,     scale,  scale,state);
    BRS_LCD_Draw_Shape_RectF(x,         y+2*scale,     2*scale, scale,state);
    BRS_LCD_Draw_Shape_RectF(x,         y+4*scale,     6*scale, scale,state); 
    BRS_LCD_Draw_Shape_RectF(x+7 *scale,y,             6*scale, scale,state);
    BRS_LCD_Draw_Shape_RectF(x+12*scale,y+scale,       scale,  scale,state);    
    BRS_LCD_Draw_Shape_RectF(x+11*scale,y+2*scale,     scale,  scale,state);
    BRS_LCD_Draw_Shape_RectF(x+12*scale,y+3*scale,     scale,  2*scale,state);
    BRS_LCD_Draw_Shape_RectF(x+7 *scale,y+2*scale,     2*scale, scale,state);  
    BRS_LCD_Draw_Shape_RectF(x+7 *scale,y+4*scale,     2*scale, scale,state);
    BRS_LCD_Draw_Shape_RectF(x+15*scale,y,             5*scale, scale,state);
    BRS_LCD_Draw_Shape_RectF(x+14*scale,y+scale,       scale,  scale,state);     
    BRS_LCD_Draw_Shape_RectF(x+14*scale,y+2*scale,     6*scale, scale,state);
    BRS_LCD_Draw_Shape_RectF(x+19*scale,y+3*scale,     scale,  scale,state);
    BRS_LCD_Draw_Shape_RectF(x+14*scale,y+4*scale,     5*scale, scale,state);    
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
  void BRS_LCD_Draw_Misc_LabHeader(char const *lab, char const *Table)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 23/03/2022 --- 29/03/2022
//__________________________________________________________________________________________________
//	Function:	| Function displaying the header on the LCD
//			| 
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
  {
    char const CurrentLine2[] = "                    ";    
    char const CurrentLine3[] = "   Cegep Limoilou   ";    
    char const CurrentLine4[] = "        2022        ";
    char const CurrentLine5[] = "                    ";
    
    vPutStringGLcd((char const*)lab, 1, 5);
    vPutStringGLcd((char const*)CurrentLine2, 2, 5);
    vPutStringGLcd((char const*)CurrentLine3, 3, 5);    
    vPutStringGLcd((char const*)CurrentLine4, 4, 5);
    vPutStringGLcd((char const*)CurrentLine5, 5, 5);
    vPutStringGLcd((char const*)Table, 6, 5);        
  }

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Clear_Swipe(unsigned char direction)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 28/03/2022
//__________________________________________________________________________________________________
//	Function:	| Clears the LCD in a simple swipe
//__________________________________________________________________________________________________
//	Entry:		| 0: Left->Right 1: Top->Down 2: Right->Left 3:Down->Top
//                      | speed: in ms
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
 //##########################################//####################################_Local Variables_ 
   unsigned char MaxCount   = 0;             // distance inbetween the 2 coordinates
 //##########################################//####################################_Local Variables_<
   
   //Choose the direction and the needed lenght to travel
   switch(direction)
         {
           case(0):           
           case(2):
                    MaxCount = 127;
                    break;
           case(1):                    
           case(3):
                    MaxCount = 64;
                    break;           
         }
   
   //Draw lines
   for( unsigned char i=0; i<MaxCount; i+=2)
      {
//        HAL_Delay(speed);
        switch(direction)
              {
                case(0):
                          BRS_LCD_Draw_Line(i,0,i,64,1);
                          BRS_LCD_Draw_Line(i+1,0,i+1,64,1);                          
                          break;
           
                case(1):
                          BRS_LCD_Draw_Line(0,i,128,i,1);                     
                          BRS_LCD_Draw_Line(0,i+1,128,i+1,1);                  
                          break;
           
                case(2):
                          BRS_LCD_Draw_Line(127-i,0,127-i,64,1);
                          BRS_LCD_Draw_Line(127-(i+1),0,127-(i+1),64,1);                            
                          break;
                case(3):
                          BRS_LCD_Draw_Line(0,63-i,128,63-i,1);
                          BRS_LCD_Draw_Line(0,63-(i+1),128,63-(i+1),1);                             
                          break;           
                }
      }
   //Clear lines
   for(unsigned char i=0; i<MaxCount; i+=2)
      {
//        HAL_Delay(speed);
        switch(direction)
              {
                case(0):
                          BRS_LCD_Draw_Line(i,0,i,64,0);
                          BRS_LCD_Draw_Line(i+1,0,i+1,64,0);                          
                          break;
           
                case(1):
                          BRS_LCD_Draw_Line(0,i,128,i,0);                     
                          BRS_LCD_Draw_Line(0,i+1,128,i+1,0);                  
                          break;
           
                case(2):
                          BRS_LCD_Draw_Line(127-i,0,127-i,64,0);
                          BRS_LCD_Draw_Line(127-(i+1),0,127-(i+1),64,0);                            
                          break;
                case(3):
                          BRS_LCD_Draw_Line(0,63-i,128,63-i,0);
                          BRS_LCD_Draw_Line(0,63-(i+1),128,63-(i+1),0);                             
                          break;           
                }
      }
}
















//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Text_Char(unsigned char x, unsigned char y, unsigned char letter, unsigned char font, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 29/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a single character to a set coordinate on the screen.
//                      | This function currently only works with BRS font
//__________________________________________________________________________________________________
//	Entry:		| x,y, ascii value of letter, 0,1,2
//                      | 
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  if(letter == 0) letter = ' ';
  BRS_Lcd_Font4(x,y,letter,state);
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Text_String(unsigned char x, unsigned char y, char const string[], unsigned char font, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 29/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a table of characters in a single line with no returns
//                      | This function currently only works with BRS fonts of 4*
//__________________________________________________________________________________________________
//	Entry:		| x,y, , 0,1,2
//                      | 
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
   char const length = strlen(string);
  
  //Draw the line of character
  for(unsigned char i=0; i<length; i++)
    {
      BRS_LCD_Draw_Text_Char(x + (i*5),y, string[i],4,state);
    }
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Text_Integer(unsigned char x, unsigned char y, int Number, unsigned char maxDigits, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 5/04/2022
//__________________________________________________________________________________________________
//	Function:	| Draws an integer value, which can be negative at the specified coordinates 
//                      | The font is 4 pixel wide, and is drawn from the top left pixel 
//                      | You need to specify the maximum digits you want to display, minus included
//__________________________________________________________________________________________________
//	Entry:		| x,y, displayed number, amount of digits including the minus, wanted state
//                      | 
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  unsigned int displaying = 0;
  unsigned int divider = 1;
  unsigned int restDivider = 1;

  bool was0 = 0;  
/////////////////////////////////////////////////////////////////////////////////////[NEW DIGIT MAX]  

  
  //Positive number
  if(Number >= 0)
  {
    for(unsigned int currentDigit = 1; currentDigit <= maxDigits; currentDigit++)
       {
         restDivider = 1;
         divider = 1;
         displaying = Number;
         
          for(unsigned char i = 0; i<currentDigit; i++)   divider     = divider*10;
          for(unsigned char i = 0; i<currentDigit-1; i++) restDivider = restDivider*10;    
         
          displaying = (displaying%divider)/restDivider;
         
          //reduce to 1 digit number
          while(displaying >= 10) displaying = displaying/10;
          
          if(Number < 100 && currentDigit == 3) {displaying = 0xFF;}
          if(Number < 10  && currentDigit == 2) {displaying = 0xFF;}           
          
          if(displaying == 0xFF)
          {
            BRS_LCD_Draw_Text_Char(((maxDigits-1)*5)-((currentDigit-1)*5) + x,y, ' ', 4, state); 
          }
          else
          {
            BRS_LCD_Draw_Text_Char(((maxDigits-1)*5)-((currentDigit-1)*5) + x,y, (unsigned char)displaying+0x30, 4, state);            
          }
        }
   }
  
  else //Negative number
  {
    //knowing we need to show the - in front of the number, they should be slided to the left 1 char
    BRS_LCD_Draw_Text_Char(x,y,'-',4,state);
  }
  
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Draw_Text_Hexa(unsigned char x, unsigned char y, int Number, unsigned char maxDigits, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 6/04/2022
//__________________________________________________________________________________________________
//	Function:	| Draws an integer value as an hexadecimal number on the LCD screen.
//                      | example: 0 = 0xZZ
//                      | Max digit will define how many Z will be drawn after the 0x
//__________________________________________________________________________________________________
//	Entry:		| x,y, displayed hexa, amount of digits including the minus, wanted state
//                      | 
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  unsigned char Table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};  
  unsigned int  Value = 0;
  unsigned char BitShift = 0;
  unsigned char posX = x+10;
  //Positive number
  if(Number >= 0)
  {
    //DRAW 0x
    BRS_LCD_Draw_Text_Char(x,y,'0',4,state);    
    BRS_LCD_Draw_Text_Char(x+5,y,'x',4,state);     
    
    for(unsigned currentDigit = maxDigits; currentDigit > 0; currentDigit--)
       {
          BitShift = (currentDigit-1)*4;
          
          Value = (Number >> BitShift) & 0x0F;
          
          BRS_LCD_Draw_Text_Char(posX,y,Table[Value],4,1);
          
          posX = posX + 5;
       }
  }  
}  
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§ 
void BRS_LCD_Draw_Text_Double  (unsigned char x, unsigned char y, double Number,unsigned char decimals, unsigned char maxDigits, bool state)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 6/04/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a double number on the screen at the specified coordinates
//                      | MaxDigit is ONLY for the numbers before the decimal point
//                      | decimals is ONLY for the numbers AFTER the decimal point
//__________________________________________________________________________________________________
//	Entry:		| x,y, displayed float, amount of digits including the minus, wanted state
//                      | 
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  double lastChar   =(int) Number;
  
  double displaying = 0;
  int    Casted=0;
    
  unsigned char posX = x;
  
  
  if(Number>=0)
  {
    BRS_LCD_Draw_Text_Char(x+((maxDigits)*5)+((decimals)*5)+5,y,' ',4,state);
  }  
  
  // CHECK IF NUMBER IS NEGATIVE
  if(Number<0)
  {
    BRS_LCD_Draw_Text_Char(x,y,'-',4,state);
    posX = x + 5;
    Number = -Number;
    
    lastChar   =(int) Number;
  }

  
  //////////////////////////////////////////////////////////////////////////////////////////////////[INT]
      for(unsigned currentDigit = maxDigits; currentDigit > 0; currentDigit--)
       {
         displaying = (lastChar/10);            //divide the number to get 1 decimal
         
         //Cast it to remove decimal
         Casted     = (int)    displaying;     //25,6 ->25    
         
         displaying = (double) Casted;          // cast it back to a double        

         //Get remove the upper values           
         displaying = ((lastChar/10) - displaying) * 10; //(25,6 - 25)*10) = 6
       
         //Set last char to the remaining numbers
         lastChar    = (lastChar/10)    - (displaying/10); //remaining = 25
     
         BRS_LCD_Draw_Text_Char((currentDigit-1)*5 + posX,y,(unsigned char)displaying+0x30,4,state);

       }
  //////////////////////////////////////////////////////////////////////////////////////////////////[DECIMAL]
  //DRAW DECIMAL POINT
  BRS_LCD_Draw_Text_Char(posX + (maxDigits)*5 ,y,'.',4,state);
  
  //Transform the decimals of Number, into an integer
  Casted     = (int) Number;
  displaying = (double) Casted;
  
  Number = Number - displaying; //Keeps decimals only
  posX   = posX   + maxDigits*5 +5;//Shifts pos X position
  
      lastChar = Number;
      for(unsigned currentDigit = decimals; currentDigit > 0; currentDigit--)
       {
         displaying = (lastChar*10);           //Multiply the number by 10 (0.125 = 1.25)
         
         //Cast it to remove decimal
         Casted     = (int)    displaying;     //1.25 -> 1    
         displaying = (double) Casted;         // cast it back to a double        
       
         //Set last char to the remaining numbers
         lastChar    = (lastChar*10) - displaying; //remaining = 0.25
     
         BRS_LCD_Draw_Text_Char((decimals-currentDigit)*5 + posX,y,(unsigned char)displaying+0x30,4,state);

       }
}





//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Demo_Line(void)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 31/03/2022
//__________________________________________________________________________________________________
//	Function:	| Demonstrate effects that can be acheived using BRS_LCD_Draw_Line.
//                      | The normal function draws a line of pixels from one coordinate to an other
//                      | (x1,y1,x2,y2)
//                      | The Order in which you put your coordinates affects minimaly the obtained
//                      | results.
//                      |
//                      | Although beware, sometimes the function will round pixels weirdly and
//                      | some results will not be what you expect them to be.
//                      |
//                      | Trial and error is thus required in order to acheive a wanted result
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  Demo_TitleSwipe("   2 Points Lines   ");
  
  BRS_LCD_Draw_Line(0,0,63,63,1); // diagonal from top left to bottom middle
  BRS_LCD_Draw_Line(63,0,0,63,1); // diagonal from middle top to bottom left

  BRS_LCD_Draw_Line(63,0,127,63,1);  // diagonal from middle top to bottom right
  BRS_LCD_Draw_Line(63,63,127,0,1);  // diagonal from bottom middle to top right

  BRS_LCD_Draw_Line(0,0,126,62,1);  // diagonal from top left to bottom right
  BRS_LCD_Draw_Line(126,0,0,62,1);  // diagonal from top right to bottom left
  
  while(1)
  {
    
  }
}



//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Demo_Circles(void)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 07/04/2022
//__________________________________________________________________________________________________
//	Function:	| This function is a 1up of the previous demo of circle pixels.
//                      | 
//                      | This function simple allows you to draw a line from a smaller radius
//                      | circle's perimeter, to a larger radius circle's perimeter.
//                      | 
//                      | This function is useful when creating radial graph to display changing
//                      | values. For example: Speed, RPM which would ideally be represented by
//                      | such graph
//                      | 
//                      | This function demonstrates effects that can be acheived using CircleLine
//                      | as well as where a line would be pointing if given a specific radian
//                      | 
//                      | If the smaller circle has a radius of 0, it draws the line from center
//                      | coordinates to the larger one, useful for data graph.
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  //##########################################//####################################_Local Variables_    
  double count      = 0;
  double countB     = 0;
  double oldCount   = 0;
  
  double localCount = 4.5;
  
  unsigned char NextFunction     = 0;
  unsigned int  AnimationTime    = 6000;
  double        AnimationCounter = AnimationTime;
  
  double        loadingRatio     = floor(AnimationCounter/127);
  unsigned char loadingBarCoord  = 0;
  unsigned char oldCoord         = 0;
  
  ////////////////////////////////////////////////[ANIMATION DIRECTIONS]  
  double direction1 = 0.01;
  double direction2 = 1; 
  ////////////////////////////////////////////////[RADIUS OF DISPLAYED CIRCLE]
  double newRadius1 = 10;
  double newRadius2 = 10;
  double oldRadius1 = 9;
  double oldRadius2 = 9;  
  ////////////////////////////////////////////////[DRAWN STATE]  
  bool state=0;
  //##########################################//####################################_Local Variables_ 
  Demo_TitleSwipe("  Circle Functions  ");
  
  while(1)
  {
//##################################################################################################// CIRCLE PIXEL    
    if(NextFunction == 0)
    {
      HAL_Delay(1);
      
      BRS_LCD_Draw_CirclePixel(63,31,oldRadius1,localCount,0); // Erase the pixel at the last radian      
      BRS_LCD_Draw_CirclePixel(63,31,newRadius1,count,1);      //Draw the pixel at the current radian

      //____________________________________________________________________________[RADIUS COUNTER]
      if(count      >= 6.25){ newRadius1++; }      
      if(localCount >= 6.25){ oldRadius1++; BRS_LCD_Draw_Text_Integer(60,30,(unsigned char)newRadius1,2,1);}
      
      if(newRadius1 > 20){newRadius1 = 10;}
      if(oldRadius1 > 20){oldRadius1 = 10;}  
      
      //_____________________________________________________________________________[LOCAL COUNTER]      
      localCount = localCount + 0.02;
      if(localCount > 6.27){localCount = 0;}
      
      //____________________________________________________________________________[RADIAN DISPLAY]        
      BRS_LCD_Draw_Text_Double(40,55,count,2,1,1);
      
      //////////////////////////////////////////////////////////////////////////////////////////////[DRAWN ONCE]         
      if(state == 0)
      {
        state = 1;
        BRS_LCD_Draw_Text_String(0,55,"Radians:",4,1);
        vPutStringGLcd("Circumference pixels", 0,5);    
      }
      //____________________________________________________________________________[Radian Counter]
      count  += 0.02;  //Fast counter
      if(count > 6.27) {count  = 0;}

      countB += 0.002; //Slow counter
      if(countB > 6.27){countB = 0;}  
      
      //////////////////////////////////////////////////////////////////////////////////////////////[NEXT ANIMATION]
      if(AnimationCounter == 0)
      {       
        BRS_LCD_Clear_Swipe(1);
        BRS_LCD_Draw_Misc_ScalableBRS(50,5,1,1);         
        vPutStringGLcd(" Next:  Circle Line ", 2,5);
        vPutStringGLcd("   In/out  radius   ", 3,5);    
        HAL_Delay(2000);        
        BRS_LCD_Clear_Swipe(1);
        
        localCount = 0;
        count      = 8;
        direction1 = 14;
        countB     = 17;
        direction2 = 24;
        state      = 0;
        oldCount   = 0;
        
        NextFunction++;
        AnimationCounter = AnimationTime;        
      }
    }
//##################################################################################################// CIRCLE LINE RADIUS
    if(NextFunction == 1)
    {
////////////////////////////////////////////////////////////////////////////////////////////////////[FIRST HALF]      
      if(AnimationCounter > AnimationTime/2)
      {
        HAL_Delay(5);
       //______________________________________________________________________[Draw radius Numbers]        
        BRS_LCD_Draw_Text_Integer(31,48,(unsigned char)newRadius1,2,1);
        BRS_LCD_Draw_Text_Integer(31,55,(unsigned char)newRadius2,2,1);        
       //______________________________________________________________________[Wipe Out Old Circle]
       //Wipe out the circle because one of the radius counters reseted. otherwise, there will be
       //residues of the past radius
        if(localCount == 0)
          {
            if(oldCount == 1)
              {
                oldCount = 0;
                //Rectangle erasing the quarter circle
                BRS_LCD_Draw_Shape_RectF(62,30,27,27,0);
              }
            
            //Draw a line from a circle with from the first counter radius to the next counter radius
            for(double i = 0; i<1.58; i+=0.01)
               {
                BRS_LCD_Draw_CircleLine(63,31,newRadius1,newRadius2,i,1);                   
               }
        
            //Clear the edges to avoid phantoms
            for(double i = 0; i<1.59; i+=0.01)
              {        
                BRS_LCD_Draw_CirclePixel(63,31,newRadius1-1,i,0);
                BRS_LCD_Draw_CirclePixel(63,31,newRadius2+1,i,0); 
              }
          }
        //__________________________________________________________________________[Radius Counter]
        localCount++;
        if(localCount > 40)
          {
            localCount = 0;
            
            //Inner counter
            newRadius1++;
            if(newRadius1 > 15){newRadius1=0;  oldCount=1;}
            
            //Outer counter
            newRadius2++;
            if(newRadius2 > 22){newRadius2=17; oldCount=1;}
          }
        //_________________________________________________________________________[Radius displays]        
      }
////////////////////////////////////////////////////////////////////////////////////////////////////[SECOND HALF]       
      else
      {
        HAL_Delay(5);
        //__________________________________________________________________________[Radian Display]        
        BRS_LCD_Draw_Text_Double(1,55,count,2,1,1);
        //_______________________________________________________________________________[Done Once]
        if(oldCount != 2)
          {
            oldCount = 2;
          
            //LCD Clear
            BRS_LCD_Draw_Shape_RectF(0,9,127,51,0);
          
            //New text display
            vPutStringGLcd("       Radians      ", 0,5);
          
            //Redraw the quarter of circle
            for(double i = 0; i<1.58; i+=0.01) {BRS_LCD_Draw_CircleLine(63,31,newRadius1,newRadius2,i,1);}          
          
            localCount = 0;
            count      = 4.71;
          }
        
        //_____________________________________________________________________[Spin radian counter]
        localCount += 0.01;
        if(localCount >6.27) {localCount = 0;}
        
        count += 0.01;
        if(count >6.27) {count = 0;} 
        
        //_____________________________________________________________________________[DRAW CIRCLE]
        BRS_LCD_Draw_CircleLine(63,31,newRadius1,newRadius2,localCount,1); //draw a line
        BRS_LCD_Draw_CircleLine(63,31,newRadius1,newRadius2,count,0);      //clears behind line
      }
////////////////////////////////////////////////////////////////////////////////////////////////////[DRAWN ONCE]      
      if(state == 0)
        {
          state = 1; 
          vPutStringGLcd("Custom in/out radius", 0,5);
       
          //Stage 1 text drawings
          BRS_LCD_Draw_Text_String(1,48,"Start:",4,1);
          BRS_LCD_Draw_Text_String(1,55,"Edges:",4,1); 
        }
      
////////////////////////////////////////////////////////////////////////////////////////////////////[NEXT ANIMATION]
      if(AnimationCounter == 0)
      {       
        BRS_LCD_Clear_Swipe(1);
        BRS_LCD_Draw_Misc_ScalableBRS(50,5,1,1);         
        vPutStringGLcd("  Next: Oval Pixel  ", 2,5);
        HAL_Delay(2000);          
        BRS_LCD_Clear_Swipe(1);
        AnimationCounter = AnimationTime;
        
        ///VARIABLE RESET///
        localCount = 0;   //
        oldCount   = 0;   //        
        count      = 4.71;//
        countB     = 0;   //        
                          //
        direction1 = 1;   // decrease
        direction2 = 0;   // increase     
        state      = 0;   //
                          //
        newRadius1 = 10;  // will decrease
        newRadius2 = 10;  // will increase
        oldRadius1 = 10;  // will decrease
        oldRadius2 = 10;  // will increase
        ////////////////////        
        
        NextFunction++;      
      }
    } 
//##################################################################################################// OVAL PIXEL   
    if(NextFunction == 2)
    {
     //____________________________________________________________________________[RADIAN COUNTERS]      
       count += 0.02;
       if(count > 6.27){count = 0;}
     //____________________________________________________________________________[RADIUS COUNTERS]
       HAL_Delay(1);
     if(localCount > 30)
     {  localCount = 0;
     //__________________________________[CLEAR OLD PIXELS]
       for(double i = 0; i<6.27; i+=0.01)
          {
            BRS_LCD_Draw_OvalPixel(63, 32, newRadius1, newRadius2, i, 0);
          }        
     
     // X Radius. The second radius is used to clear the pixel
       // New radius
       if(direction1 == 0)
         {
          newRadius1 -= 0.4;
          if(newRadius1 <= 0) {direction1 = 1;}
         }
       
       if(direction1 == 1)
         {
          newRadius1 += 0.4;
          if(newRadius1 >= 35) {direction1 = 0;}
         }       
       
     // Y Radius. The second radius is used to clear the pixel
       // New radius Y      
       if(direction2 == 0)
         {
          newRadius2 -= 1;
          if(newRadius2 <= 0) {direction2 = 1;}
         }
       
       if(direction2 == 1)
         {
          newRadius2 += 1;
          if(newRadius2 >= 20){direction2 = 0;}
         }
       
     //____________________________________________________________________________[DRAW NEW PIXELS]
       for(double i = 0; i<6.27; i+=0.01)
       {
        BRS_LCD_Draw_OvalPixel(63, 32, newRadius1, newRadius2, i, 1);
       }
        
     } 
     localCount++;     

     //_____________________________________________________________________________________________[DRAW RADIUS VALUES]         
     BRS_LCD_Draw_Text_Integer(11,48,(unsigned char)newRadius1,2,1);
     BRS_LCD_Draw_Text_Integer(11,55,(unsigned char)newRadius2,2,1);
        
////////////////////////////////////////////////////////////////////////////////////////////////////[DRAWN ONCE]
     if(state == 0)
       { state = 1;
        
        BRS_LCD_Draw_Text_String(1,48,"X:",4,1);
        BRS_LCD_Draw_Text_String(1,55,"Y:",4,1);         
        vPutStringGLcd("  Elongate circles  ", 0,5);
        
        direction1 = 1;   // decrease
        direction2 = 0;   // increase     
                          //
        newRadius1 = 10;  // will decrease
        newRadius2 = 10;  // will increase
        oldRadius1 = 9;   // will decrease
        oldRadius2 = 11;  // will increase        
       }
      
////////////////////////////////////////////////////////////////////////////////////////////////////[NEXT ANIMATION]
      if(AnimationCounter == 0)
      {       
        BRS_LCD_Clear_Swipe(1);
        BRS_LCD_Draw_Misc_ScalableBRS(50,5,1,1);         
        vPutStringGLcd("Next: Perfect Circle", 2,5);
        HAL_Delay(2000);          
        BRS_LCD_Clear_Swipe(1);
        AnimationCounter = AnimationTime;

        ///VARIABLE RESET///
        localCount = 0;   //
        oldCount   = 0;   //        
        count      = 0;   //
        countB     = 0;   //        
                          //
        direction1 = 0;   // decrease
        direction2 = 0;   // increase     
        state      = 0;   //
                          //
        newRadius1 = 10;  // will decrease
        newRadius2 = 10;  // will increase
        oldRadius1 = 10;  // will decrease
        oldRadius2 = 10;  // will increase
        ////////////////////       
        
        NextFunction++;      
      }
    }     
//##################################################################################################// PERFECT CIRCLES  
    if(NextFunction == 3)
    {
      HAL_Delay(1);
      if(localCount > 60)
      { localCount = 0;
      
        //___________________________________________________________________________[CLEAR CIRCLES]         
        BRS_LCD_Draw_Shape_CircleF(30,30,newRadius1,0);
        BRS_LCD_Draw_Shape_Circle (100,30,newRadius1,0);      
////////////////////////////////////////////////////////////////////////////////////////////////////[COUNTER]
        //Increase or decrease depending on direction
        if(direction1 == 0) {newRadius1++;}
        if(direction1 == 1) {newRadius1--;}
        
        //Change direction when above or below a certain threshold
        if(newRadius1 > 20) {direction1 = 1;}
        if(newRadius1 < 5)  {direction1 = 0;}
        
        //____________________________________________________________________________[DRAW CIRCLES]  
        BRS_LCD_Draw_Shape_CircleF(30,30,newRadius1,1);
        BRS_LCD_Draw_Shape_Circle (100,30,newRadius1,1);
        
        //_____________________________________________________________________________[DRAW RADIUS]          
        BRS_LCD_Draw_Text_Integer(35,55,(unsigned char)newRadius1,2,1);
      }
        localCount++;
////////////////////////////////////////////////////////////////////////////////////////////////////[DRAWN ONCE]
     if(state == 0)
       { state = 1;
        
        BRS_LCD_Draw_Text_String(1,55,"Radius:",4,1);         
        vPutStringGLcd("  Perfect circles  ", 0,5);
        
        direction1 = 1;   // decrease
        newRadius1 = 10;  // will decrease 
       }      
////////////////////////////////////////////////////////////////////////////////////////////////////[NEXT ANIMATION]
      if(AnimationCounter == 0)
      {       
        BRS_LCD_Clear_Swipe(1);
        BRS_LCD_Draw_Misc_ScalableBRS(50,5,1,1);         
        vPutStringGLcd("   Next:  Radians   ", 2,5);
        HAL_Delay(2000);
        BRS_LCD_Clear_Swipe(1);
        AnimationCounter = AnimationTime;

        ///VARIABLE RESET///
        localCount = 0;   //
        oldCount   = 0;   //        
        count      = 0;   //
        countB     = 0;   //        
                          //
        direction1 = 0;   // decrease
        direction2 = 0;   // increase     
        state      = 0;   //
                          //
        newRadius1 = 0;   // will decrease
        newRadius2 = 0;   // will increase
        oldRadius1 = 0;   // will decrease
        oldRadius2 = 0;   // will increase
        ////////////////////           
        
        NextFunction++;      
      }
    }    
//##################################################################################################// RADIANS
    if(NextFunction == 4)
    {
      HAL_Delay(10);
      if(localCount > 10)
      {  localCount = 0;


////////////////////////////////////////////////////////////////////////////////////////////////////[COUNTER]      
       count+=0.1;
       if(count > 6.2) {count = 0;}
       BRS_LCD_Draw_Text_Double(55,29,count,1,1,1);
      
      
      
      
      }
      localCount++;
////////////////////////////////////////////////////////////////////////////////////////////////////[DRAWN ONCE]
     if(state == 0)
       { state = 1;
        
       // TEXT
        BRS_LCD_Draw_Text_String(1,55,"Radians:",4,1);
        vPutStringGLcd("   Radian Values   ", 0,5);
        
       // Middle Circle
        BRS_LCD_Draw_Shape_Circle(63,31,10,1);
        
        direction1 = 1;   // decrease
        newRadius1 = 10;  // will decrease 
       }        
      
      //////////////////////////////////////////////////////////////////////////////[NEXT ANIMATION]
      if(AnimationCounter == 0)
      {      
        BRS_LCD_Clear_Swipe(1);
        BRS_LCD_Draw_Misc_ScalableBRS(50,5,1,1);         
        vPutStringGLcd(" Next: Circle Pixel ", 2,5);
        HAL_Delay(2000);
        BRS_LCD_Clear_Swipe(1);
        AnimationCounter = AnimationTime;

        ///VARIABLE RESET///
        localCount = 4.5;   //
        oldCount   = 0;   //        
        count      = 0;   //
        countB     = 0;   //        
                          //
        direction1 = 0;   // decrease
        direction2 = 0;   // increase     
        state      = 0;   //
                          //
        newRadius1 = 10;  // will decrease
        newRadius2 = 10;  // will increase
        oldRadius1 = 0;   // will decrease
        oldRadius2 = 0;   // will increase
        ////////////////////             
        
        NextFunction = 0;      
      }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////[NEXT ANIMATION COUNTER]
    AnimationCounter--;
////////////////////////////////////////////////////////////////////////////////////////////////////[LOADING BAR DRAWING]
    loadingBarCoord = floor(127-floor(AnimationCounter/loadingRatio));
    
    if(loadingBarCoord > 0 && loadingBarCoord<127)
    {
      if(oldCoord != loadingBarCoord)
      {
        BRS_LCD_Draw_Shape_RectF(loadingBarCoord, 61, 1, 3, 1);
        oldCoord = loadingBarCoord;
      }
    }
  
  
  }
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Demo_Text(void)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 04/04/2022
//__________________________________________________________________________________________________
//	Function:	| 
//                      | Demonstrates the easy use and implementations of BRS_LCD_Text functions
//                      | 
//                      | This demonstration shows uses of the LCD_Text functions by showing the
//                      | custom BRS alphabet as well as how the text can easily be drawn inside
//                      | boxes of custom dimmensions with LCD_Draw_Text_Box
//                      | 
//                      | This function also demonstrates how the Draw_Text_Variable can be used
//                      | to display tests on your LCD and be used to debug some programs
//                      | 
//                      | LCD_Text allows you to draw letters at any coordinates on your screen 
//                      | without the restrictions of lines and columns. Which is absolutely needed
//                      | when drawing graphs and dials on your screen
//                      | 
//                      | DO note however, that LCD_Text are far slower than the default GLCD
//                      | functions used to draw texts. And they are better used only when
//                      | the specific case necessites them.
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
//////////////////////////////////////////////////////////////////////////////////////////////[INIT]   
 Demo_TitleSwipe("   Text Functions   ");
 int countA = 0;
 //int countB = 0; 
//////////////////////////////////////////////////////////////////////////////////////////////[DEMO] 

   BRS_LCD_Draw_Text_String(0,0,"0123456789!\"#$%'()*+,-./",4,1);
   BRS_LCD_Draw_Text_String(0,7,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",4,1);
   BRS_LCD_Draw_Text_String(0,14,"{}[]`_/^~|¬?&µ±°",4,1);
   
 while(1)
 {
   countA = countA+1;
   HAL_Delay(200);
    
   if(countA > 999) {countA=0;}
   
   BRS_LCD_Draw_Text_Integer(10,30,countA,3,1);  
 }
}





void BRS_LCD_Demo_Clear(void);






////////////////////////
//_INTERNAL_FUNCTIONS_//
////////////////////////

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
size_t strlen(const char *pString)
{
    unsigned int length = 0;

    while(*pString++ != 0) {
        length++;
    }
    return length;
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§








//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void Demo_TitleSwipe(char const *NameOfDemo)
{
  vClearGLcd(0xFF);
  BRS_LCD_Draw_Misc_ScalableBRS(4,18,6,0);

  HAL_Delay(500);
  BRS_LCD_Clear_Swipe(0);

  vPutStringGLcd("    BRS LCD DEMO    ", 2,5);  
  vPutStringGLcd(NameOfDemo, 4,5);
  vPutStringGLcd("   By Lyam / S.C.   ", 6,5);  
  
  HAL_Delay(3000);
  
  BRS_LCD_Clear_Swipe(3);  
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§

//void BRS_LCD_Draw_Text_Line(unsigned char x, unsigned char y, unsigned char *string, unsigned char font);
//void BRS_LCD_Draw_Text_Box (unsigned char x, unsigned char y, unsigned char *string, unsigned char font, unsigned char LR, unsigned char UD);