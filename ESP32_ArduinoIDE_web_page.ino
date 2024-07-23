#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h> // Include this library

String URL = "http://192.168.1.9/robot-web/fetch_last_movement.php"; // Replace with your server URL

const char* ssid = "ABDULLATIF";
const char* password = "Aa0506375183";

const int ledPin_red = 2;
const int ledPin_green = 0;
const int ledPin_blue = 4;
const int ledPin_yellow = 32;
const int ledPin_white = 25;

#define LED_BUILTIN 2

void setup() {
  Serial.begin(115200);
  Serial.println("Setup started...");
  connectWiFi();
  pinMode(ledPin_red, OUTPUT);
  pinMode(ledPin_green, OUTPUT);
  pinMode(ledPin_blue, OUTPUT);
  pinMode(ledPin_yellow, OUTPUT);
  pinMode(ledPin_white, OUTPUT);

  // Ensure all LEDs are off initially
  digitalWrite(ledPin_red, LOW);
  digitalWrite(ledPin_green, LOW);
  digitalWrite(ledPin_blue, LOW);
  digitalWrite(ledPin_yellow, LOW);
  digitalWrite(ledPin_white, LOW);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  Serial.println("Loop started...");
  HTTPClient http;

  if (http.begin(URL)) {
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.print("Response payload: ");
      Serial.println(payload);

      // Parse JSON response
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);

      String direction = doc["direction"].as<String>();
       Serial.println(direction);

      // Reset all LEDs to LOW
      digitalWrite(ledPin_red, LOW);
      digitalWrite(ledPin_green, LOW);
      digitalWrite(ledPin_blue, LOW);
      digitalWrite(ledPin_yellow, LOW);
      digitalWrite(ledPin_white, LOW);

      if (direction == "forward") {
        Serial.println("Turning on LED Forward");
        digitalWrite(ledPin_red, HIGH);
        delay(500);
      } else if (direction == "backward") {
        Serial.println("Turning on LED Backward");
        digitalWrite(ledPin_green, HIGH);
        delay(500);
      } else if (direction == "right") {
        Serial.println("Turning on LED Right");
        digitalWrite(ledPin_blue, HIGH);
        delay(500);
      } else if (direction == "left") {
        Serial.println("Turning on LED Left");
        digitalWrite(ledPin_yellow, HIGH);
        delay(500);
      } else if (direction == "stop") {
        Serial.println("Turning on LED Stop");
        digitalWrite(ledPin_white, HIGH);
        delay(500);
      }
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Unable to connect to server");
  }

  delay(500); // Delay to prevent spamming the server
}

void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
