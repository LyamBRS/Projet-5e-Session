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
//pas de fonctions privees

//Definitions de variables publiques:
// Replace with your network credentials
const char* wifi_network_ssid = "ESP32-Access-Point";
const char* wifi_network_password =  "123456789";

WiFiUDP ERUDP;
char readBuf[20];

//Definitions de fonctions publiques:
void piloteUDPStation_initialise(void)
{
 Serial.begin(115200);
  // Connnection sur le réseau WIFI
  //debut retirer
  Serial.print("Connecting to ");
  Serial.println(wifi_network_ssid);
  WiFi.begin(wifi_network_ssid, wifi_network_password );
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
  ERUDP.begin(11000);
}
//************************************************************************************

void ServiceUDPStation(void)
{
  receiveUDP();
  transUDP('A');
}

void receiveUDP(void)
{
  int len;
  if (len = ERUDP.parsePacket())
  {
    ERUDP.read(readBuf, 20);
    readBuf[len] = 0;
    Serial.print(readBuf);
  }
}

void transUDP(char cEtat)
{
  ERUDP.beginPacket(ERUDP.remoteIP(), 11000);
  ERUDP.write(cEtat);
  ERUDP.endPacket();
}