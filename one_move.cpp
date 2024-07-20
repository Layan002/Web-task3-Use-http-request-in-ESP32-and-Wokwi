#include <HTTPClient.h>
#include <WiFi.h>

String URL_S = "https://s-m.com.sa/s.html";

const char *ssid = "Wokwi-GUEST";
const char *password = "";

const int ledPin_S = 17;

void setup()
{
    Serial.begin(115200);
    Serial.println("Setup started...");
    connectWiFi();
    pinMode(ledPin_S, OUTPUT);
    digitalWrite(ledPin_S, LOW);
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        connectWiFi();
    }

    Serial.println("Loop started...");

    HTTPClient http_S;

    if (http_S.begin(URL_S))
    {
        int httpResponseCode_S = http_S.GET();

        if (httpResponseCode_S > 0)
        {
            String payload_S = http_S.getString();
            Serial.print("Response payload S: ");
            Serial.println(payload_S);

            if (payload_S == "stop")
            {
                Serial.println("Turning on LED Stop");
                digitalWrite(ledPin_S, HIGH);
                delay(2000);
            }
        }
        else
        {
            Serial.print("Error on HTTP request S: ");
            Serial.println(httpResponseCode_S);
        }

        http_S.end();
    }
    else
    {
        Serial.println("Unable to connect to server for URL_S");
    }

    digitalWrite(ledPin_S, LOW);

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
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --