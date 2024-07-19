> [!NOTE]
> This task combines Two previous tasks: [Designing a web control panal for robot and saving it in database](https://github.com/Layan002/Web-Task1-designing-a-web-saving-it-with-database	), and [Designing another web to save the last value from task1](https://github.com/Layan002/Web-Task2-Take-the-last-data-to-new-web-page/blob/main/README.md)


# Using previous knowledge
I am learning **python** with 'Angela Yu' on Udemy website- I've finished 33 days unlit now!-, taking a bootcamb on it [100 Days of Code: The Complete Python Pro Bootcamp](https://www.udemy.com/course/100-days-of-code/?couponCode=MCLARENT71824). On day 33, I've learnt about APIs and how it works. So, I tried what I've learnt to fetch the value of 'forward' from this website: [https://s-m.com.sa/f.html](https://s-m.com.sa/f.html). 

``` python
import requests


response= requests.get("https://s-m.com.sa/f.html")
print(response)

response.raise_for_status()

type1= response.headers['content-type']

print(type1)

data = response.text

print(data)
```
## Explinations:
```
import requests
```
- This library is important to get the request to any url on the internet.
----------------------------------------------------------------
```
response= requests.get("https://s-m.com.sa/f.html")
print(response)
```
- I get the response to the url by using 'get()' method and get the output as 'response'.
- this will output:
``` OUTPUT
output:

<Response [200]>
```
- [200] or 2XX means it sucsees, if it was 4XX (eg.404) it means that it is failed.

--------------------------------------------------------------

```
response.raise_for_status()
```
- This is to show the reason of any potential error if it occurs.
------------------------------------------------------------------

```
type1= response.headers['content-type']

print(type1)
```
- This step is not important if you know the content website type. I didn't know how to fetch the content because I dont know the type, so I use the above step and it succeded. Therefore, the type was a text.
``` OUTPUT
Output:

text/html
```
---------------------------------------------------------------------

```
data = response.text

print(data)
```
- As I mentioned before, I used response.text because the data I have is a "text".
- the output is: "forward" as the content of [https://s-m.com.sa/f.html](https://s-m.com.sa/f.html).
``` output
Output:

forward
```

----------------------------------------

That is it!

Now, I will try to apply this knowledge with C++ language and ESP32. 

# Applyin on Wokwi
I've used the following code and it was the final one after facing so many problems but I've succeded in troubilshooting it.<br> 

## Circuit Simulation
<img src= "https://github.com/user-attachments/assets/5919da81-f8ca-4568-8430-5ad5179562f7" alt= "img" width= 700>

## Final Code
``` CPP
#include <HTTPClient.h>
#include <WiFi.h>

String URL_F = "https://s-m.com.sa/f.html";
String URL_B = "https://s-m.com.sa/b.html";
String URL_R = "https://s-m.com.sa/r.html";
String URL_L = "https://s-m.com.sa/l.html";



const char* ssid = "Wokwi-GUEST";
const char* password = "";

const int ledPin_F = 2;
const int ledPin_B = 0; 
const int ledPin_R = 4;
const int ledPin_L = 16;



void setup() {
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

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  Serial.println("Loop started...");

  HTTPClient http_F;
  HTTPClient http_B;
  HTTPClient http_R;
  HTTPClient http_L;


  if (http_F.begin(URL_F) && http_B.begin(URL_B) && http_R.begin(URL_R) && http_L.begin(URL_L)) {
    int httpResponseCode_F = http_F.GET();
    int httpResponseCode_B = http_B.GET();
    int httpResponseCode_R = http_R.GET();
    int httpResponseCode_L = http_L.GET();
   

    if (httpResponseCode_F > 0 && httpResponseCode_B > 0 && httpResponseCode_R > 0 && httpResponseCode_L > 0) {
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
    

      if (payload_F == "forward") {
        Serial.println("Turning on LED Forward");
        digitalWrite(ledPin_F, HIGH);
        delay(1000);
      } 
      if (payload_B == "backward") {
        Serial.println("Turning on LED Backward");
        digitalWrite(ledPin_B, HIGH);
        delay(1000);

      } 
      if (payload_R == "right") {
        Serial.println("Turning on LED Right");
        digitalWrite(ledPin_R, HIGH);
        delay(1000);

      } 
      if (payload_L == "left") {
        Serial.println("Turning on LED Left");
        digitalWrite(ledPin_L, HIGH);
        delay(1000);
      }
      
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.print("F: "); Serial.print(httpResponseCode_F);
      Serial.print(" B: "); Serial.print(httpResponseCode_B);
      Serial.print(" R: "); Serial.print(httpResponseCode_R);
      Serial.print(" L: "); Serial.print(httpResponseCode_L);
      Serial.println();
    }

    http_F.end();
    http_B.end();
    http_R.end();
    http_L.end();

  } else {
    Serial.println("Unable to connect to server");
  }

delay(500);
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
```
### Explination:
Let's break it down to one LED To understnd the concept and make everything clear:

#### Diagram:
<img src= "https://github.com/user-attachments/assets/04071dff-3eca-4ffe-a1a4-3db7f55ab7d6" alt= "img" width= 700>

#### Code:
``` CPP
#include <HTTPClient.h>
#include <WiFi.h>


String URL_S = "https://s-m.com.sa/s.html";


const char* ssid = "Wokwi-GUEST";
const char* password = "";

const int ledPin_S = 17;


void setup() {
  Serial.begin(115200);
  Serial.println("Setup started...");
  connectWiFi();
  pinMode(ledPin_S, OUTPUT);
  digitalWrite(ledPin_S, LOW);
   
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  Serial.println("Loop started...");

  HTTPClient http_S;

  if (http_S.begin(URL_S)) {
    int httpResponseCode_S = http_S.GET();

    if (httpResponseCode_S > 0) {
      String payload_S = http_S.getString();
      Serial.print("Response payload S: ");
      Serial.println(payload_S);

      if (payload_S == "stop") {
        Serial.println("Turning on LED Stop");
        digitalWrite(ledPin_S, HIGH);
        delay(2000);
      }
    } else {
      Serial.print("Error on HTTP request S: ");
      Serial.println(httpResponseCode_S);
    }

    http_S.end();
  } else {
    Serial.println("Unable to connect to server for URL_S");
  }

  digitalWrite(ledPin_S, LOW);

  delay(500);
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
```
- The library I've used are:
```
#include <HTTPClient.h>
#include <WiFi.h>
```
- HTTPClient.h is the library that is responsible about requesting the website and getting the text from it.
- WiFi.h is the library for the ESP32 that is reponsible about making connections between both ESP32 and the WiFi initiallizing hotspot



