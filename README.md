> [!NOTE]
> This task combines Two previous tasks: [Designing a web control panal for robot and saving it in database](https://github.com/Layan002/Web-Task1-designing-a-web-saving-it-with-database	), and [Designing another web to save the last value from task1](https://github.com/Layan002/Web-Task2-Take-the-last-data-to-new-web-page/blob/main/README.md)

------------------------------------------------
-------------------------------------------------


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
``` PYTHON
import requests
```
- This library is important to get the request to any url on the internet.
----------------------------------------------------------------
``` PYTHON
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

``` PYTHON
response.raise_for_status()
```
- This is to show the reason of any potential error if it occurs.
------------------------------------------------------------------

``` PYTHON
type1= response.headers['content-type']

print(type1)
```
- This step is not important if you know the content website type. I didn't know how to fetch the content because I dont know the type, so I use the above step and it succeded. Therefore, the type was a text.
``` OUTPUT
Output:

text/html
```
---------------------------------------------------------------------
 
``` PYTHON
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


------------------------------------------------
-------------------------------------------------

# Applyin on Wokwi
I've used the following code and it was the final one after facing so many problems but I've succeded in troubilshooting it.<br> 

## Simulation Video
https://github.com/user-attachments/assets/935d7568-7be8-4381-9dc3-84f47ed19564



## Final Circuit Simulation
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
> [!NOTE]
> There is a limitation in HTTPClient library since it can't take more than 4 URLs at the same time. This is the reoson behind why I did not include this URL: ["https://s-m.com.sa/l.htm"l](https://s-m.com.sa/l.html) which is responsible about the stop movemen, but I will use it in explination to improve that it works well individually without facing any problem 👍.

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
--------------------------------------------------------
```
- The libraries I've used are:
``` CPP
#include <HTTPClient.h>
#include <WiFi.h>
```
- HTTPClient.h is the library that is responsible about requesting the website and getting the text from it.
- WiFi.h is the library for the ESP32 that is reponsible about making connections between both ESP32 and the WiFi, in another word, initiallizing 'hotspot'.
------------------------------------------------------------
``` CPP
String URL_S = "https://s-m.com.sa/s.html";
```
- Defines a String variable URL_S that holds the URL you will be sending an HTTP request to.
----------------------------------------------------------
``` CPP
const char* ssid = "Wokwi-GUEST";
const char* password = "";
```
- Defines the WiFi SSID and password for connecting to the network. The const char* type is used for string literals.
- Wokwi simulator uses each of "Wokwi-GUEST" ssid and no password (As what they mentioned me when I have trouble with wifi connection).
--------------------------------------------------------------
``` CPP
const int ledPin_S = 17;
```
- Defines a constant integer ledPin_S representing the GPIO pin number (17) to which the LED is connected.
--------------------------------------------------------------
``` CPP
void setup() {
  Serial.begin(115200);
  Serial.println("Setup started...");
  connectWiFi();
  pinMode(ledPin_S, OUTPUT);
  digitalWrite(ledPin_S, LOW);
}
```
- Serial.begin(115200); initializes serial communication at a baud rate of 115200.
- Serial.println("Setup started..."); prints a message indicating that the setup phase has started.
- connectWiFi(); calls a function to connect to the WiFi network, it is strongly recommended to use in every ESP32 project in setup and loop. I will explain it in loop section in detalis. 
- pinMode(ledPin_S, OUTPUT); sets the LED pin as an output. If you don't do this command, it won't turn on because the default mode is INPUT. 
- digitalWrite(ledPin_S, LOW); ensures that the LED is off initially by setting the pin to LOW. If it is "HIGH" the led will be turned on.
-------------------------------------------------------------------------
Now I will break down the void loop(), and explain every line in it:
``` CPP
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
```
----------------------------------------------
``` CPP
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }
```
- 'if' (WiFi.status() != WL_CONNECTED) { connectWiFi(); } checks if the device is connected to WiFi; if not, it tries to reconnect. By colling this function: connectWiFi(), then it will goes to: 
``` CPP
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
This will make it reconnect the wifi if something went wrong. 
-------------------------------------------------------------
``` CPP
Serial.println("Loop started...");
```
- Serial.println("Loop started..."); prints a message indicating that the main loop has started. If it is not printed, this means that the connection to the internet was failed.
----------------------------------------------------------------
``` CPP
HTTPClient http_S;
```
- HTTPClient http_S; creates an HTTPClient object for making HTTP requests.
-------------------------------------------------------------------
``` CPP
if (http_S.begin(URL_S)) {
    int httpResponseCode_S = http_S.GET();
    // If's statements, but I didn't write it to make the wxplination clear!!
}
else {
    Serial.println("Unable to connect to server for URL_S");
  }
```
- if (http_S.begin(URL_S)) { initializes the HTTP client with the specified URL. Returns true (non-zero value): If the initialization is successful and the HTTP client is ready to make requests to the URL. This means that the URL is valid, and the HTTP client has been set up correctly. Thus it will go into the follwing if statement
``` CPP
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
  }
``` 
- Returns false (zero value): If there is an issue initializing the HTTP connection. This could happen due to an invalid URL, network issues, or problems setting up the HTTP client. and then will get to the else statement:
``` CPP
else {
    Serial.println("Unable to connect to server for URL_S");
  }
```
 printing: "Unable to connect to server for URL_S" <br>
 
- int httpResponseCode_S = http_S.GET(); sends a GET request to the URL and stores the HTTP response code (if it is 200 "2XX" it is succesded and will get into (httpResponseCode_S > 0) if it is something else, then there is an error. and will excute  Serial.print("Error on HTTP request S: "); Serial.println(httpResponseCode_S);
``` CPP
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
```
- String payload_S = http_S.getString(); retrieves the response payload as a String, which is here "stop".
- Serial.print("Response payload S: "); prints a label for the response payload to ensure that the logic of c++ got into this if statement..
- Serial.println(payload_S); prints the actual response payload to make sure it is "stop" as what we expected.
``` CPP
if (payload_S == "stop") {
        Serial.println("Turning on LED Stop");
        digitalWrite(ledPin_S, HIGH);
        delay(2000);
      }
```
- if (payload_S == "stop") { checks if the payload matches the string "stop". if it matches it will print: "Turning on LED Stop" this will make use sure that if statement here is excuted and prints a message indicating that the LED will be turned on.
- digitalWrite(ledPin_S, HIGH); turns on the LED by setting the pin to HIGH.
- delay(2000); waits for 2 seconds.<br>
``` CPP
else {
      Serial.print("Error on HTTP request S: ");
      Serial.println(httpResponseCode_S);
    }
```
- else { Serial.print("Error on HTTP request S: "); Serial.println(httpResponseCode_S); } prints an error message if the HTTP request failed.
``` CPP
 http_S.end();
```
- http_S.end(); ends the HTTP request and frees resources.
------------------------------------------------------------------------------------------------------
Then it will get out from the if statement of if if (httpResponseCode_S > 0), going to face each of:
``` CPP
digitalWrite(ledPin_S, LOW);

delay(500);
```
- digitalWrite(ledPin_S, LOW); turns off the LED by setting the pin to LOW. I did this because the loop will be repeated and I want the white LED to turn off before checkeing the if statement of (httpResponseCode_S > 0) and turning on again. 
- delay(500); waits for 500 milliseconds before repeating the loop.

-----------------------------------------------------------------
I hope that everything is clear for now.<br>

# Arduino IDE
I've used two method to contro the leds here; 
- The first one depends on the wokwi simulator. (You can fin the code in the file named "ESP32_ArduinoIDE_LOOP.ino").
- The second one by the web page that I have created for [task 1](https://github.com/Layan002/Web-Task1-designing-a-web-saving-it-with-database) & [task 2](https://github.com/Layan002/Web-Task2-Take-the-last-data-to-new-web-page/blob/main/README.md) of the web page (You can fin the code in the file named "ESP32_ArduinoIDE_web_page.ino").

## Testing on Arduino IDE for Wokwi code:
The code is excatly the same but this time I've changed the Wifi ssid and password to the one that I am using.
then pasete it as what I will show you here: <br>


``` CPP
#include <HTTPClient.h>
#include <WiFi.h>

String URL_F = "https://s-m.com.sa/f.html";
String URL_B = "https://s-m.com.sa/b.html";
String URL_R = "https://s-m.com.sa/r.html";
String URL_L = "https://s-m.com.sa/l.html";



const char* ssid = "ABDULLATIF";
const char* password = "Aa0506375183";

const int ledPin_F = 2;
const int ledPin_B = 0; 
const int ledPin_R = 4;
const int ledPin_L = 32;



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
         
      digitalWrite(ledPin_F, LOW);
      digitalWrite(ledPin_B, LOW); 
      digitalWrite(ledPin_R, LOW); 
      digitalWrite(ledPin_L, LOW);

    http_F.end();
    http_B.end();
    http_R.end();
    http_L.end();

  } else {
    Serial.println("Unable to connect to server");
  }

delay(2000);
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
### Testing Video 



https://github.com/user-attachments/assets/2bacfcbd-50ba-4af2-b697-fa678667e005









## Arduino IDE and using the Web page
In addition to changing the password as the previous step, here the URL is changed to the IP of my laptob instead of using http host of the smart-methods hosting page which is complicated to create a personal one at this time and since the website is changed to my web page which is localhost that is not hosted in the internet. <br>

to get The IP ->
``` CPP
open the cmd -> ipconfig -> IPv4 Address
```

The cose is: 
``` CPP
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
```
>[!NOTE]
> This process are depending on the web page I've created so I will insert the file in the repo, they are: "index.html", "styles.css", "send_last_movement.php", "last_movement.html", and "fetch_last_movement.php". put them all inside "robot-move" folder in this path on your computer: C:\xampp\htdocs\robot-move
> Don't forget to start mysql and apache on xampp before getting starting with the project. In addition creating a database table in mysql. You can find these steps in [task 1](https://github.com/Layan002/Web-Task1-designing-a-web-saving-it-with-database) and [task 2](https://github.com/Layan002/Web-Task2-Take-the-last-data-to-new-web-page/blob/main/README.md) for more details if you are not familiar with this process.

### Testing Video 


https://github.com/user-attachments/assets/ccd4187d-76c2-4387-b198-9aa8d2a4ecdb


