import requests


response= requests.get("https://s-m.com.sa/f.html")
print(response)

response.raise_for_status()

type1= response.headers['content-type']

print(type1)

data = response.text

print(data)