> [!NOTE]
> This task combines three previous tasks: [Connecting ESP32 with any sensor on WOKWI](https://github.com/Layan002/Electronics-task-3-Connecting-ESP32-with-Ultrasound), [Designing a web control panal for robot and saving it in database](https://github.com/Layan002/Web-Task1-designing-a-web-saving-it-with-database	), and [Designing another web to save the last value from task1](https://github.com/Layan002/Web-Task2-Take-the-last-data-to-new-web-page/blob/main/README.md)

# Library
The library of curlpp is a C++ wrapper library for libcurl, which is a widely used library for transferring data with URLs. libcurl provides support for various protocols such as HTTP, HTTPS, FTP, FTPS, SCP, SFTP, TFTP, LDAP, and others. curlpp simplifies the use of libcurl in C++ by providing an object-oriented interface that makes it easier to perform tasks such as making HTTP requests.

# Using previous knowledge
I am learning python with Angela on Udemy website, taking a bootcamb on it [100 Days of Code: The Complete Python Pro Bootcamp](https://www.udemy.com/course/100-days-of-code/?couponCode=MCLARENT71824). I've learnt about APIs and how it works. So, I tried what I've learnt to fetch the value of 'forward' from this website: [https://s-m.com.sa/f.html](https://s-m.com.sa/f.html). 

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
- This to show the reason of any potential error if it occurs.
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



