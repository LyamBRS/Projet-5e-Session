//******************************************************************************
//    Nom du fichier : GLcd.c
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 16-03-2006 
//    Date de modification pour le STM32F4 : 23-12-2015
//    Fonction de controle d'un ecran graphique de type KS0108.
// 
//******************************************************************************
//Include
#include "piloteLcd.h"
#include "Font.h"

//_BRS_[Global LCD Table]#[08/04/2022]#[Shawn Couture]中中中中中中中中中中中中中中中中中中中中中中中|| [BRS_ADDED]

//BRS// Initialises a table that represents the current data on the LCD. (1024 bytes)
unsigned char BRS_CurrentlyDrawnOnLCD[128][8];
//丁RS中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中||






//**********************************ucInputGLcd*********************************
//    Nom de la fonction : ucInputGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 02-04-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Lecture d'une donn? sur les registres de l'?ran LCD Graph.
//                  KS0108.  La donn? est pr?ente ?une adresse sp?ifi? en 
//                  param?re d'entr?. 
//
//    Appel : ucData ucInputGLcd(0x04);
//            Permet de lire la donn? sur le dispositif ?l'adresse 0x04. 
//           
//    Fonctions appel?s : ucReadIO.
//    Param?res d'entr? : ucAdresse.
//    Param?res de sortie : unsigned char.               
//    Variables utilis?s : ucDonnee, ucTest.            
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
uint8_t ucInputGLcd(uint8_t ucAdresse)
{
  uint8_t ucDonnee, ucTest;      
  
  ucTest = ucReadIO (CS0, 1, ADRBUSYFLAG);
  while ((ucTest & 0x80) == 0x80)                      //Attente du BUSY FLAG.
    ucTest = ucReadIO (CS0, 1, ADRBUSYFLAG);        
  
  ucDonnee = ucReadIO (CS0, 1, (ucAdresse | 0x04));    //Lire la donnee.  
  return(ucDonnee);                                    //Retourner la donnee.  
} 
//fin routine ucInputGLcd-------------------------------------------------------


//*********************************vOutputGLcd**********************************
//    Nom de la fonction : vOutputGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 02-04-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Ecriture d'une donn? sur les registres de l'?ran KS0108.
//                  La donn? est ?rite ?une adresse sp?ifi? en param?re 
//                  d'entr?. 
//
//    Appel : vOutputGLcd(0x04, 0x55);
//            Permet d'?rire la donn? 0x55 sur le dispositif ?l'adresse 0x04. 
//     
//    Fonctions appel?s : ucReadIO, vWriteIO.
//    Param?res d'entr? : ucAdresse, ucDonnee.
//    Param?res de sortie : Aucun.               
//    Variables utilis?s :  ucTest.         
//    Equate : Aucun	
//    #Define : Aucun   
//                                    
//******************************************************************************   
void vOutputGLcd(uint8_t ucAdresse, uint8_t ucDonnee)
{   
  uint8_t ucTest; 
  
  ucTest = ucReadIO (CS0, 1, ADRBUSYFLAG);  
  while ((ucTest & 0x80) == 0x80)                    //Attente du BUSY FLAG.
    ucTest = ucReadIO (CS0, 1, ADRBUSYFLAG);
  
  vWriteIO(ucDonnee, CS0, 1, (ucAdresse & 0x0B));    //Ecriture de la donnee.
}    
//fin routine vOutputGLcd-------------------------------------------------------


//***********************************vInitGLcd**********************************
//    Nom de la fonction : vInitGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Initialisation de l'ecran graphique KS0108.
//
//    Appel : vInitGLcd();
//            Initialise l'?ran selon des param?res ?ablis. 
//           
//    Fonctions appel?s : vOutputGLcd.
//    Param?res d'entr? : Aucun.
//    Param?res de sortie : Aucun.                
//    Variables utilis?s : Aucun. 
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vInitGLcd(void)
{
  //Cote gauche 
  vOutputGLcd(ADRINSTRLEFTW, 0x3E);  //Display OFF. 
  vOutputGLcd(ADRINSTRLEFTW, 0xC0);  //Start line.     
  vOutputGLcd(ADRINSTRLEFTW, 0xB8);  //Page a 0.
  vOutputGLcd(ADRINSTRLEFTW, 0x40);  //Adresse Y a 0.      
  vOutputGLcd(ADRINSTRLEFTW, 0x3F);  //Display ON.
  //Cote droit  
  vOutputGLcd(ADRINSTRRIGHTW, 0x3E);  //Display OFF.
  vOutputGLcd(ADRINSTRRIGHTW, 0xC0);  //Start line.     
  vOutputGLcd(ADRINSTRRIGHTW, 0xB8);  //Page a 0.
  vOutputGLcd(ADRINSTRRIGHTW, 0x40);  //Adresse Y a 0.      
  vOutputGLcd(ADRINSTRRIGHTW, 0x3F);  //Display ON.
  
  //_BRS_[Reset of LCD table]#[08/04/2022]#[Shawn Couture]??????????????????????|| [BRS_ADDED]  
  for(unsigned char X=0; X<128; X++)
  {
    for(unsigned char Y=0; Y<8; Y++)
    {
      BRS_CurrentlyDrawnOnLCD[X][Y] = 0x00; 
    }
  }
  
  //?RS???????????????????????????????????????????????||  
  
}
//fin routine vInitGLcd---------------------------------------------------------


//**********************************vClearGLcd**********************************
//    Nom de la fonction : vClearGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Effacer l'ecran graphique KS0108.
//
//    Appel : vClearGLcd(0x00); 
//            Place tous les pixel ?0, donc efface l'?ran.
//
//    Fonctions appel?s : vOutputGLcd()
//    Param?res d'entr? : ucData
//    Param?res de sortie : Aucun                
//    Variables utilis?s : i et j
//    Equate : Aucun
//    #Define : ADRINSTRRIGHTW, ADRINSTRLEFTW, ADRDATALEFTW, ADRDATARIGHTW
//                                    
//******************************************************************************
void vClearGLcd(uint8_t ucData)
{
  int i, j;
  //_BRS_[Clearing LCD Table]#[08/04/2022]#[Shawn Couture]??????????????????????|| [BRS_ADDED]
  //Clamp Value
  if(ucData > 0x00)
  {
    ucData = 0xFF;
  }
  else
  {
    ucData = 0x00;
  }
  
  for(unsigned char X=0; X<128; X++)
  {
    for(unsigned char Y=0; Y<8; Y++)
    {
      BRS_CurrentlyDrawnOnLCD[X][Y] = ucData; 
    }
  }
  //?RS???????????????????????????????????????????????||  
  
  for (j=0; j<8; j++)
  {              
    vOutputGLcd(ADRINSTRRIGHTW, (0xB8+j));  //Page                                 
    vOutputGLcd(ADRINSTRLEFTW, (0xB8+j));   //Page    
    for (i=0; i<64; i++)
    {
      vOutputGLcd(ADRDATALEFTW, ucData); 
    }     
    for (i=0; i<64; i++)
    {
      vOutputGLcd(ADRDATARIGHTW, ucData); 
    }     
  }     
}   
//fin routine vClearGLcd--------------------------------------------------------


//********************************vPutPixelGLcd*********************************
//    Nom de la fonction : vPutPixelGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Placer un pixel en x et y sur l'ecran graphique KS0108. 
//                  X = 0 a 127 et Y = 0 a 63.  Pour placer le pixel, on doit
//                  lire la position 8 bits, ?l'?ran, et masquer le bit ?
//                  afficher.  La lecture doit ?re faite deux fois (directive
//                  du manufacturier) et on doit replacer le curseur apr? 
//                  chaque lecture.
//           
//    Appel : vPutPixelGLcd(10,10); 
//            Active un pixel ?la position 10, 10.
//
//    Fonctions appel?s : vOutputGLcd()ucInputGLcd()
//    Param?res d'entr? : ucX et ucY
//    Param?res de sortie : Aucun             
//    Variables utilis?s : ucAdresse, ucData, ucDataY, ucDataOld
//    Equate : Aucun	
//    #Define : ADRINSTRRIGHTW, ADRINSTRLEFTW
//                                    
//******************************************************************************
void vPutPixelGLcd(uint8_t ucX, uint8_t ucY)
{
//_BRS_[Header name]#[08/04/2022]#[Shawn Couture]中中中中中中中中中中中中中中中中中中中中中中中中中弋| [BRS_ADDED]
  unsigned char tableData = 0;
  unsigned char KeptX = ucX;
  //What char is currently at those coordinates
  tableData = BRS_CurrentlyDrawnOnLCD[ucX][ucY/8];
  
  //If the LCD saved data is the same as the LCD saved data or coordinate, then skip.
  if(tableData == (tableData|(0x01 << (ucY % 8))))
  {
    // TABLE WAS THE SAME, SKIP THIS ENTIRELY 
  }
  else
  {
//丁RS中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中||  
  
    uint8_t ucData, ucDataY, ucDataOld; 
    uint8_t ucAdresse;
    //Choix du cote de l'ecran    
    if (ucX >= 64) 
    { 
      ucAdresse = ADRINSTRRIGHTW;
      ucX = ucX - 64;
    }  
    else
      ucAdresse = ADRINSTRLEFTW;
    
    //Position de l'adresse (Set Address).
    ucData = 0x40 | ucX; 
    ucDataY = ucData; 
    vOutputGLcd((ucAdresse & 0x03), ucDataY);
    
    //Position de la page (Set Page).
    ucData = 0xB8 | ucY/8;
    vOutputGLcd((ucAdresse & 0x03), ucData); 
    
    //Lecture de l'octet en memoire a deux reprises.
    ucDataOld = ucInputGLcd(ucAdresse | 0x0C);
    
    //Repositionner le curseur.  
    vOutputGLcd((ucAdresse & 0x03), ucDataY);
    vOutputGLcd((ucAdresse & 0x03), ucData); 
    ucDataOld = ucInputGLcd(ucAdresse | 0x0C);

      //Ecriture du pixel.
      
      //Repositionner le curseur.
      vOutputGLcd((ucAdresse & 0x03), ucDataY);
      vOutputGLcd((ucAdresse & 0x03), ucData);      
      
      ucData = 0x01;
      ucData = ucDataOld | (ucData << (ucY % 8));
      BRS_CurrentlyDrawnOnLCD[KeptX][ucY/8] = ucData;
      vOutputGLcd((ucAdresse | 0x08), ucData);    
  }
  
}      
//fin routine vPutPixelGLcd-----------------------------------------------------


//********************************vClearPixelGLcd*******************************
//    Nom de la fonction : vClearPixelGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Effacer un pixel en x et y sur l'ecran graphique KS0108. 
//                  X = 0 a 127 et Y = 0 a 63.  Pour effacer le pixel, on doit
//                  lire la position 8 bits, ?l'?ran, et masquer le bit ?
//                  afficher.  La lecture doit ?re faite deux fois (directive
//                  du manufacturier) et on doit replacer le curseur apr? 
//                  chaque lecture.
//
//    Appel : vClearPixelGLcd(10,10); 
//            D?active un pixel ?la position 10, 10.
//           
//    Fonctions appel?s : vOutputGLcd(), ucInputGLcd().
//    Param?res d'entr? : ucX et ucY.
//    Param?res de sortie : Aucun.                
//    Variables utilis?s : ucAdresse, ucData, ucDataY, ucDataOld. 
//    Equate : Aucun	
//    #Define : ADRINSTRRIGHTW, ADRINSTRLEFTW
//                                
//******************************************************************************
void vClearPixelGLcd(uint8_t ucX, uint8_t ucY)
{
  uint8_t ucAdresse;  
  uint8_t ucData, ucDataY, ucDataOld;
  
//_BRS_[Declaration]#[08/04/2022]#[Shawn Couture]戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌帆| [BRS_MODIFIED]
  unsigned char tableData = 0;
  unsigned char KeptX = ucX;
  //What char is currently at those coordinates
  tableData = BRS_CurrentlyDrawnOnLCD[ucX][ucY/8];

  ucData = 0x01;
  ucData = ucData << (ucY % 8);
  ucData = ucData ^ 0xFF;
  ucData = ucData & tableData;
  //If the LCD saved data is the same as the LCD saved data or coordinate, then skip.
  if(tableData != ucData)
  {
//冰RS戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌||   
       
    //Choix du cote de l'ecran    
    if (ucX >= 64) 
    { 
      ucAdresse = ADRDATARIGHTW;
      ucX = ucX - 64;
    }  
    else
      ucAdresse = ADRDATALEFTW;  
    
    //Position de l'adresse Y.
    ucData = 0x40 | ucX; 
    ucDataY = ucData; 
    vOutputGLcd((ucAdresse & 0x03), ucDataY);
    
    //Position de la page.
    ucData = 0xB8 | ucY/8;
    vOutputGLcd((ucAdresse & 0x03), ucData); 
    
    //Lecture de l'octet en memoire a deux reprises.  
    ucDataOld = ucInputGLcd(ucAdresse | 0x0C); 
    
    //Repositionner le curseur.  
    vOutputGLcd((ucAdresse & 0x03), ucDataY);
    vOutputGLcd((ucAdresse & 0x03), ucData); 
    ucDataOld = ucInputGLcd(ucAdresse | 0x0C); 
    
//_BRS_[Read Pixel]#[08/04/2022]#[Shawn Couture]戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌|| [BRS_MODIFIED]
      //Data was different, read pixel
      
      //Repositionner le curseur.  
      vOutputGLcd((ucAdresse & 0x03), ucDataY);
      vOutputGLcd((ucAdresse & 0x03), ucData);
      
      //Ecriture du pixel. 
      ucData = 0x01;
      ucData = ucData << (ucY % 8);
      ucData = ucData ^ 0xFF; 
      ucData = ucData & ucDataOld;  
      vOutputGLcd((ucAdresse | 0x08), ucData);
      BRS_CurrentlyDrawnOnLCD[KeptX][ucY/8] = ucData;      
//冰RS戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌|| 
  }
}  
//fin routine vClearPixelGLcd---------------------------------------------------


//*******************************vDrawLineGLcd**********************************
//    Nom de la fonction : vDrawLineGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 20-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Dessiner une ligne de la coordonnee (X1Y1) avec une  
//                  direction (H ou V) et une longueur.
//
//    Appel : vDrawLineGLcd(0, 0, 20, 'H');
//            Trace une ligne horizontale de 20 pixel dont l'origine est 0, 0.
//           
//    Fonctions appel?s : vPutPixelGLcd()
//    Param?res d'entr? : ucX, ucY, ucLong, ucDir
//    Param?res de sortie : Aucun
//    Variables utilis?s : i
//    Equate : Aucun	
//    #Define : ADRINSTRRIGHTW, ADRINSTRLEFTW
//                                    
//******************************************************************************
void vDrawLineGLcd(uint8_t ucX, uint8_t ucY, uint8_t ucLong, uint8_t ucDir)
{   
  int i;
  if (ucDir == 'H')
  {
    for (i = 0; i <= ucLong; i ++)
    {
      vPutPixelGLcd(ucX+i, ucY); 
    }    
  }
  if (ucDir == 'V')
  {
    for (i = 0; i <= ucLong; i ++)
    {
      vPutPixelGLcd(ucX, ucY+i); 
    }
  }                                 
}
//fin routine vDrawLineGLcd----------------------------------------------------- 


//******************************vDrawRectangleGLcd******************************
//    Nom de la fonction : vDrawRectangleGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 18-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Dessiner un rectangle aux coordonnees (X1Y1, X2Y2).
//
//    Appel : vDrawRectangleGLcd(1,1,20,20);
//            Tra?ge d'un rectangle dont la diagonale est positionn?
//            aux coordonn?s X1=1, Y1=1 et X2=20, Y2=20.
//
//    Fonctions appel?s : vPutPixelGLcd()
//    Param?res d'entr? : ucX1, ucY1, ucX2 et ucY2
//    Param?res de sortie : Aucun     
//    Variables utilis?s : ucLong et ucHaut, i
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vDrawRectangleGLcd(uint8_t ucX1, uint8_t ucY1, uint8_t ucX2, uint8_t ucY2)
{
  uint8_t ucLong, ucHaut;
  uint8_t i;
  
  ucLong = ucX2 - ucX1;
  ucHaut = ucY2 - ucY1; 
  //Tracer les lignes horizontales.   
  for (i = 0; i <= ucLong; i ++)
  {
    vPutPixelGLcd(ucX1+i, ucY1); 
    vPutPixelGLcd(ucX1+i, ucY2); 
  }                             
  //Tracer les lignes verticales.   
  for (i = 0; i <= ucHaut; i ++)
  {
    vPutPixelGLcd(ucX1, ucY1+i); 
    vPutPixelGLcd(ucX2, ucY1+i); 
  }  
}
//fin routine vDrawRectangleGLcd------------------------------------------------


//********************************vDrawCircleGLcd*******************************
//    Nom de la fonction : vDrawCircleGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 18-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Dessiner un cercle de rayon ucRayon a la coordonnee ucX et
//                  ucY.
//    
//    Appel : vDrawCircleGLcd(20, 50, 10);
//            Tra?ge d'un cercle de 10 de rayon dont le centre est situ?
//            aux coordonn?s X=20, Y=50.
//
//    Fonctions appel?s : vPutPixelGLcd()
//    Param?res d'entr? : ucX, ucY et ucRayon
//    Param?res de sortie : Aucun    
//    Variables utilis?s : iSwitch, iX, iY, ucD
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vDrawCircleGLcd(uint8_t ucX, uint8_t ucY, uint8_t ucRayon)
{
  int iSwitch=0, iX=0, iY=0;
  unsigned char ucD;
  
  ucD = ucY - ucX;
  iY = ucRayon;
  iSwitch = 3 - (2 * ucRayon);
  while (iX <= iY)
  {
    vPutPixelGLcd((ucX + iX),(ucY + iY));
    vPutPixelGLcd((ucX + iX),(ucY - iY));
    vPutPixelGLcd((ucX - iX),(ucY + iY));
    vPutPixelGLcd((ucX - iX),(ucY - iY));    
    vPutPixelGLcd((ucY + iY - ucD),(ucY + iX));     
    vPutPixelGLcd((ucY + iY - ucD),(ucY - iX));     
    vPutPixelGLcd((ucY - iY - ucD),(ucY + iX));     
    vPutPixelGLcd((ucY - iY - ucD),(ucY - iX));  
    
    if (iSwitch < 0)
    {
      iSwitch += (4 * iX + 6);
    }                          
    else
    {
      iSwitch += (4 * (iX - iY) + 10);
      iY --;
    }        
    iX++; 
  }
}
//fin routine vDrawCircleGLcd---------------------------------------------------


//**********************************vPutCharGLcd********************************
//    Nom de la fonction : vPutCharGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 17-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Ecriture d'un caractere a une position Ligne Colonne sur 
//                  l'ecran GLCD. Il est possible d'utiliser les colonnes 0 a 15 
//                  et les lignes 0 a 7 pour le FONT 7, les colonnes 0 a 19 et 
//                  les lignes 0 a 7 pour le FONT 5 et les colonnes 0 a 31 et  
//                  les lignes 0 a 7 pour le FONT 3.
//           
//    Exemple d'appel : vPutCharGLcd('A', 1, 0, 3);
//                      ?rit le caract?e A de grosseur de font 3 ?la ligne 1
//                      et la colonne 0.
//
//    Fonctions appel?s : vOutputGLcd()
//    Param?res d'entr? : ucChar, ucLigne et ucColonne
//    Param?res de sortie : Aucun
//    Variables utilis?s : uiAdresse, i, iChar, ucX et ucData
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vPutCharGLcd(uint8_t ucChar, uint8_t ucLigne, uint8_t ucColonne, uint8_t ucFont)
{
//_BRS_[keep X value]#[08/04/2022]#[Shawn Couture]中中中中中中中中中中中中中中中中中中中中中中中中中|| [BRS_ADDED]
  unsigned char X = 0;
//丁RS中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中|| 
  uint8_t ucAdresse; 
  int8_t i, iChar; 
  uint8_t ucX, ucData;  
  iChar = ucChar - 0x20;                //Choix de la ligne dans le tableau.  
  
  if (ucFont == 3)                      //Si on utilise le font de 3 pixels.
  {
    ucX = (ucColonne * 4);              //Calcul de la position en X.
  }
  
  if (ucFont == 5)                      //Si on utilise le font de 5 pixels.
  { 
    ucX = ((ucColonne * 6) + 4);        //Calcul de la position en X.
  }
  
  if (ucFont == 7)                      //Si on utilise le font de 3 pixels.
  {
    ucX = (ucColonne * 8);              //Calcul de la position en X.
  }  
//_BRS_[keep X value]#[08/04/2022]#[Shawn Couture]中中中中中中中中中中中中中中中中中中中中中中中中中|| [BRS_ADDED]
  X = ucX;
//丁RS中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中||
  
  //Choix du cote de l'ecran    
  if (ucX >= 64) 
  { 
    ucAdresse = ADRDATARIGHTW;
    ucX = ucX - 64;
  }  
  else ucAdresse = ADRDATALEFTW;     
  
  //Position de l'adresse Y.
  ucData = 0x40 | ucX;  
  
  //LCDDI = 0;    
  vOutputGLcd((ucAdresse & 0x07), ucData);
  
  //Position de la page. 
  ucData = 0xB8 | ucLigne;
  vOutputGLcd((ucAdresse & 0x07), ucData); 
  
  //LCDDI = 1;     
  if (ucFont == 3)                      //Si on utilise le font de 3 pixels.
  {
    for (i = 0; i <= 2; i++)
    {
//_BRS_[FONT 3 COMPARAISON]#[08/04/2022]#[Shawn Couture]戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌|| [BRS_MODIFIED]   
      //if(ucFontSystem3x6[iChar][i] != BRS_CurrentlyDrawnOnLCD[X+i][ucLigne])
      //{
        ucData = ucFontSystem3x6[iChar][i];       // PUT 8 BITS INTO 
        vOutputGLcd((ucAdresse | 0x08), ucData);
        BRS_CurrentlyDrawnOnLCD[X+i][ucLigne] = ucData;         
      //}      
//冰RS戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌||       
    }
  }
  if (ucFont == 5)                      //Si on utilise le font de 5 pixels.
  { 
    for (i = 0; i < 5; i++)
    {
//_BRS_[FONT 5 COMPARAISON]#[11/04/2022]#[Shawn Couture]戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌|| [BRS_MODIFIED]        
      //if(ucFontSystem5x8[iChar][i] != BRS_CurrentlyDrawnOnLCD[X+i][ucLigne])
      //{
        ucData = ucFontSystem5x8[iChar][i];       // PUT 8 BITS INTO 
        vOutputGLcd((ucAdresse | 0x08), ucData);
        BRS_CurrentlyDrawnOnLCD[X+i][ucLigne] = ucData;         
      //}
//冰RS戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌||      
    } 
  }
  if (ucFont == 7)                      //Si on utilise le font de 7 pixels.
  {
    for (i = 0; i <= 6; i++)
    {
//_BRS_[FONT 5 COMPARAISON]#[11/04/2022]#[Shawn Couture]戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌|| [BRS_MODIFIED]            
      //if(ucFontSystem7x8[iChar][i] != BRS_CurrentlyDrawnOnLCD[X+i][ucLigne])
      //{
        ucData = ucFontSystem7x8[iChar][i];       // PUT 8 BITS INTO 
        vOutputGLcd((ucAdresse | 0x08), ucData);
        BRS_CurrentlyDrawnOnLCD[X+i][ucLigne] = ucData;         
      //}
//冰RS戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌||      
    }
  }
}
//fin routine vPutCharGLcd------------------------------------------------------

//**********************************vPutCharGLcdINV*****************************
//    Nom de la fonction : vPutCharGLcdINV
//    Auteur : Alain Champagne
//    Modifications: Shawn Couture
//    Date de cr?tion : 17-03-2006
//    Date de modification : 11-05-2022   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Ecriture d'un caractere a une position Ligne Colonne sur 
//                  l'ecran GLCD. Il est possible d'utiliser les colonnes 0 a 15 
//                  et les lignes 0 a 7 pour le FONT 7, les colonnes 0 a 19 et 
//                  les lignes 0 a 7 pour le FONT 5 et les colonnes 0 a 31 et  
//                  les lignes 0 a 7 pour le FONT 3.
//           
//    Exemple d'appel : vPutCharGLcd('A', 1, 0, 3);
//                      ?rit le caract?e A de grosseur de font 3 ?la ligne 1
//                      et la colonne 0.
//
//    Fonctions appel?s : vOutputGLcd()
//    Param?res d'entr? : ucChar, ucLigne et ucColonne
//    Param?res de sortie : Aucun
//    Variables utilis?s : uiAdresse, i, iChar, ucX et ucData
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vPutCharGLcdINV(uint8_t ucChar, uint8_t ucLigne, uint8_t ucColonne, uint8_t ucFont)
{
//_BRS_[keep X value]#[08/04/2022]#[Shawn Couture]中中中中中中中中中中中中中中中中中中中中中中中中中|| [BRS_ADDED]
  unsigned char X = 0;
//丁RS中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中|| 
  uint8_t ucAdresse; 
  int8_t i, iChar; 
  uint8_t ucX, ucData;  
  iChar = ucChar - 0x20;                //Choix de la ligne dans le tableau.  
  
  if (ucFont == 3)                      //Si on utilise le font de 3 pixels.
  {
    ucX = (ucColonne * 4);              //Calcul de la position en X.
  }
  
  if (ucFont == 5)                      //Si on utilise le font de 5 pixels.
  { 
    ucX = ((ucColonne * 6) + 4);        //Calcul de la position en X.
  }
  
  if (ucFont == 7)                      //Si on utilise le font de 3 pixels.
  {
    ucX = (ucColonne * 8);              //Calcul de la position en X.
  }  
//_BRS_[keep X value]#[08/04/2022]#[Shawn Couture]中中中中中中中中中中中中中中中中中中中中中中中中中|| [BRS_ADDED]
  X = ucX;
//丁RS中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中||
  
  //Choix du cote de l'ecran    
  if (ucX >= 64) 
  { 
    ucAdresse = ADRDATARIGHTW;
    ucX = ucX - 64;
  }  
  else ucAdresse = ADRDATALEFTW;     
  
  //Position de l'adresse Y.
  ucData = 0x40 | ucX;  
  
  //LCDDI = 0;    
  vOutputGLcd((ucAdresse & 0x07), ucData);
  
  //Position de la page. 
  ucData = 0xB8 | ucLigne;
  vOutputGLcd((ucAdresse & 0x07), ucData); 
  
  //LCDDI = 1;     
  if (ucFont == 3)                      //Si on utilise le font de 3 pixels.
  {
    for (i = 0; i <= 2; i++)
    {
//_BRS_[FONT 3 COMPARAISON]#[08/04/2022]#[Shawn Couture]戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌|| [BRS_MODIFIED]   
      //if(ucFontSystem3x6[iChar][i] != BRS_CurrentlyDrawnOnLCD[X+i][ucLigne])
      //{
        ucData = ucFontSystem3x6[iChar][i]^0xFF;       // PUT 8 BITS INTO 
        vOutputGLcd((ucAdresse | 0x08), ucData);
        BRS_CurrentlyDrawnOnLCD[X+i][ucLigne] = ucData;         
      //}      
//冰RS戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌||       
    }
  }
  if (ucFont == 5)                      //Si on utilise le font de 5 pixels.
  { 
    for (i = 0; i < 5; i++)
    {
//_BRS_[FONT 5 COMPARAISON]#[11/04/2022]#[Shawn Couture]戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌|| [BRS_MODIFIED]        
      //if(ucFontSystem5x8[iChar][i] != BRS_CurrentlyDrawnOnLCD[X+i][ucLigne])
      //{
        ucData = ucFontSystem5x8[iChar][i]^0xFF;       // PUT 8 BITS INTO 
        vOutputGLcd((ucAdresse | 0x08), ucData);
        BRS_CurrentlyDrawnOnLCD[X+i][ucLigne] = ucData;         
      //}
//冰RS戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌||      
    } 
  }
  if (ucFont == 7)                      //Si on utilise le font de 7 pixels.
  {
    for (i = 0; i <= 6; i++)
    {
//_BRS_[FONT 5 COMPARAISON]#[11/04/2022]#[Shawn Couture]戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌|| [BRS_MODIFIED]            
      //if(ucFontSystem7x8[iChar][i] != BRS_CurrentlyDrawnOnLCD[X+i][ucLigne])
      //{
        ucData = ucFontSystem7x8[iChar][i]^0xFF;       // PUT 8 BITS INTO 
        vOutputGLcd((ucAdresse | 0x08), ucData);
        BRS_CurrentlyDrawnOnLCD[X+i][ucLigne] = ucData;         
      //}
//冰RS戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌戌||      
    }
  }
}
//fin routine vPutCharGLcd------------------------------------------------------

//*********************************vPutStringGLcd*******************************
//    Nom de la fonction : vPutStringGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 17-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : ?riture d'un ligne de caract?es a une position Ligne sur 
//                 l'?ran GLCD. 
//                 Il est possible d'utiliser les lignes 0 a 7 et
//                 les FONT 3 ou 5.  
//                 32 caract?es de font 3, 
//                 20 caract?es de font 5
//                 16 caract?es de font 7
//           
//    Exemple d'appel : vPutStringGLcd(ucTab, 0, 3);
//                      ?rit une cha?e de caract?es de font 3 provenant d'un 
//                      tableau ucTab ?la ligne 0.
//
//    Fonctions appel?s : vPutCharGLcd()
//    Param?res d'entr? : ucChar, ucLigne et ucColonne
//    Param?res de sortie : Aucun
//    Variables utilis?s : uiAdresse, i
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vPutStringGLcd(char const ucTab[], int8_t iLigneLcd, uint8_t ucFont)
{
  int i; 
  {
    if (ucFont == 3)
    {
      for (i = 0; i <= 31; i++)
      {
        vPutCharGLcd(ucTab[i], iLigneLcd, i, 3);
      }
    }
    if (ucFont == 5)
    {
      for (i = 0; i <= 19; i++)
      {
        vPutCharGLcd(ucTab[i], iLigneLcd, i, 5);
      }
    } 
    if (ucFont == 7)
    {
      for (i = 0; i <= 15; i++)
      {
        vPutCharGLcd(ucTab[i], iLigneLcd, i, 7);
      }
    }
  }
}  
//fin routine vPutStringGLcd----------------------------------------------------

//*********************************vPutStringGLcdINV****************************
//    Nom de la fonction : vPutStringGLcd
//    Auteur : Alain Champagne
//    Modifer par: Shawn Couture
//    Date de cr?tion : 17-03-2006
//    Date de modification : 11-05-2022   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : ?riture d'un ligne de caract?es a une position Ligne sur 
//                 l'?ran GLCD. 
//                 Il est possible d'utiliser les lignes 0 a 7 et
//                 les FONT 3 ou 5.  
//                 32 caract?es de font 3, 
//                 20 caract?es de font 5
//                 16 caract?es de font 7
//           
//    Exemple d'appel : vPutStringGLcd(ucTab, 0, 3);
//                      ?rit une cha?e de caract?es de font 3 provenant d'un 
//                      tableau ucTab ?la ligne 0.
//
//    Fonctions appel?s : vPutCharGLcd()
//    Param?res d'entr? : ucChar, ucLigne et ucColonne
//    Param?res de sortie : Aucun
//    Variables utilis?s : uiAdresse, i
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vPutStringGLcdINV(char const ucTab[], int8_t iLigneLcd, uint8_t ucFont)
{
  int i; 
  {
    if (ucFont == 3)
    {
      for (i = 0; i <= 31; i++)
      {
        vPutCharGLcdINV(ucTab[i], iLigneLcd, i, 3);
      }
    }
    if (ucFont == 5)
    {
      for (i = 0; i <= 19; i++)
      {
        vPutCharGLcdINV(ucTab[i], iLigneLcd, i, 5);
      }
    } 
    if (ucFont == 7)
    {
      for (i = 0; i <= 15; i++)
      {
        vPutCharGLcdINV(ucTab[i], iLigneLcd, i, 7);
      }
    }
  }
}  
//fin routine vPutStringGLcdINV----------------------------------------------------

//**********************************vPutBMPGLcd*********************************
//    Nom de la fonction : vPutBMPGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Affiche un BMP ?l'?ran graphique KS0108.
//
//    Appel : vPutBMPGLcd(ucTab[]); 
//            Dessine un fichier BMP de 128 X 64 ?l'?ran.
//           
//    Fonctions appel?s : vOutputGLcd()
//    Param?res d'entr? : Aucun
//    Param?res de sortie : Aucun                
//    Variables utilis?s : i et j
//    Equate : Aucun	
//    #Define : ADRDATALEFTW, ADRDATARIGHTW
//                                    
//******************************************************************************
void vPutBMPGLcd(uint8_t ucTab[])
{
  int8_t i, j;  
  //  LCDDI = 0; 
  vOutputGLcd((ADRDATALEFTW & 0x07), 0x40);  //Adresse Y a 0.  
  vOutputGLcd((ADRDATARIGHTW &0x07), 0x40);  //Adresse Y a 0. 
  for (j=0; j<8; j++)
  {              
    //  LCDDI = 0;    
    vOutputGLcd((ADRDATARIGHTW & 0x07), (0xB8+j));  //Page                                 
    vOutputGLcd((ADRDATALEFTW & 0x07), (0xB8+j));   //Page     
    //  LCDDI = 1;
    
    // i = Y
    // j = X/2 (0-8)(0-8)
    for (i=0; i<64; i++) //top to bottom, left side
    {
      vOutputGLcd((ADRDATALEFTW | 0x08), ucTab[i + (j * 128)]); 
      BRS_CurrentlyDrawnOnLCD[i][j] = ucTab[i + (j * 128)]; //X = (0-63) // Y = 0-7     
    }     
    for (i=0; i<64; i++) //top to bottom, right side
    {
      vOutputGLcd((ADRDATARIGHTW | 0x08), ucTab[i + 64 + (j * 128)]);
      BRS_CurrentlyDrawnOnLCD[i+64][j] = ucTab[i + 64 + (j * 128)]; // 64-127 // 0-7
    }     
  }     
}   

//**********************************vPutBMPGLcd*********************************
//    Nom de la fonction : vPutBMPGLcd
//    Auteur : Alain Champagne                  
//    Date de cr?tion : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Affiche un BMP ?l'?ran graphique KS0108.
//
//    Appel : vPutBMPGLcd(ucTab[]); 
//            Dessine un fichier BMP de 128 X 64 ?l'?ran.
//           
//    Fonctions appel?s : vOutputGLcd()
//    Param?res d'entr? : Aucun
//    Param?res de sortie : Aucun                
//    Variables utilis?s : i et j
//    Equate : Aucun	
//    #Define : ADRDATALEFTW, ADRDATARIGHTW
//                                    
//******************************************************************************
void vPutBMPGLcdINV(uint8_t ucTab[])
{
  int8_t i, j;  
  //  LCDDI = 0; 
  vOutputGLcd((ADRDATALEFTW & 0x07), 0x40);  //Adresse Y a 0.  
  vOutputGLcd((ADRDATARIGHTW &0x07), 0x40);  //Adresse Y a 0. 
  for (j=0; j<8; j++)
  {              
    //  LCDDI = 0;    
    vOutputGLcd((ADRDATARIGHTW & 0x07), (0xB8+j));  //Page                                 
    vOutputGLcd((ADRDATALEFTW & 0x07), (0xB8+j));   //Page     
    //  LCDDI = 1;
    
    // i = Y
    // j = X/2 (0-8)(0-8)
    for (i=0; i<64; i++) //top to bottom, left side
    {
      vOutputGLcd((ADRDATALEFTW | 0x08), ucTab[i + (j * 128)]^0xFF); 
      BRS_CurrentlyDrawnOnLCD[i][j] = ucTab[i + (j * 128)]^0xFF; //X = (0-63) // Y = 0-7     
    }     
    for (i=0; i<64; i++) //top to bottom, right side
    {
      vOutputGLcd((ADRDATARIGHTW | 0x08), ucTab[i + 64 + (j * 128)]^0xFF);
      BRS_CurrentlyDrawnOnLCD[i+64][j] = ucTab[i + 64 + (j * 128)]^0xFF; // 64-127 // 0-7
    }     
  }     
}   
//fin routine vPutBMPGLcd-------------------------------------------------------