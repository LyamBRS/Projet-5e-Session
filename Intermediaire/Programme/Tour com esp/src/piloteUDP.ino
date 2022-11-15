//piloteUDP:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "piloteUDP.h"
#include <WiFi.h>

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

//Definitions de fonctions publiques:
void piloteUDP_initialise(void)
{
  Serial.begin(115200);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}
//************************************************************************************

void ServiceUDP(void)
{
  WiFiClient Client = server.available(); // Note le client connecté dans client.
  //Si pas de client, Client == false
  if (Client) // Vérifie si un nouveau client est connecté
  {
   while( Client.connected() )
   {
	if (Client.available())
	{
	 unsigned char c = Client.read(); // Lit un octet du client
	 Client.write(0x89); 
	 //Serial.write(c); // Envoie cet octet sur le port série
	}
   }
 }
}
