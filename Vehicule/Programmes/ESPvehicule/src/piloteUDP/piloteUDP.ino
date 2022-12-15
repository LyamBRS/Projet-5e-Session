/**
 * @file piloteUDP.ino
 * @author Camille Fortin (camfortin2022"gmail.com)
 * @brief Le pilote UDP sers à la communication par wifi UDP
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

//Definitions de variables publics:

/// @brief Structure contenant 2 tableau de 8 unsigned char pour la réception et la transmition UDP
extern stPILOTEUDP piloteUDP;

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:

/// @brief Le nom donné au point d'acces wifi
const char* cSsidAP = "LeWifiACam";
/// @brief Le mot de passe donné au point d'acces wifi
const char* cPasswordAP = "pic16f88";
/// @brief Adresse IP du point d'acces
IPAddress LocalIpAP (192,168,4,88);
/// @brief Adresse de passerelle réseau
IPAddress GatewayAP (192,168,4,88);
/// @brief Masque de sous réseau
IPAddress SubnetAP (255,255,255,0);
/// @brief Adresse ip du client à qui on veut envoyer les packets
IPAddress IPCom4 (192,168,4,89);
/// @brief Port auquel envoyé les packet
unsigned int localPort = 11800;

/**
 * @brief Objet udp fesant parti des librairies arduino. Permet 
 *  la communication udp avec un ESP32.
 */
WiFiUDP Udp;

/// @brief Fonction d'initialisation en mode Point d'acces du piloteUDP
/// @param  void
void piloteUDP_initialise(void)
{
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

/// @brief Fonction permettant de recevoir un packet envoyé en par wifi en utilisant UDP
/// @param  void
void receiveUDP1(void)
{
    Udp.read(piloteUDP.readBuffer, 8);
    printf("RECU\n");

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
}
//*************************************************************************************

/// @brief Fonction qui envoie un packet UDP
/// @param send Buffer with maximum of 255 unsigned char
void transUDP1(unsigned char *transmet)
{
    Udp.beginPacket(IPCom4, 11000);

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
/// @brief Fonction permettant de savoir la longueur d'un packet UDP
/// @return Un entier indiquant la quantité de caractère du packet
int GetUDPSize()
{
    return Udp.parsePacket();
}