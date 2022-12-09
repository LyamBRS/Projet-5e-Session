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

//Definitions de variables privees:
extern stPILOTEUDP piloteUDP;

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

unsigned int localPort = 11800;

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
//*************************************************************************************
void receiveUDP1(void)
{
    //int len = Udp.parsePacket();
    //printf("%i\n",len);
    //if (len >= 1)
    //{
    //Serial.println("RX:\n");
        printf("RECU\n");
        Udp.read(piloteUDP.readBuffer, 8);
        

        /*
        Serial.println("Recu:");
        Serial.println(piloteUDP.readBuffer[0]);
        Serial.println(piloteUDP.readBuffer[1]);
        Serial.println(piloteUDP.readBuffer[2]);
        Serial.println(piloteUDP.readBuffer[3]);
        Serial.println(piloteUDP.readBuffer[4]);
        Serial.println(piloteUDP.readBuffer[5]);
        Serial.println(piloteUDP.readBuffer[6]);
        Serial.println(piloteUDP.readBuffer[7]);
        */
    //}

}
//*************************************************************************************
void transUDP1(unsigned char *transmet)
{
    //Serial.println(IPCom4);
    Udp.beginPacket(IPCom4, 11000);  // Changer IPCom4 pour adresse ip de l'esp camion

    Udp.write(transmet[0]);
    Udp.write(transmet[1]);
    Udp.write(transmet[2]);
    Udp.write(transmet[3]);
    Udp.write(transmet[4]);
    Udp.write(transmet[5]);
    Udp.write(transmet[6]);
    Udp.write(transmet[7]);

    Udp.endPacket();
    Serial.println("TX:\n");
}
//*************************************************************************************
int GetUDPSize()
{
    return Udp.parsePacket();
}