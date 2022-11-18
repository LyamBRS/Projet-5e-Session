
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
** New:      BRS_Lcd.h --- By Shawn Couture   *****************************************************
** Original: GLcd.h    --- By Alain Champagne *****************************************************
** Date: 24/03/2022               *****************************************************************
***************************************************************************************************/

#ifndef BRS_LCD_FUNCTIONS
  #define BRS_LCD_FUNCTIONS

//================================================================================================//
//	Include
//================================================================================================//
#include "stm32f4xx_hal.h"                       //Définition pour le KIT ARM
//#include "IO_BUS.h"       
//#include "main.h"
#include "stdbool.h"

#include "GLcd.h"
#include "math.h"
#include "BRS_Lcd_Font.h"
//================================================================================================//
//	DEMONSTRATOR // these functions will loop inside of themselves to show what the normal
//                   // function can be used for.
//================================================================================================//
void BRS_LCD_Demo_Line(void);

void BRS_LCD_Demo_Circles(void);

void BRS_LCD_Demo_Clear(void);

//================================================================================================//
//	Pixel & Lines
//================================================================================================//
void BRS_LCD_Draw_Pixel(double x, double y, bool state);
void BRS_LCD_Draw_Line (double x1, double y1, double x2, double y2, bool state);

void BRS_LCD_Draw_OvalPixel  (unsigned char x, unsigned char y, double radiusX, double radiusY,            double radian, bool state);
void BRS_LCD_Draw_CirclePixel(unsigned char x, unsigned char y, double radius,                             double radian, bool state);
void BRS_LCD_Draw_CircleLine (unsigned char x, unsigned char y, double InsideRadius, double OutsideRadius, double radian, bool state);

//================================================================================================//
//	Rectangles
//================================================================================================//
void BRS_LCD_Draw_Shape_RectF(unsigned char x, unsigned char y, unsigned char width, unsigned char height, bool state);
void BRS_LCD_Draw_Shape_Rect (unsigned char x, unsigned char y, unsigned char width, unsigned char height, bool state);

//================================================================================================//
//	Circles
//================================================================================================//
void BRS_LCD_Draw_Shape_CircleF(unsigned char x, unsigned char y, double radius, bool state);
void BRS_LCD_Draw_Shape_Circle (unsigned char x, unsigned char y, double radius, bool state);

//================================================================================================//
//	Text/Strings
//================================================================================================//
void BRS_LCD_Draw_Text_Double  (unsigned char x, unsigned char y, double Number,unsigned char decimals, unsigned char maxDigits, bool state);
void BRS_LCD_Draw_Text_Integer (unsigned char x, unsigned char y, int Number, unsigned char maxDigits, bool state);
void BRS_LCD_Draw_Text_Hexa    (unsigned char x, unsigned char y, int Number, unsigned char maxDigits, bool state);

void BRS_LCD_Draw_Text_Char    (unsigned char x, unsigned char y, unsigned char letter,   unsigned char font, bool state);
void BRS_LCD_Draw_Text_String  (unsigned char x, unsigned char y, char const string[], unsigned char font, bool state);
void BRS_LCD_Draw_Text_Box     (unsigned char x, unsigned char y, unsigned char *string,  unsigned char font, unsigned char LR, unsigned char UD);

//================================================================================================//
//	Logo + header
//================================================================================================//
void BRS_LCD_Draw_Misc_ScalableBRS(unsigned char x, unsigned char y, unsigned char scale, bool state);
void BRS_LCD_Draw_Misc_LabHeader(char const *lab, char const *Table);                            //("      LAB9-416      ","    SHAWN COUTURE    ")

//================================================================================================//
//	Animations // NOT DONE
//================================================================================================//
void BRS_LCD_Animations_Outline(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char lineLenght, unsigned char delay, bool state);
void BRS_LCD_Animations_ScreenSaver(unsigned char delay, bool state);

//================================================================================================//
//	LCD Clears
//================================================================================================//
void BRS_LCD_Clear_Swipe(unsigned char direction); 






//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//	INTERNAL FUNCTIONS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void Demo_TitleSwipe(char const *NameOfDemo);
size_t strlen(const char *pString);


#endif 