
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
** New:  BRS_Lcd_Objects.h --- By Shawn Couture   *************************************************
** Date: 24/03/2022               *****************************************************************
** This file initialises the classes used to generate GLCD objetcs such as a toggle slider
** switching between ON/OFF, or an analogue graph.
** All the avaliable options are explained next to their variables
***************************************************************************************************/

#ifndef BRS_LCD_OBJECTS
  #define BRS_LCD_OBJECTS

//================================================================================================//
//	Include
//================================================================================================//
#include "stm32f4xx_hal.h"                       //Définition pour le KIT ARM
#include "stdbool.h"

#include "GLcd.h"
#include "math.h"
#include "BRS_Lcd.h"
#include "BRS_Lcd_Font.h"

//================================================================================================//
//	Slider Object
//================================================================================================//

class BRS_LCD_Toggle_Slider_Class
{
//##########################################################################################################################################################//              
  private:
//##########################################################################################################################################################//

//-COMPARED VARIABLES-//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [COMPARED VARIABLES]
  
  bool oldState;
    
  unsigned char oldWidth;
  unsigned char oldHeight;
  unsigned char oldPosX;
  unsigned char oldPosY;
  
  float         currentX;
  float         wantedX;
  unsigned char dotRadius;
  
//##########################################################################################################################################################//              
  public:
//##########################################################################################################################################################//
    
//-CONSTRUCTOR-/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [CONSTRUCTOR]
   BRS_LCD_Toggle_Slider_Class(unsigned char x, unsigned char y, unsigned char wantedWidth, unsigned char wantedHeight);
//-FUNCTIONS-///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [FUNCTIONS]
   void drawSlider (void);                      // Draws and update values on the screen. The speed at which this is called will affect animations speeds
                                                // The graphs automatically clears newly dead pixels.
//-VARIABLES-///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [VARIABLES]       
   bool value;                                  // Sets how filled the graph must be. Use this to input the value you want the graph to be displaying
   bool reDraw;                                 // Specifies the slider that it needs to be redrawn.

//-SCREEN COORDS-///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [SCREEN COORDS]   
  unsigned char width;                           // Sets how wide your graph, including the borders, should be [ GRAPH IS DRAWN FROM TOP LEFT TO RIGHT ]
  unsigned char height;                          // Sets how tall your graph, including the borders, should be [ GRAPH IS DRAWN FROM TOP TO BOTTOM ]
  unsigned char xPos;                            // X screen coordinate where the graph will be displayed [TOP LEFT COORD]
  unsigned char yPos;                            // Y screen coordinate where the graph will be displayed [TOP LEFT COORD]
  
//-SPECIAL PARAMETERS-//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [SPECIAL PARAMETERS]
  
  bool displayState;                             // Will display ON/OFF on the slider. Make sure it is of apropriated size. (minimum 20 wide, 7 tall)
  float sliderSpeed;                             // Default to 0.01. Defines how fast the slider will move forward/backward depending on the new value
  
  
};


//================================================================================================//
//	GRAPH OBJECT
//================================================================================================//

class BRS_LCD_Graph_Class
{
//##########################################################################################################################################################//              
  private:
//##########################################################################################################################################################//

//-COMPARED VARIABLES-//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [COMPARED VARIABLES]
  float        oldValue;
  float        oldMax;  
  float        oldMin;
  
  unsigned char oldWidth;
  unsigned char oldHeight;
  unsigned char oldPosX;
  unsigned char oldPosY;
  
  unsigned char oldDirection          : 2;
  unsigned char oldBorders            : 3;
  unsigned char oldFilling            : 3;
  
  float         oldBlinkingThreshold;
  unsigned char oldBlinkEdges         : 1;
  unsigned char oldAnimatedFill       : 1;
  float         oldAnimationCounter;
  
  unsigned char oldRatio;
  
//##########################################################################################################################################################//              
  public:
//##########################################################################################################################################################//
    
//-CONSTRUCTOR-/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [CONSTRUCTOR]
   BRS_LCD_Graph_Class(unsigned char x, unsigned char y, unsigned char wantedWidth, unsigned char wantedHeight, unsigned char wantedDirection, float wantedMin, float wantedMax);
//-FUNCTIONS-///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [FUNCTIONS]
   void drawGraph (void);                        // Draws and update values on the screen. The speed at which this is called will affect animations speeds
    
//-VARIABLES-///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [VARIABLES]       
  float value;                                  // Sets how filled the graph must be. Use this to input the value you want the graph to be displaying  
  float min;                                    // The lowest your graphed value can reach
  float max;                                    // The highest your graphed value can reach

//-SCREEN COORDS-///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [SCREEN COORDS]   
  unsigned char width;                           // Sets how wide your graph, including the borders, should be [ GRAPH IS DRAWN FROM TOP LEFT TO RIGHT ]
  unsigned char height;                          // Sets how tall your graph, including the borders, should be [ GRAPH IS DRAWN FROM TOP TO BOTTOM ]
  unsigned char xPos;                            // X screen coordinate where the graph will be displayed [TOP LEFT COORD]
  unsigned char yPos;                            // Y screen coordinate where the graph will be displayed [TOP LEFT COORD]

//-DRAWING PARAMETERS-//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [DRAWING PARAMETERS]
  unsigned char graphDirection : 2;              // 0 = Left -> Right 
                                                 // 1 = Top -> Bottom 
                                                 // 2 = Right -> Left 
                                                 // 3 = Bottom -> Top 
  
  unsigned char graphBorders   : 3;              // 0 = Transparent Borders                             NO BORDERS
                                                 // 1 = Filled contour borders                          [______] (just imagine there is a line on top aswell)
                                                 // 2 = Bracket border edges                            [      ]
                                                 // 3 = Rounded filled contour borders                  (______) (just imagine there is a line on top aswell)
                                                 // 4 = Rounded bracket border edges                    (      )
                                                 // 5 = Battery Shape Left
                                                 // 6 = Battery Right
  
  unsigned char graphFilling : 3;                // 0 = Transparent (pixel clear) filled
                                                 // 1 = Filled                                          [###########]
                                                 // 2 = Bars                                            [|||||||||||]
                                                 // 3 = Checker pattern
                                                 // 4 = Diagonal lines                                  [\\\\\\\\\\\]
                                                 // 5 = Value Edges Only                                [    |      ]
  
  bool reDraw;                                   // Calls a complete redraw of the graph
  
//-SPECIAL PARAMETERS-//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [SPECIAL PARAMETERS]
  
  unsigned char pixelGap;                        // Amount of pixels seperating the border with the filling.
                                                 // There is no limits to this parameter, be careful when you use it. We recommend setting it to 0 or 1.
  
  unsigned char startFromMiddle : 1;             // 0/1 // value starts from the middle of the graph when set to 1
  
  float blinkingThreshold;                       // Filled area will blink on/off when "value" is below this number. 0 will turn off this functionality
  
  unsigned char blinkEdges : 1;                  // 0/1 // Makes the top most bar blink on/off. 0 will disable this functionality
  
  unsigned char animatedFill : 1;                // 0/1 // Toggles an animation pulsing from min to max at 5 times the update rate of the set counter
  
  float animationCounter;                        // Counter counting down, with automatic reset. When reaching 0, animations will update. (Default: 10000)
  
  
  

  
};

#endif 