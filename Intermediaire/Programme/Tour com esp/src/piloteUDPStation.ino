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

//Definitions de variables publiques:
// Replace with your network credentials
const char* ssid = "LeWifiACam";
const char* password = "pic16f88";

WiFiUDP ERUDP;
IPAddress IPCom6(192,168,4,88);

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
  //receiveUDP();
}
//************************************************************************************
void receiveUDP(void)
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    readBuf[i] = 0;
  }
   int len;
 if (len = ERUDP.parsePacket())
 {
   ERUDP.read(readBuf, 8);
   Serial.println("Recu:");
   Serial.println(readBuf);
 }
}
//************************************************************************************
void transUDP(unsigned char* transmitBuffer, char sizeOfBuffer)
{
  ERUDP.parsePacket();
  ERUDP.beginPacket(IPCom6, 11800);

  for(int i=0; i<sizeOfBuffer; ++i)
  {
    ERUDP.write(transmitBuffer[i]);
    printf("[%i]: %i",i,transmitBuffer[i]);
  }
  ERUDP.endPacket();
  Serial.println("Transmis:");
}
//************************************************************************************