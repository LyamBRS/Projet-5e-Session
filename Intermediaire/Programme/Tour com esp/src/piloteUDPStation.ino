//piloteUDPStation:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "piloteUDP.h"
#include <WiFi.h>
#include <WiFiUdp.h>
//Definitions privees
#define DELAI 1000

//Declarations de fonctions privees:

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void receiveUDP(void);
void transUDP(char cEtat);

//Definitions de variables publiques:
// Replace with your network credentials
const char* ssid = "etudiant7";
const char* password = "etudiant7";

WiFiUDP ERUDP;
char readBuf[20];
IPAddress IPCom6(192,168,0,100);

//Definitions de fonctions publiques:
//************************************************************************************
void piloteUDPStation_initialise(void)
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
ERUDP.begin(11000);
}
//************************************************************************************

void ServiceUDPStation(void)
{
  receiveUDP();
  transUDP('A');
}
//************************************************************************************
void receiveUDP(void)
{
   int len;
 if (len = ERUDP.parsePacket())
 {
   ERUDP.read(readBuf, 20);
   Serial.println("Recu:");
   Serial.println(readBuf);
}
//************************************************************************************
void transUDP(char cEtat)
{
  ERUDP.parsePacket();
 ERUDP.beginPacket(IPCom6, 11800);
 ERUDP.write(cEtat);
 ERUDP.endPacket();
 Serial.println("Transmis:");
}
//************************************************************************************