#include <Arduino.h>
#include <wire.h>
#include <Si7020.h>
#include <Wifi.h>
#include "ThingSpeak.h"  //To publish to thingspeak
#include <Pubnub.h> //To publish or subscribe to pubnub

#define PubNub_BASE_CLIENT WiFiClient


#define Si7020_ADDR 0x40

Si7020 temp_hum = Si7020 ();

const char *apiKey = "IDROPHET99Y3NTE5"; // Write API key from ThingSpeak
const char *ssid = "SHAW-xxxxx";     // wifi ssid 
const char *password = "xxxx";  //wifi password
const char* server = "api.thingspeak.com";
unsigned long channel_no = 1608099;  // thingspeak channel no

const char* pubkey = "pub-c-xxxxxxxxxxxxxxxxxx"; // Pubnub publish key
const char* subkey = "sub-c-xxxxxxxxxxxxxxxxxx"; // pubnub subscribe key
const char* channel = "smart_garden";  // Pubnub channel


float moisture, temp, humidity;  //variable for storing moisture value, temperature and humidity

int moisture_sensor = 34; //pin on ESP32 that reads moisture value from the sensor

WiFiClient client;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(26, OUTPUT);

  pinMode(moisture_sensor, INPUT);

  Serial.begin(9600);

  WiFi.mode(WIFI_STA);  //setting the esp 32 as a station so it can connect to a wifi access point.
  WiFi.begin(ssid, password); //this will connect the board to the wifi with the given ssid & password as long as it is in range.
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("Connected to Wifi: ");
  Serial.println(WiFi.localIP());

  PubNub.begin(pubkey, subkey);  //To initialize connection to pubnub

  temp_hum.begin();  // To initialize temperature & humidity measuement

  ThingSpeak.begin(client);  // To initialize connection thingspeak channel

}

void loop() {
  // put your main code here, to run repeatedly:


  temp = temp_hum.getTemp();  //Obtain temperature
  humidity = temp_hum.getRH();  //Obtain RH
  int motor_stat = digitalRead(26);  //Obtain pump status
  moisture = analogRead(moisture_sensor);  //Obtain analog moisture value
  moisture = map(moisture,3000,1000,0,100);  // convert analog moistur evalue to value between 0 & 100

  Serial.println(moisture);  // print moisture to terminal

  // Publish sensor values to thingspeak channel
  ThingSpeak.setField(1, moisture);
  ThingSpeak.setField(2, temp);
  ThingSpeak.setField(3, humidity);
  ThingSpeak.setField(4, motor_stat);

  int a = ThingSpeak.writeFields(channel_no, apiKey);

  if(a == 200){
    Serial.println("Channels update successful.");
  }
  else{
    Serial.println("Problem updating channels. HTTP error code " + String(a));
  }

  // Subscribe to pubnub channel to listen for messages
  auto client2 = PubNub.subscribe(channel);
    if (client2 != 0) {
      String msg;
      SubscribeCracker control(client2);
      while (!control.finished()) {
        control.get(msg);
        if (msg.length() > 0) {
          Serial.print("Received: ");
          Serial.println(msg);

          if (msg == "\"remote\"") {
            digitalWrite(26,1);
            Serial.println("Remote Control activated.");
            delay(15000);
            digitalWrite(26,0);
          }

          else if ( msg == "\"sensor\"") {
            Serial.println("Sensor Mode activated.");
            if (moisture < 50) {
              digitalWrite(26,1);
            }
            else {
              digitalWrite(26,0);
            }
          }
          else {
            digitalWrite(26,0);
          }
        }
      }
    }
}