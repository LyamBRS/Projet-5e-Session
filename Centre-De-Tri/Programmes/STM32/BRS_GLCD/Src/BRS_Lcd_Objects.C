/**************************************************************************************************
***************************************************************************************************
***************************************************************************************************

    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

***************************************************************************************************
** New:  BRS_Lcd_Object.c --- By Shawn Couture   **************************************************
** Date: 20/04/2022                              **************************************************
***************************************************************************************************/
//================================================================================================//
//	Include
//================================================================================================//
#include "BRS_Lcd_Objects.h"


//================================================================================================//
//     || WARNING || C++ || WARNING || C++ || WARNING || C++ || WARNING || C++ || WARNING ||
//================================================================================================//
      
//================================================================================================//
//     Enabled / Disabled Slider
//================================================================================================//
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
BRS_LCD_Toggle_Slider_Class::BRS_LCD_Toggle_Slider_Class(unsigned char x, unsigned char y, unsigned char wantedWidth, unsigned char wantedHeight)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture
//	Date made:	| 27/04/2022
//__________________________________________________________________________________________________
//	Function:	| Slider constructor
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
///////////////////////////////////////////////////////////////////////////////////[Sets parameters]  

  width        = wantedWidth;
  height       = wantedHeight;
  xPos         = x;
  yPos         = y;
  
  displayState = 1;
  sliderSpeed  = 0.005;
  
////////////////////////////////////////////////////////////////////////////////[Default parameters]
  oldState  = 0;  
  oldWidth  = 0;
  oldHeight = 0;
  oldPosX   = 0;
  oldPosY   = 0;

  currentX  = x + (height/2);
  wantedX   = 0;
  dotRadius = 0;
  
  reDraw = 1;
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Toggle_Slider_Class::drawSlider(void)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture
//	Date made:	| 27/04/2022
//__________________________________________________________________________________________________
//	Function:	| Draws the slider on the screen.
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
 //##########################################//####################################_Local Variables_ 
   bool eraseOld = 0;                        //
   bool drawBorder = 0;                      //
   bool updateState = 0;                     //
 //##########################################//####################################_Local Variables_   

////////////////////////////////////////////////////////////////////////////////////////////[Update]
  if((xPos != oldPosX) || (yPos != oldPosY) || (height != oldHeight) || (width != oldWidth))
  {
    eraseOld    = true;
    drawBorder  = true;
    updateState = true;
  }
////////////////////////////////////////////////////////////////////////////////////////////[ReDraw]  
  if(reDraw == 1) // Only draws above the current slider and does not erase the old one.
  {
    drawBorder  = true;
    updateState = true;
    eraseOld    = false;
  }
//////////////////////////////////////////////////////////////////////////////////////[Update State]
  if((oldState != value) || updateState == 1)
    {
      dotRadius  = (height/2)-1; //-1 is there to make sure the circle does not touch the borders 
      
      wantedX    = ((xPos + width - dotRadius)*value) + ((xPos + dotRadius + 1)* !value);
      
      //Make the slider at the right X from the start when redraw is called
      if(reDraw == 1) currentX = (xPos + dotRadius + 1);
    }
///////////////////////////////////////////////////////////////////////////////////////[Move Slider]
  if(wantedX != currentX)
    {
      if(currentX < wantedX) currentX += sliderSpeed; //Move left
      if(currentX > wantedX) currentX -= sliderSpeed; //Move right
      
      //Close enough
      if((currentX > wantedX-sliderSpeed) && (currentX < wantedX+sliderSpeed)) currentX = wantedX;
      
      updateState = 1;      
    }
//================================================================================================//  
//////////////////////////////////////-[ Erasing ]-/////////////////////////////////////////////////  
//================================================================================================// 
  if(eraseOld == 1)
  {
    BRS_LCD_Draw_Shape_RectF(oldPosX, oldPosY, oldWidth, oldHeight, 0);
  }
//================================================================================================//
//////////////////////////////////////-[ Drawing ]-/////////////////////////////////////////////////  
//================================================================================================//  
///////////////////////////////////////////////////////////////////////////////////////[Draw Middle]
  
  if(updateState == 1)
  {
    if(value == 1)
    {    
      //Right Inner Circle
      BRS_LCD_Draw_Shape_CircleF((unsigned char)currentX, (unsigned char)yPos + dotRadius + 1, dotRadius-1, 1);
    }
    else
    {
      //Clear circle backward
      BRS_LCD_Draw_Shape_CircleF((unsigned char)currentX, (unsigned char)yPos + dotRadius + 1, dotRadius-1, 0);  
    }
  }
//////////////////////////////////////////////////////////////////////////////////////[Draw Borders]  
  if(drawBorder == 1)
  {
    //2 filled edge circles
    BRS_LCD_Draw_Shape_CircleF(xPos + dotRadius, yPos + dotRadius + 1, dotRadius, 1);
    BRS_LCD_Draw_Shape_CircleF(xPos + width - dotRadius+1, yPos + dotRadius + 1, dotRadius, 1);    
    //border
    BRS_LCD_Draw_Shape_Rect(xPos + dotRadius, yPos+1, width - dotRadius*2 + 3, height-1, 1);
    
    //Clear inner of circles
    BRS_LCD_Draw_Shape_CircleF(xPos + dotRadius+1, yPos + dotRadius + 1, dotRadius-1, 0);
    BRS_LCD_Draw_Shape_CircleF(xPos + width - dotRadius, yPos + dotRadius + 1, dotRadius-1, 0);

    //Clear insides of the rectangle
    BRS_LCD_Draw_Shape_Rect(xPos + (dotRadius*2)+2, yPos+2, width - (dotRadius*3)-1, height-3, 0);    
    
  }
  
////////////////////////////////////////////////////////////////////////////////////////[Redraw Dot]
  if((wantedX == currentX) && (updateState) && (currentX >= (xPos + dotRadius + 1)))
  {
    //Filled dot
    BRS_LCD_Draw_Shape_CircleF((unsigned char)currentX, (unsigned char)yPos + dotRadius + 1, dotRadius, 1);  
      
    //Cleared insides of right circle
    BRS_LCD_Draw_Shape_CircleF((unsigned char)currentX, (unsigned char)yPos + dotRadius + 1, dotRadius-1, 0);
    
    // TEXT //
    if(displayState == true)
    {
      if(value == 1) // ON
        {
          BRS_LCD_Draw_Text_String(xPos + dotRadius - 1, yPos + dotRadius - 1, "ON", 4,0);      
        }
      else // OFF
        {
          BRS_LCD_Draw_Text_String(xPos + width - dotRadius-14, yPos + dotRadius - 1, "OFF", 4,1);
        }
    }
  }
    
//================================================================================================//
//////////////////////////////////////-[ UPDATE ]-/////////////////////////////////////////////////  
//================================================================================================//
  oldHeight = height;
  oldWidth  = width;
  oldState  = value;
  reDraw = 0;
  
  oldPosY = yPos;
  oldPosX = xPos;
  
  //HAL_Delay(500);
}
      
                
      
      
                
//================================================================================================//
//     Graph
//================================================================================================//
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
BRS_LCD_Graph_Class::BRS_LCD_Graph_Class(unsigned char x, unsigned char y, unsigned char wantedWidth, unsigned char wantedHeight, unsigned char wantedDirection, float wantedMin, float wantedMax)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture
//	Date made:	| 20/04/2022
//__________________________________________________________________________________________________
//	Function:	| Graph Constructor
//			| 
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  xPos           = x;
  yPos           = y;
  width          = wantedWidth;
  height         = wantedHeight;
  graphDirection = wantedDirection;
  min            = (float) wantedMin;
  max            = (float) wantedMax;
  
  value = min;
  
  // PRESETS //
  graphBorders   = 1;
  graphFilling   = 1;
  
  oldValue = 0;
  oldMax   = 0;  
  oldMin   = 0;
  
  oldWidth  = 0;
  oldHeight = 0;
  oldPosX   = 0;
  oldPosY   = 0;
  
  oldDirection          = 0;
  oldBorders            = 0;
  oldFilling            = 0;
  
  oldBlinkingThreshold  = 0;
  oldBlinkEdges         = 0;
  oldAnimatedFill       = 0;
  oldAnimationCounter   = 0;

  startFromMiddle = 0;
  
  pixelGap = 1;
  
}


//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Graph_Class::drawGraph(void)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture
//	Date made:	| 20/04/2022
//__________________________________________________________________________________________________
//	Function:	| Updates the graph objects
//			| 
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  //##########################################//####################################_Local Variables_ 
    bool updatePos        = 0;                // These variables are used to avoid
    bool updateSize       = 0;                // constantly executing lines of codes
    bool updateFill       = 0;                // for no reasons, and thus save on
    bool updateBorder     = 0;                // processing speeds.
    bool updateAnimations = 0;                //
    
    bool clearGraphArea   = 0;                // Clears entire graph when something
                                              // drastic changes
    
    bool valueChanged     = 0;                // Value was updated
    bool wantedState      = 0;                // decides if we clear or drawn the fillings of the graph
    
    unsigned char tempVariable = 0;
    unsigned char tempVariable2 = 0;
    
    float ratio = 0;
    
    unsigned char startX  = 0;                // Value used in for loops to better understand the
    unsigned char startY  = 0;                // Maximums and Minimums
    unsigned char filledX = 0;
    unsigned char filledY = 0;
    
    unsigned char startClearX = 0;
    unsigned char startClearY = 0;
    
    unsigned char clearX = 0;
    unsigned char clearY = 0;    

  //##########################################//####################################_Local Variables_
//================================================================================================//    
//================================================================================================//
// Clamp Value
//================================================================================================//    
//================================================================================================//
  if(value > max) {value = max;}  
  if(value < min) {value = min;}      
    
//================================================================================================//    
//================================================================================================//
// Value comparing and updates settings
//================================================================================================//    
//================================================================================================//
    if(reDraw == true)
    {
      reDraw = false;
      updatePos        = true;
      updateSize       = true;
      updateFill       = true;
      updateBorder     = true;
      updateAnimations = true;
      
      clearGraphArea  = true;
      valueChanged = 1;      
    }
///////////////////////////////////////////////////////////////////////////////////////////////[Pos]
    if((xPos != oldPosX) || (yPos != oldPosY) || (width != oldWidth) || (height != oldHeight) || (graphDirection != oldDirection) || (graphBorders != oldBorders) || (graphFilling != oldFilling))
    {
      //Everything needs to be redrawn, cuz the size or positions changes everything
      updatePos        = true;
      updateSize       = true;
      updateFill       = true;
      updateBorder     = true;
      updateAnimations = true;
      
      clearGraphArea  = true;
    }    
/////////////////////////////////////////////////////////////////////////////////////////////[VALUE]         
    if(oldValue != value)
    {
      valueChanged = 1;
    }
    
////////////////////////////////////////////////////////////////////////////////////////[Animations]      
    // Counter //
    if(oldAnimationCounter == 0)
    {
      updateAnimations = true;
      oldAnimationCounter = animationCounter;
    }
    oldAnimationCounter--;
//================================================================================================//    
//================================================================================================//
// Graph clearing
//================================================================================================//  
//================================================================================================//
  if(clearGraphArea)
  {
    BRS_LCD_Draw_Shape_RectF(oldPosX, oldPosY, oldWidth, oldHeight, 0);
  }
    
//================================================================================================//    
//================================================================================================//
// Draw Borders
//================================================================================================//  
//================================================================================================//    
  if(updateBorder == 1)
  {  oldBorders = graphBorders;

    // Swich for graph Border Style //
    switch(graphBorders)
    {
      case(0): // Transparent borders
              BRS_LCD_Draw_Shape_Rect(xPos, yPos, width, height, 0);
              break;
              
      case(1): // Filled contour 
              BRS_LCD_Draw_Shape_Rect(xPos, yPos, width, height, 1);
              break;
              
      case(2): // Bracket Edges
              
              //Changes depending on graph direction
              switch(graphDirection)
              {
                case(0): // Horizontal brackets
                case(2):
                        // TOP
                        BRS_LCD_Draw_Shape_Rect(xPos, yPos,                1, height,1); //left
                        BRS_LCD_Draw_Shape_Rect(xPos, yPos,          width/4,      1,1); //Top Left
                        BRS_LCD_Draw_Shape_Rect(xPos, yPos+height-1, width/4,      1,1); //Bottom left
                        
                        // Bottom
                        BRS_LCD_Draw_Shape_Rect(xPos+width-1, yPos, 1, height,1);                     //right
                        BRS_LCD_Draw_Shape_Rect(xPos+width - (width/4)-1, yPos, width/4, 1,1);        //Left
                        BRS_LCD_Draw_Shape_Rect(xPos+width - (width/4)-1, yPos+height-1, width/4, 1,1);//Right                         
                break;
  
                case(1): // vertical brackets
                case(3):
                        // TOP
                        BRS_LCD_Draw_Shape_Rect(xPos,         yPos, width, 1,      1); //Top
                        BRS_LCD_Draw_Shape_Rect(xPos,         yPos, 1,    height/3,1); //Left
                        BRS_LCD_Draw_Shape_Rect(xPos+width-1, yPos, 1,    height/3,1); //Right
                        
                        // Bottom
                        BRS_LCD_Draw_Shape_Rect(xPos,         yPos+height-1,            width,       1,1); //Top
                        BRS_LCD_Draw_Shape_Rect(xPos,         yPos+height - (height/3), 1,    height/3,1); //Left
                        BRS_LCD_Draw_Shape_Rect(xPos+width-1, yPos+height - (height/3), 1,    height/3,1); //Right     
                  break;                
              }   
              break;
              
      case(3): // Rounded filled edges
              BRS_LCD_Draw_Shape_Rect(xPos+1      , yPos           , width-2, 1       , 1);
              BRS_LCD_Draw_Shape_Rect(xPos        , yPos+1         , 1      , height-2, 1);     
              BRS_LCD_Draw_Shape_Rect(xPos+width-1, yPos+1         , 1      , height-2, 1);     
              BRS_LCD_Draw_Shape_Rect(xPos+1      , yPos+height-1  , width-2, 1       , 1);               
              break;
              
      case(4): // Rounded bracket edges
              //Changes depending on graph direction
              switch(graphDirection)
              {
                case(0): // Horizontal brackets
                case(2):
                        // LEFT
                        BRS_LCD_Draw_Shape_Rect(xPos, yPos+1,                    1, height-2,1); //left
                        BRS_LCD_Draw_Shape_Rect(xPos+1, yPos,          (width/4)-1,        1,1); //Top Left
                        BRS_LCD_Draw_Shape_Rect(xPos+1, yPos+height-1, (width/4)-1,        1,1); //Bottom left
                        
                        // RIGHT
                        BRS_LCD_Draw_Shape_Rect(xPos+width-1, yPos+1, 1, height-2,1);                    //right
                        BRS_LCD_Draw_Shape_Rect(xPos+width - (width/4)-1, yPos, (width/4), 1,1);         //Left
                        BRS_LCD_Draw_Shape_Rect(xPos+width - (width/4)-1, yPos+height-1, (width/4), 1,1);//Right                         
                break;
  
                case(1): // vertical brackets
                case(3):
                  
                        tempVariable = (height/3)-2;
                        
                        if(tempVariable < 2)
                        {
                          tempVariable = 2;
                        }
                          
                        // TOP
                        BRS_LCD_Draw_Shape_Rect(xPos+1,       yPos, width-2,            1,1); //Top
                        BRS_LCD_Draw_Shape_Rect(xPos,         yPos+1,     1, tempVariable,1); //Left
                        BRS_LCD_Draw_Shape_Rect(xPos+width-1, yPos+1,     1, tempVariable,1); //Right
                        
                        // Bottom
                        BRS_LCD_Draw_Shape_Rect(xPos+1,         yPos+height-1,            width-2,       1,1); //Top
                        BRS_LCD_Draw_Shape_Rect(xPos,         yPos+height - tempVariable-1, 1,    tempVariable,1); //Left
                        BRS_LCD_Draw_Shape_Rect(xPos+width-1, yPos+height - tempVariable-1, 1,    tempVariable,1); //Right     
                  break;                
              }                     
              break;
              
      case(5): // Battery shape Right
                
               //Changes depending on graph direction
              switch(graphDirection)
              {
                case(0): // LEFT->RIGHT

                        tempVariable = height/3;
                        tempVariable2= width/18;
                  
                        if(tempVariable  < 1) {tempVariable = 1;}
                        if(tempVariable2 < 1) {tempVariable2 = 1;}
                        if(tempVariable2 > 3) {tempVariable2 = 3;}                      
                  
                        BRS_LCD_Draw_Shape_Rect(xPos,yPos,1,height,1);                              // Bottom of battery
                        BRS_LCD_Draw_Shape_Rect(xPos,yPos,width-1,1,1);                             // Top                  
                        BRS_LCD_Draw_Shape_Rect(xPos,yPos+height-1,width-1,1,1);                    // Bottom
                  
                        BRS_LCD_Draw_Shape_Rect(xPos+width-1, yPos+1, 1, height-2,1);               //battery top
                        BRS_LCD_Draw_Shape_RectF(xPos+width, yPos+tempVariable, tempVariable2, tempVariable,1); //battery tip                  
                  
                break;
                
                case(1): //TOP -> DOWN

                        tempVariable  = height/18;
                        tempVariable2 = width/3;
                  
                        if(tempVariable  < 1) {tempVariable = 1;}
                        if(tempVariable2 < 1) {tempVariable2 = 1;}
                        if(tempVariable2 > 3) {tempVariable2 = 3;}                      
                  
                        BRS_LCD_Draw_Shape_Rect(xPos,yPos,width,1,1);            // Bottom of battery (top)
                        BRS_LCD_Draw_Shape_Rect(xPos,yPos,1,height-1,1);         // Left                  
                        BRS_LCD_Draw_Shape_Rect(xPos+width-1,yPos,1,height-1,1); // Right
                  
                        BRS_LCD_Draw_Shape_Rect(xPos+1, yPos+height-1, width-2, 1,1); //battery top
                        BRS_LCD_Draw_Shape_RectF(xPos+tempVariable2, yPos+height, tempVariable2, tempVariable,1); //battery tip                   
                  
                break;
  
                case(2): // RIGHT -> LEFT

                        tempVariable = height/3;
                        tempVariable2= width/18;
                  
                        if(tempVariable  < 1) {tempVariable = 1;}
                        if(tempVariable2 < 1) {tempVariable2 = 1;}
                        if(tempVariable2 > 3) {tempVariable2 = 3;}                      
                  
                        BRS_LCD_Draw_Shape_Rect(xPos+width-1,yPos,1,height,1);                        // Bottom of battery (Right)
                        BRS_LCD_Draw_Shape_Rect(xPos+1,yPos,width-1,1,1);                             // Top                  
                        BRS_LCD_Draw_Shape_Rect(xPos+1,yPos+height-1,width-1,1,1);                    // Bottom
                  
                        BRS_LCD_Draw_Shape_Rect(xPos, yPos+1, 1, height-2,1);                                         // battery top
                        BRS_LCD_Draw_Shape_RectF(xPos-tempVariable2, yPos+tempVariable, tempVariable2, tempVariable,1); // battery tip                          
                  
                break;
                
                case(3): // TOP -> DOWN
                  

                  tempVariable  = (height/18);
                  tempVariable2 = width/3;
                  
                  if(tempVariable  < 1) {tempVariable = 1;}
                  if(tempVariable2 < 1) {tempVariable2 = 1;}
                  if(tempVariable2 > 3) {tempVariable2 = 3;}                      
                  
                  BRS_LCD_Draw_Shape_Rect(xPos,yPos+height-1,width,1,1);     // Bottom of battery (bottom)
                  BRS_LCD_Draw_Shape_Rect(xPos,yPos+1,1,height-1,1);         // Left                  
                  BRS_LCD_Draw_Shape_Rect(xPos+width-1,yPos+1,1,height-1,1); // Right
                  
                  BRS_LCD_Draw_Shape_Rect(xPos+1, yPos, width-2, 1,1);                             //battery top
                  BRS_LCD_Draw_Shape_RectF(xPos+tempVariable2, yPos-tempVariable, tempVariable2, tempVariable,1); //battery tip                   
                  
                  
                break;                
              }
    }
  }

//================================================================================================//    
//================================================================================================//
// Maths and values
//================================================================================================//  
//================================================================================================//
if(valueChanged == 1)
{
  if(startFromMiddle)
///////////////////////////////////////////////////////[Value is drawn from the middle of the graph]       
  {
    // Swichfor graph directions //
    switch(graphDirection)
    {
      case(0): // Left -> Right // Only X matters
              
              ratio = floor((((value - min) / (max - min))) * ((width-2) - (pixelGap*2)));
              
              startX = xPos + 1 + pixelGap;
              startY = yPos + 1 + pixelGap;
              
              //filled area sized
              filledX = (unsigned char) ratio;
              filledY = (height-2) - (pixelGap*2);              
              
              //Clear
              startClearX = startX + filledX;
              startClearY = startY; 
              
              //Cleared area sized              
              clearX = ((width-2) - (pixelGap*2)) - filledX;
              clearY = filledY;
              
              //Clamping
              if((filledX+xPos+1) >= (xPos+width-1))
              {
                filledX = (xPos+width-2);
              }

              break;
              
      case(1): // Top -> Bottom

              ratio = floor(((value - min) / (max - min)) * ((height-2) - (pixelGap*2)));
              
              startX = xPos + 1 + pixelGap;
              startY = yPos + 1 + pixelGap;
              
              //filled area sized
              filledX = ((width-2) - (pixelGap*2));
              filledY = (unsigned char) ratio;

              //Clear
              startClearX = startX;
              startClearY = startY + filledY; 
              
              //Cleared area sized              
              clearX = filledX;
              clearY = ((height-2) - (pixelGap*2)) - filledY;
              
              
              
              //Clamping
              if((filledY+yPos+1) >= (yPos+height-2))
              {
                filledY = (yPos+height-2);
              }  
              break;
              
      case(2): // Left <- Right

              ratio = floor(((value - min) / (max - min)) * ((width-2) - (pixelGap*2)));
        
              startX = xPos+1 + (width-2) - pixelGap - (unsigned char) ratio;
              startY = yPos+1 + pixelGap;
              
              //filled area sized
              filledX = (unsigned char) ratio;
              filledY = ((height-2) - (pixelGap*2));              
              
              //Clear
              startClearX = xPos+1+pixelGap;
              startClearY = startY; 
              
              //Cleared area sized              
              clearX = ((width-2) - (pixelGap*2)) - filledX;
              clearY = filledY;
                      
              break;
              
      case(3): // Bottom -> Top

              ratio = floor(((value - min) / (max - min)) * ((height-2) - (pixelGap*2)));
              
              startX = xPos+1 + pixelGap;
              startY = yPos+1 + (height-2) - pixelGap - (unsigned char) ratio;
              
              //filled area sized
              filledX = ((width-2) - (pixelGap*2));
              filledY = (unsigned char) ratio;

              //Clear
              startClearX = startX;
              startClearY = yPos+1+pixelGap; 
              
              //Cleared area sized              
              clearX = filledX;
              clearY = ((height-2) - (pixelGap*2)) - ((unsigned char) ratio);
              
              
              
              //Clamping
              if((filledY+yPos+1) >= (yPos+height-2))
              {
                //filledY = (yPos+height-2);
              }  
              break;        
              break;              
    }
  }
  else
///////////////////////////////////////////////////////////////////[Value is drawn from graph edges]       
  {
    // Swichfor graph directions //
    switch(graphDirection)
    {
      case(0): // Left -> Right // Only X matters
              
              ratio = floor(((value - min) / (max - min)) * ((width-2) - (pixelGap*2)));
              
              startX = xPos + 1 + pixelGap;
              startY = yPos + 1 + pixelGap;
              
              //filled area sized
              filledX = (unsigned char) ratio;
              filledY = (height-2) - (pixelGap*2);              
              
              //Clear
              startClearX = startX + filledX;
              startClearY = startY; 
              
              //Cleared area sized              
              clearX = ((width-2) - (pixelGap*2)) - filledX;
              clearY = filledY;
              
              //Clamping
              if((filledX+xPos+1) >= (xPos+width-1))
              {
                filledX = (xPos+width-2);
              }

              break;
              
      case(1): // Top -> Bottom

              ratio = floor(((value - min) / (max - min)) * ((height-2) - (pixelGap*2)));
              
              startX = xPos + 1 + pixelGap;
              startY = yPos + 1 + pixelGap;
              
              //filled area sized
              filledX = ((width-2) - (pixelGap*2));
              filledY = (unsigned char) ratio;

              //Clear
              startClearX = startX;
              startClearY = startY + filledY; 
              
              //Cleared area sized              
              clearX = filledX;
              clearY = ((height-2) - (pixelGap*2)) - filledY;
              
              
              
              //Clamping
              if((filledY+yPos+1) >= (yPos+height-2))
              {
                filledY = (yPos+height-2);
              }  
              break;
              
      case(2): // Left <- Right

              ratio = floor(((value - min) / (max - min)) * ((width-2) - (pixelGap*2)));
        
              startX = xPos+1 + (width-2) - pixelGap - (unsigned char) ratio;
              startY = yPos+1 + pixelGap;
              
              //filled area sized
              filledX = (unsigned char) ratio;
              filledY = ((height-2) - (pixelGap*2));              
              
              //Clear
              startClearX = xPos+1+pixelGap;
              startClearY = startY; 
              
              //Cleared area sized              
              clearX = ((width-2) - (pixelGap*2)) - filledX;
              clearY = filledY;
                      
              break;
              
      case(3): // Bottom -> Top

              ratio = floor(((value - min) / (max - min)) * ((height-2) - (pixelGap*2)));
              
              startX = xPos+1 + pixelGap;
              startY = yPos+1 + (height-2) - pixelGap - (unsigned char) ratio;
              
              //filled area sized
              filledX = ((width-2) - (pixelGap*2));
              filledY = (unsigned char) ratio;

              //Clear
              startClearX = startX;
              startClearY = yPos+1+pixelGap; 
              
              //Cleared area sized              
              clearX = filledX;
              clearY = ((height-2) - (pixelGap*2)) - ((unsigned char) ratio);
              
              
              
              //Clamping
              if((filledY+yPos+1) >= (yPos+height-2))
              {
                //filledY = (yPos+height-2);
              }  
              break;        
              break;              
    }
    
      //Check if the new floored ratio is bigger or smaller than 1.
     // That would mean that more than 1 pixel have been drawn or cleared
              
     if(ratio >= floor(oldRatio)) // Ratio was bigger than 1 pixel
    {
     updateFill  = true;
     wantedState = 1; 
    }
              
    if(ratio <= floor(oldRatio)) // Ratio smaller than 1 pixel
    {
      updateFill  = true;
      wantedState = 0; 
    }
    
  }
}
//================================================================================================//    
//================================================================================================//
// Draw Filling
//================================================================================================//  
//================================================================================================//  
if(updateFill == 1)
{
  switch(graphFilling)
  {
    case(0): // Transparent
             BRS_LCD_Draw_Shape_RectF(startX, startY, filledX, filledY, 0);      
      break;
      
    case(1): // Standard Filled
             BRS_LCD_Draw_Shape_RectF(startClearX, startClearY, clearX, clearY, 0); //Clear bottom
             BRS_LCD_Draw_Shape_RectF(startX, startY, filledX, filledY, 1); //Draw top                    
      break;

    case(2): // Segmented Bars
             BRS_LCD_Draw_Shape_RectF(startClearX, startClearY, clearX, clearY, 0); //Clear bottom      
      
            switch(graphDirection)
            {
              case(0): // Left -> Right //
              case(2): // Right -> Left //
                      
                      if(startX % 2 == 1) //Even
                      {
                        for(unsigned char i=startX; i<filledX+startX; i+=2)
                        {
                          BRS_LCD_Draw_Shape_RectF(i, startY, 1, filledY, 1);
                        }                        
                      }
                      else
                      {
                        for(unsigned char i=startX+1; i<filledX+startX+1; i+=2)
                        {
                          BRS_LCD_Draw_Shape_RectF(i, startY, 1, filledY, 1);
                        }                        
                      }
               break;
               
              case(3): // Top -> Bottom //
              case(1): // Bottom -> Top //
                      if(startY % 2 == 1) //Even
                      {                
                        for(unsigned char i=startY; i<filledY+startY; i+=2)
                        {
                          BRS_LCD_Draw_Shape_RectF(startX, i, filledX, 1, 1);
                        }
                      }
                      else
                      {
                        for(unsigned char i=startY+1; i<filledY+startY+1; i+=2)
                        {
                          BRS_LCD_Draw_Shape_RectF(startX, i, filledX, 1, 1);
                        }                        
                      }
               break;               
            }
      break;

    case(3): // Checker Pattern
             BRS_LCD_Draw_Shape_RectF(startClearX, startClearY, clearX, clearY, 0); //Clear bottom         
             for(unsigned char x=startX; x<filledX+startX; x++)
             {
               for(unsigned char y=startY; y<filledY+startY; y++)
               {
                 BRS_LCD_Draw_Pixel(x,y,(y%2==0)^(x%2==0));
               }
             }
      break;

    case(4): // Diagonal Lines
      
      break;
      
    case(5): // EDGE ONLY
      //So there is no fillings basically
      break;            
  }
}

////================================================================================================//    
////================================================================================================//
//// Blink Edges
////================================================================================================//  
////================================================================================================//
//  if(blinkEdges and oldAnimationCounter<animationCounter/2)
//  {
//     switch(graphDirection)
//     {
//      case(0): // Left -> Right //
//      case(2): // Right -> Left //
//              BRS_LCD_Draw_Shape_RectF(startX+filledX, startY, 1, filledY, 1);
//      break;
//               
//      case(3): // Top -> Bottom //
//      case(1): // Bottom -> Top //
//              BRS_LCD_Draw_Shape_RectF(startX, startY+filledY, filledX, 1, 1);
//      break;               
//     }    
//  }
//  if(blinkEdges and not oldAnimationCounter<animationCounter/2)
//  {
//     switch(graphDirection)
//     {
//      case(0): // Left -> Right //
//      case(2): // Right -> Left //
//              BRS_LCD_Draw_Shape_RectF(startX+filledX, startY, 1, filledY, 0);
//      break;
//               
//      case(3): // Top -> Bottom //
//      case(1): // Bottom -> Top //
//              BRS_LCD_Draw_Shape_RectF(startX, startY+filledY, filledX, 1, 0);
//      break;               
//     }  
//  }
//================================================================================================//    
//================================================================================================//
// Value Updating
//================================================================================================//  
//================================================================================================//
  oldPosX       = xPos;
  oldPosY       = yPos;
  oldWidth      = width;
  oldHeight     = height;
  oldBorders    = graphBorders;
  oldDirection  = graphDirection;
  oldFilling    = graphFilling;
  oldMax        = max;
  oldMin        = min;
  oldValue      = value;
  oldBlinkEdges = blinkEdges;
  oldBlinkingThreshold = blinkingThreshold;
  oldRatio      = ratio;
  

}