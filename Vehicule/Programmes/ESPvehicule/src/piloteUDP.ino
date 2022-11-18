/**
 * @file piloteUDP.ino
 * @author Camille Fortin (camfortin2022"gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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
const char* cSsidAP = "LeWifiACam";
const char* cPasswordAP = "pic16f88";
IPAddress LocalIpAP (192,168,4,88);
IPAddress GatewayAP (192,168,4,88);
IPAddress SubnetAP (255,255,255,0);
IPAddress IPCom4 (192,168,4,89);

unsigned int localPort = 11104;
char readBuf[255]; //buffer to hold incoming packet
char ReplyBuffer[] = "acknowledged"; 


WiFiUDP Udp;


void piloteUDP_initialise(void)
{
    Serial.begin(115200);

    //Connexion en mode Point D'accès
    // démarre UDP
    Serial.begin(115200);

    Serial.print("Starting Acces Point: ");
    Serial.println(cSsidAP);


    WiFi.mode(WIFI_AP);
    WiFi.softAP(cSsidAP,cPasswordAP);
    delay(100);
    WiFi.softAPConfig(LocalIpAP, GatewayAP, SubnetAP);
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());

    Udp.begin(localPort);
}
//************************************************************************************

void ServiceUDP(void)
{
   transUDP1('D');
   //receiveUDP1();
}
//*************************************************************************************
void receiveUDP1(void)
{
  int len;
 if (len = Udp.parsePacket())
 {
   Udp.read(readBuf, 20);
   readBuf[len] = 0;
   Serial.println("Recu:");
   Serial.println(readBuf);
 }
  
}
//*************************************************************************************
void transUDP1(char cEtat)
{
    Serial.println(IPCom4);
    Udp.beginPacket(IPCom4, 11000);  // Changer IPCom4 pour adresse ip de l'esp camion
    Udp.write(cEtat);
    Udp.endPacket();
    Serial.println("Transmis:");
}
//*************************************************************************************