//piloteUDP:
//Historique: 
// 2021-04-07, Yves Roy, creation
/*
//INCLUSIONS
#include "xmain.h"
#include "piloteUDP.h"
#include <WiFi.h>
#include <WiFiUdp.h>

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void receiveUDP1(void);
void transUDP1(char cEtat);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// Replace with your network credentials
const char* ssid = "etudiant7";
const char* password = "etudiant7";

WiFiUDP ERUDP;
char readBuf[20];
IPAddress IPCom4(192,168,0,103);
//Definitions de fonctions publiques:
void piloteUDP_initialise(void)
{
 Serial.begin(115200);
// Connnection sur le réseau WIFI
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.print(".");
}
// Envoie sur le port série, l'adresse IP
Serial.println("");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
//Connexion en mode station
WiFi.mode(WIFI_MODE_STA);
 // démarre UDP
ERUDP.begin(11800);
}
//************************************************************************************

void ServiceUDP(void)
{
   transUDP1('D');
   receiveUDP1();
}
//*************************************************************************************
void receiveUDP1(void)
{
  int len;
 if (len = ERUDP.parsePacket())
 {
   ERUDP.read(readBuf, 20);
   readBuf[len] = 0;
   Serial.println("Recu:");
   Serial.println(readBuf);
 }
  
}
//*************************************************************************************
void transUDP1(char cEtat)
{
  Serial.println(IPCom4);
 ERUDP.beginPacket(IPCom4, 11000);  // Changer IPCom4 pour adresse ip de l'esp camion
 ERUDP.write(cEtat);
 ERUDP.endPacket();
 Serial.println("Transmis:");
}
//*************************************************************************************
*/