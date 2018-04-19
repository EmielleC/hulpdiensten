#include <Arduino.h>
#include "functions.h"
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "smart ambulance";      // your network SSID (name)
char pass[] = "test123!";   // your network password
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


trafficLightMode(1);
changeToReturn(1);
}

int mode = 0;
bool override = false;
int direction = 0;
char c = '0';
char CompletedString[63];



void loop() {

  // listen for incoming clients
Serial.print("a");
int mode = cycleTrafficLights();
Serial.println(mode);
trafficLightMode(mode);
  if(server.available()){
    Serial.println("b");
  WiFiClient client = server.available();
  Serial.println("c");
  if (client) {
    Serial.println("d");
    Serial.println("new client");
    Serial.println("e");
    // an http request ends with a blank line


    while (client.connected()) {
      //Serial.println("2");

      if (client.available()) {
        //c = client.read();
        addCharacter(client.read(),  CompletedString);
      }
      c = decodeProtocol(CompletedString);


      int mode;
        if(c == '1'){
          emergencyMode(1);

        }
        else if(c == '2'){
          emergencyMode(3);

        }
        else if(c == '3'){
          emergencyMode(5);

        }
        else if(c == '4'){
          emergencyMode(7);

        }
      else if(c == '0'){
          mode = cycleTrafficLights();
          trafficLightMode(mode);
        }
        else{
          mode = cycleTrafficLights();
          trafficLightMode(mode);
        }

        //Serial.write(CompletedString[0]);
        //Serial.write(c);
  //Serial.println("4");
      }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    Serial.println("client disonnected");
      //client.stop();

        Serial.println("3");
  }
client.stop();
Serial.println("2");

  }



}





    // put your main code here, to run repeatedly:
