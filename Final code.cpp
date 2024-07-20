#include <HTTPClient.h>
#include <WiFi.h>

String URL_F = "https://s-m.com.sa/f.html";
String URL_B = "https://s-m.com.sa/b.html";
String URL_R = "https://s-m.com.sa/r.html";
String URL_L = "https://s-m.com.sa/l.html";

const char *ssid = "Wokwi-GUEST";
const char *password = "";

const int ledPin_F = 2;
const int ledPin_B = 0;
const int ledPin_R = 4;
const int ledPin_L = 16;

void setup()
{
    Serial.begin(115200);
    Serial.println("Setup started...");
    connectWiFi();
    pinMode(ledPin_F, OUTPUT);
    pinMode(ledPin_B, OUTPUT);
    pinMode(ledPin_R, OUTPUT);
    pinMode(ledPin_L, OUTPUT);

    digitalWrite(ledPin_F, LOW);
    digitalWrite(ledPin_B, LOW);
    digitalWrite(ledPin_R, LOW);
    digitalWrite(ledPin_L, LOW);
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        connectWiFi();
    }

    Serial.println("Loop started...");

    HTTPClient http_F;
    HTTPClient http_B;
    HTTPClient http_R;
    HTTPClient http_L;

    if (http_F.begin(URL_F) && http_B.begin(URL_B) && http_R.begin(URL_R) && http_L.begin(URL_L))
    {
        int httpResponseCode_F = http_F.GET();
        int httpResponseCode_B = http_B.GET();
        int httpResponseCode_R = http_R.GET();
        int httpResponseCode_L = http_L.GET();

        if (httpResponseCode_F > 0 && httpResponseCode_B > 0 && httpResponseCode_R > 0 && httpResponseCode_L > 0)
        {
            String payload_F = http_F.getString();
            String payload_B = http_B.getString();
            String payload_R = http_R.getString();
            String payload_L = http_L.getString();

            Serial.print("Response payload: ");
            Serial.println(payload_F);
            Serial.println(payload_B);
            Serial.println(payload_R);
            Serial.println(payload_L);

            // Reset all LEDs to LOW
            digitalWrite(ledPin_F, LOW);
            digitalWrite(ledPin_B, LOW);
            digitalWrite(ledPin_R, LOW);
            digitalWrite(ledPin_L, LOW);

            if (payload_F == "forward")
            {
                Serial.println("Turning on LED Forward");
                digitalWrite(ledPin_F, HIGH);
                delay(1000);
            }
            if (payload_B == "backward")
            {
                Serial.println("Turning on LED Backward");
                digitalWrite(ledPin_B, HIGH);
                delay(1000);
            }
            if (payload_R == "right")
            {
                Serial.println("Turning on LED Right");
                digitalWrite(ledPin_R, HIGH);
                delay(1000);
            }
            if (payload_L == "left")
            {
                Serial.println("Turning on LED Left");
                digitalWrite(ledPin_L, HIGH);
                delay(1000);
            }
        }
        else
        {
            Serial.print("Error on HTTP request: ");
            Serial.print("F: ");
            Serial.print(httpResponseCode_F);
            Serial.print(" B: ");
            Serial.print(httpResponseCode_B);
            Serial.print(" R: ");
            Serial.print(httpResponseCode_R);
            Serial.print(" L: ");
            Serial.print(httpResponseCode_L);
            Serial.println();
        }

        http_F.end();
        http_B.end();
        http_R.end();
        http_L.end();
    }
    else
    {
        Serial.println("Unable to connect to server");
    }

    delay(500);
}

void connectWiFi()
{
    WiFi.mode(WIFI_OFF);
    delay(1000);
    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.print("Connected to: ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}