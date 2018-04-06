#include <Arduino.h>
#include "functions.h"
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "Emiel";      // your network SSID (name)
char pass[] = "12345678";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(8888);

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void setup() {

    DDRD |= 0b11111100;
    DDRB |= 0b11;
    DDRC |= 0b111111;

    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }

    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present");
      // don't continue:
      while(true);
    }

    // attempt to connect to Wifi network:
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
      status = WiFi.begin(ssid, pass);

      // wait 10 seconds for connection:
      delay(10000);
    }
    server.begin();
    // you're connected now, so print out the status:
    printWifiStatus();

}

int mode = 0;
bool override = false;
int direction = 0;
char c = '0';



void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line

  //  char mess[] = {};
    while (client.connected()) {

      if (client.available() > 0) {
        c = client.read();
      }


        if(c == '#')
        {
          Serial.println("");
        }
        if(c == '1'){
          override = true;
          trafficLightMode(1);
        }
        if(c == '2'){
          override = true;
          trafficLightMode(3);
        }
        if(c == '3'){
          override = true;
          trafficLightMode(5);
        }
        if(c == '4'){
          override = true;
          trafficLightMode(7);
        }
        if(c == '0'){
          override = false;
          int mode = cycleTrafficLights();
          trafficLightMode(mode);
        }

        Serial.write(c);

      }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }

}





    // put your main code here, to run repeatedly: