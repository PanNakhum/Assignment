#include <Arduino.h>
#include<WiFi.h>
#include <PubSubClient.h>
#include "../include/CONFIG.h"
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>

WiFiClient client;
PubSubClient mqtt(client);

OneWire oneWire1(DS18B20_1);  // Init onewire
OneWire oneWire2(DS18B20_2);

DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);

void sendData(float temp1,float temp2){ // Function send data publish data JSON form
  char jsonS[200];
  sprintf(jsonS,"{\"temperature1\":%.3f,\"temperature2\":%.3f}",temp1,temp2); // Add temp to JSON form
  Serial.println(jsonS); // Print
  mqtt.publish(THINGS_BOARD_TOPIC, jsonS); // Publish to topic
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Setup serial

  // Start the DS18B20 sensor 1 & 2
  sensors1.begin();
  sensors2.begin();

  Serial.print("Connecting to "); // Connect wifi
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt.setServer(THINGS_BOARD_HOST,THINGS_BOARD_PORT); // Set MQTT Server
}

void loop() {
  if (mqtt.connected() == false) {  // Connect and reconnect MQTT
    Serial.print("MQTT connection... ");
    if (mqtt.connect(THINGS_BOARD_NAME, THINGS_BOARD_TOKEN, THINGS_BOARD_TOKEN)) {
      Serial.println("connected");
    } else {
      Serial.println("failed");
      delay(5000);
    }
  } else {
    mqtt.loop();
  }

  sensors1.requestTemperatures();     // Read data from sensor
  float temperature1 = sensors1.getTempCByIndex(0);
  sensors2.requestTemperatures(); 
  float temperature2 = sensors2.getTempCByIndex(0);
  
  sendData(temperature1,temperature2); // Send data with function
  // For test
  // for(int i=0;i<10;i++){
  //     sendData(random(-50000,50000)/ 1000.0,random(-50000,50000)/ 1000.0);
  //     delay(2000);
  // }
  delay(2000); // Send every 2 secs

}