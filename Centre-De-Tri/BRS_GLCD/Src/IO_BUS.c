
//**********************************IO_BUS**************************************
// 
//    Nom du fichier : IO_BUS.c
//    Auteur : Alain Champagne                  
//    Date de cr�ation : 21-12-2015 
// 
//    Fonctions n�cessaires au contr�le des lignes de donn�es, d'adresses et de 
//    contr�le permettant de recr�er les entr�es sorties sur bus parall�le. 
//    Ces fonctions pourront �tre utilis�es dans un programme principale comme 
//    suit: 
//    
//    -vData_IN()
//     Permet de placer les lignes de donn�es en entr�e.
//
//    -vData_OUT()
//     Permet de placer les lignes de donn�es en sortie.
//
//    -uint8_t ucReadIO (uint8_t CSx, uint8_t Level, uint8_t ucAdresse)
//     Permet de faire la lecture d'un octet en IO.  On doit passer en param�tre 
//     le no du CSx (CS0 � CS4) et l'adresse sur 4 bits (0x00 � 0x0F).  
//
//    -void vWriteIO(uint8_t ucData, uint8_t CSx, uint8_t Level, uint8_t ucAdresse)
//     Permet d'�crire un octet en IO.  On passe les param�tres de donn�e, du
//     no du CSx (CS0 � CS4) et de l'adresse sur 4 bits (0x00 � 0x0F). 
//     (iColonneLcd) sp�cifiques.
//
//
//
//    -Le bus de donn�e est associ� aux lignes physiques GPIOE, D0_Pin � D7_Pin.
//    -Les CS sont associ�s aux lignes GPIOB, CS0_Pin � CS3_Pin.
//    -Les lignes d'adresses sont associ�es aux lignes GPIOD, A0_Pin � A3_Pin.
//    -Les lignes RD et WR sont associ�s � GPIOB, RD_Pin et WR_Pin.
//   
//                    
//                   
//******************************************************************************
 
 //Include
#include "IO_BUS.h"  


//********************************vData_IN**************************************
//    Nom de la fonction : vData_IN
//    Auteur : Alain Champagne		
//    Date de cr�ation : 21-12-2015
//    Description : 	Routine pour placer les lignes de donn�es en entr�e. 
//							
//    Fonctions appel�es : HAL_GPIO_Init()		
//    Param�tres d'entr�e : Aucun		
//    Param�tres de sortie : Aucun		
//    Variables utilis�es : Aucune
//    Equate : Aucun	
//    #Define : Aucun	
// 						
//******************************************************************************
void vData_IN (void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = D0_Pin|D1_Pin|D2_Pin|D3_Pin|D4_Pin|D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}
//fin routine SDA_IN------------------------------------------------------------


//********************************vData_OUT*************************************
//    Nom de la fonction : vData_OUT
//    Auteur : Alain Champagne		
//    Date de cr�ation : 21-12-2015
//    Description : 	Routine pour placer les lignes de donn�es en sortie. 
//							
//    Fonctions appel�es : HAL_GPIO_Init()		
//    Param�tres d'entr�e : Aucun		
//    Param�tres de sortie : Aucun		
//    Variables utilis�es : Aucune
//    Equate : Aucun	
//    #Define : Aucun	
// 						
//******************************************************************************
void vData_OUT (void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = D0_Pin|D1_Pin|D2_Pin|D3_Pin|D4_Pin|D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}
//fin routine SDA_OUT-----------------------------------------------------------


//*********************************ucReadIO*************************************
//    Nom de la fonction : ucReadIO
//    Auteur : Alain Champagne
//    Date de cr�ation : 21-12-2015
//    Description : Routine pour lire une donn�e d'un device avec BUS parall�le.
//                 
//    Appel : ucData = ucRead_IO(2, 0, 0x04);
//            Permet de lire une donn�e sur un dispositif dont le CS est le #2,
//            actif bas, et l'adresse est la 4 (00000100).
//
//    Fonctions appel�es : HAL_GPIO_WritePin(),  HAL_GPIO_ReadPin
//    Param�tres d'entr�e : CSx, Level, ucAdresse	
//                          CSx : 0, 1, 2, 3, 4
//                          Level : 0, 1
//                          ucAdresse : 0x00 � 0x1F
//    Param�tres de sortie : uint8_t		
//    Variables utilis�es : CSx, Level, ucAdresse
//    Equate : Aucun	
//    #Define : Aucun	
// 	
//******************************************************************************
uint8_t ucReadIO (uint8_t CSx, uint8_t Level, uint8_t ucAdresse)
{
  union
 {       
   struct 
   {
     int D0 : 1;                                 //Noms des bits.
     int D1 : 1;                                 //On ferait l'appel ainsi :
     int D2 : 1;                                 //unData.DataBit.D0 = 0;
     int D3 : 1;                                 //ou,
     int D4 : 1;                                 //unData.ucData = 0x03;
     int D5 : 1; 
     int D6 : 1; 
     int D7 : 1; 
   } DataBit;                                    //Nom du champ de bits.
   uint8_t ucData;                               //Variable associ�e � la structure.  
 }unData;  
                                                 //Nom de l'union.
 uint8_t ucLireDataIO;
  
 vData_IN ();                                    //Le port de Data est en 
                                                 //entr�e. 
 //Affectation des lignes d'adresse.
 if ((ucAdresse & 0x01) != 0)
   HAL_GPIO_WritePin(GPIOD, A0_Pin, GPIO_PIN_SET);
 else
   HAL_GPIO_WritePin(GPIOD, A0_Pin, GPIO_PIN_RESET);
 if ((ucAdresse & 0x02) != 0)
   HAL_GPIO_WritePin(GPIOD, A1_Pin, GPIO_PIN_SET);
 else
   HAL_GPIO_WritePin(GPIOD, A1_Pin, GPIO_PIN_RESET);
 if ((ucAdresse & 0x04) != 0)
   HAL_GPIO_WritePin(GPIOD, A2_Pin, GPIO_PIN_SET);
 else
   HAL_GPIO_WritePin(GPIOD, A2_Pin, GPIO_PIN_RESET);
 if ((ucAdresse & 0x08) != 0)
   HAL_GPIO_WritePin(GPIOD, A3_Pin, GPIO_PIN_SET);
 else
   HAL_GPIO_WritePin(GPIOD, A3_Pin, GPIO_PIN_RESET);
 if ((ucAdresse & 0x10) != 0)
   HAL_GPIO_WritePin(GPIOB, A4_Pin, GPIO_PIN_SET);
 else
   HAL_GPIO_WritePin(GPIOB, A4_Pin, GPIO_PIN_RESET);

//Choix du CS. 
  switch (CSx)                                 
 {
 case 0 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_RESET);
   else
     HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_SET); 
 break;
  
 case 1 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS1_Pin, GPIO_PIN_RESET);
   else
     HAL_GPIO_WritePin(GPIOB, CS1_Pin, GPIO_PIN_SET); 
 break;
 
 case 2 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS2_Pin, GPIO_PIN_RESET);
   else
     HAL_GPIO_WritePin(GPIOB, CS2_Pin, GPIO_PIN_SET); 
 break;
 
 case 3 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS3_Pin, GPIO_PIN_RESET);
   else
     HAL_GPIO_WritePin(GPIOB, CS3_Pin, GPIO_PIN_SET); 
 break;
 
 default :
 break;   
 }
 
 HAL_GPIO_WritePin(GPIOB, RD_Pin, GPIO_PIN_RESET);   //Activer le RD.
 unData.DataBit.D0 = HAL_GPIO_ReadPin(GPIOE, D0_Pin); //Lire D0.
 unData.DataBit.D1 = HAL_GPIO_ReadPin(GPIOE, D1_Pin); //Lire D1.
 unData.DataBit.D2 = HAL_GPIO_ReadPin(GPIOE, D2_Pin); //Lire D2.
 unData.DataBit.D3 = HAL_GPIO_ReadPin(GPIOE, D3_Pin); //Lire D3.
 unData.DataBit.D4 = HAL_GPIO_ReadPin(GPIOE, D4_Pin); //Lire D4.
 unData.DataBit.D5 = HAL_GPIO_ReadPin(GPIOE, D5_Pin); //Lire D5.
 unData.DataBit.D6 = HAL_GPIO_ReadPin(GPIOE, D6_Pin); //Lire D6.
 unData.DataBit.D7 = HAL_GPIO_ReadPin(GPIOE, D7_Pin); //Lire D7.
 HAL_GPIO_WritePin(GPIOB, RD_Pin, GPIO_PIN_SET);     //D�sactiver le RD.
 
 //Remettre le CS inactif.
 switch (CSx)
 {
 case 0 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_SET);
   else
     HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_RESET); 
 break;
  
 case 1 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS1_Pin, GPIO_PIN_SET);
   else
     HAL_GPIO_WritePin(GPIOB, CS1_Pin, GPIO_PIN_RESET); 
 break;
 
 case 2 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS2_Pin, GPIO_PIN_SET);
   else
     HAL_GPIO_WritePin(GPIOB, CS2_Pin, GPIO_PIN_RESET); 
 break;
 
 case 3 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS3_Pin, GPIO_PIN_SET);
   else
     HAL_GPIO_WritePin(GPIOB, CS3_Pin, GPIO_PIN_RESET); 
 break;
  
 default :
 break;   
 }
 ucLireDataIO = unData.ucData;
 return (ucLireDataIO);
}
//fin routine ucRead_IO---------------------------------------------------------


//*********************************vWrite_IO************************************
//    Nom de la fonction : vWrite_IO
//    Auteur : Alain Champagne		
//    Date de cr�ation : 21-12-2015
//    Description : 	Routine pour placer les lignes de donn�es en sortie. 
//	
//    Appel : vWrite_IO(2, 0, 0x04);
//            Permet d��crire une donn�e sur un dispositif dont le CS est le #2,
//            actif bas, et l'adresse est la 4 (00000100).
//
//    Fonctions appel�es : HAL_GPIO_WritePin(),  HAL_GPIO_ReadPin
//    Param�tres d'entr�e : CSx, Level, ucAdresse	
//                          CSx : 0, 1, 2, 3, 4
//                          Level : 0, 1
//                          ucAdresse : 0x00 � 0x1F
//    Param�tres de sortie : uint8_t		
//    Variables utilis�es : CSx, Level, ucAdresse
//    Equate : Aucun	
//    #Define : Aucun	
// 						
//******************************************************************************
void vWriteIO(uint8_t ucEcrireDataIO, uint8_t CSx, uint8_t Level, uint8_t ucAdresse)
{
  union
 {       
   struct 
   {
     int D0 : 1;                                 //Noms des bits.
     int D1 : 1;                                 //On ferait l'appel ainsi :
     int D2 : 1;                                 //unData.DataBit.D0 = 0;
     int D3 : 1;                                 //ou,
     int D4 : 1;                                 //unData.ucData = 0x03;
     int D5 : 1; 
     int D6 : 1; 
     int D7 : 1; 
   } DataBit;                                    //Nom du champ de bits.
   uint8_t ucData;                               //Variable associ�e � la structure.  
 }unData;                                        //Nom de l'union.
                                                 
 vData_OUT ();                                   //Le port de Data est en 
                                                 //sortie. 
 unData.ucData = ucEcrireDataIO;                 //La donn�e dans l'union.
 
 //�crire la donn�e dur le bus de donn�es.
 if (unData.DataBit.D0 == 0)
   HAL_GPIO_WritePin(GPIOE, D0_Pin, GPIO_PIN_RESET);
 else
   HAL_GPIO_WritePin(GPIOE, D0_Pin, GPIO_PIN_SET);
 if (unData.DataBit.D1 == 0)
   HAL_GPIO_WritePin(GPIOE, D1_Pin, GPIO_PIN_RESET);
 else
   HAL_GPIO_WritePin(GPIOE, D1_Pin, GPIO_PIN_SET);
 if (unData.DataBit.D2 == 0)
   HAL_GPIO_WritePin(GPIOE, D2_Pin, GPIO_PIN_RESET);
 else
   HAL_GPIO_WritePin(GPIOE, D2_Pin, GPIO_PIN_SET);
 if (unData.DataBit.D3 == 0)
   HAL_GPIO_WritePin(GPIOE, D3_Pin, GPIO_PIN_RESET);
 else
   HAL_GPIO_WritePin(GPIOE, D3_Pin, GPIO_PIN_SET);
 if (unData.DataBit.D4 == 0)
   HAL_GPIO_WritePin(GPIOE, D4_Pin, GPIO_PIN_RESET);
 else
   HAL_GPIO_WritePin(GPIOE, D4_Pin, GPIO_PIN_SET);
 if (unData.DataBit.D5 == 0)
   HAL_GPIO_WritePin(GPIOE, D5_Pin, GPIO_PIN_RESET);
 else
   HAL_GPIO_WritePin(GPIOE, D5_Pin, GPIO_PIN_SET);
 if (unData.DataBit.D6 == 0)
   HAL_GPIO_WritePin(GPIOE, D6_Pin, GPIO_PIN_RESET);
 else
   HAL_GPIO_WritePin(GPIOE, D6_Pin, GPIO_PIN_SET);
 if (unData.DataBit.D7 == 0)
   HAL_GPIO_WritePin(GPIOE, D7_Pin, GPIO_PIN_RESET);
 else
   HAL_GPIO_WritePin(GPIOE, D7_Pin, GPIO_PIN_SET); 
 

 //Affectation des lignes d'adresse.
 if ((ucAdresse & 0x01) != 0)
   HAL_GPIO_WritePin(GPIOD, A0_Pin, GPIO_PIN_SET);
 else
   HAL_GPIO_WritePin(GPIOD, A0_Pin, GPIO_PIN_RESET);
 if ((ucAdresse & 0x02) != 0)
   HAL_GPIO_WritePin(GPIOD, A1_Pin, GPIO_PIN_SET);
 else
   HAL_GPIO_WritePin(GPIOD, A1_Pin, GPIO_PIN_RESET);
 if ((ucAdresse & 0x04) != 0)
   HAL_GPIO_WritePin(GPIOD, A2_Pin, GPIO_PIN_SET);
 else
   HAL_GPIO_WritePin(GPIOD, A2_Pin, GPIO_PIN_RESET);
 if ((ucAdresse & 0x08) != 0)
   HAL_GPIO_WritePin(GPIOD, A3_Pin, GPIO_PIN_SET);
 else
   HAL_GPIO_WritePin(GPIOD, A3_Pin, GPIO_PIN_RESET);
 if ((ucAdresse & 0x10) != 0)
   HAL_GPIO_WritePin(GPIOB, A4_Pin, GPIO_PIN_SET);
 else
   HAL_GPIO_WritePin(GPIOB, A4_Pin, GPIO_PIN_RESET);
 
//Choix du CS.  
 switch (CSx)                                   
 {
 case 0 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_RESET);
   else
     HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_SET); 
 break;
  
 case 1 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS1_Pin, GPIO_PIN_RESET);
   else
     HAL_GPIO_WritePin(GPIOB, CS1_Pin, GPIO_PIN_SET); 
 break;
 
 case 2 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS2_Pin, GPIO_PIN_RESET);
   else
     HAL_GPIO_WritePin(GPIOB, CS2_Pin, GPIO_PIN_SET); 
 break;
 
 case 3 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS3_Pin, GPIO_PIN_RESET);
   else
     HAL_GPIO_WritePin(GPIOB, CS3_Pin, GPIO_PIN_SET); 
 break;
  
 default :
 break;   
 }
 
 //Remettre le CS inactif.
 switch (CSx)
 {
 case 0 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_SET);
   else
     HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_RESET); 
 break;
  
 case 1 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS1_Pin, GPIO_PIN_SET);
   else
     HAL_GPIO_WritePin(GPIOB, CS1_Pin, GPIO_PIN_RESET); 
 break;
 
 case 2 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS2_Pin, GPIO_PIN_SET);
   else
     HAL_GPIO_WritePin(GPIOB, CS2_Pin, GPIO_PIN_RESET); 
 break;
 
 case 3 :
   if (Level == 0)
     HAL_GPIO_WritePin(GPIOB, CS3_Pin, GPIO_PIN_SET);
   else
     HAL_GPIO_WritePin(GPIOB, CS3_Pin, GPIO_PIN_RESET); 
 break;
  
 default :
 break;   
 }
}
//fin routine vWrite_IO--------------------------------------------------------
