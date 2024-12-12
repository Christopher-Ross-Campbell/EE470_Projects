#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "CRCiPhone";            // Wi-Fi SSID
const char* password = "kgtwc8qlttkr";     // Wi-Fi password

// MQTT broker details
const char* mqtt_server = "broker.mqtt-dashboard.com"; // Public MQTT broker
const int mqtt_port = 1883;                           // Unencrypted MQTT port

// MQTT topics
const char* ledControlTopic = "campbellESP8266/MQTT/inTopic/LED";
const char* potOutputTopic = "campbellESP8266/MQTT/outTopic/POT";
const char* switchOutputTopic = "campbellESP8266/MQTT/outTopic/SWT";

// MQTT client setup
WiFiClient espClient;
PubSubClient client(espClient);

// Hardware definitions
#define POT_PIN A0
#define LED_PIN D1
#define SWITCH_PIN D2

// Variables
float voltage = 0;
int switchState = 0;
bool ledState = false;

unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 15000;

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  unsigned long startTime = millis();
  const unsigned long wifiTimeout = 30000; // 30 seconds timeout

  while (WiFi.status() != WL_CONNECTED && millis() - startTime < wifiTimeout) {
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    // Successfully connected to Wi-Fi
  } else {
    // Failed to connect to Wi-Fi
    ESP.restart(); // Restart the device if Wi-Fi connection fails
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (String(topic) == ledControlTopic) {
    if (message == "1") {
      ledState = true;
      digitalWrite(LED_PIN, HIGH);
    } else if (message == "0") {
      ledState = false;
      digitalWrite(LED_PIN, LOW);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      client.subscribe(ledControlTopic);
    } else {
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastPublishTime > publishInterval) {
    lastPublishTime = now;

    int potValue = analogRead(POT_PIN);
    voltage = potValue * (3.3 / 1023.0);
    String payload = String(voltage, 2);

    client.publish(potOutputTopic, payload.c_str());
  }

  switchState = digitalRead(SWITCH_PIN);
  if (switchState == LOW) {
    client.publish(switchOutputTopic, "1");
    delay(5000);
    client.publish(switchOutputTopic, "0");
    delay(200);
  }
}