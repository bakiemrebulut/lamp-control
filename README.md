# lamp-control
Arduino and web based lamp automation with ESP01

Requirements:
Arduino
ESP01(ESP8266)
5v RELAY
LM35 Temperature sensor
Push Button

Connections:
Arduino.TX---------ESP.RX
Arduino.RX---------ESP.TX
Arduino.8----------BUTTON
Arduino.9----------RELAY
Arduino.A5---------LM35

Begin of running this code on arduino, may needed to reset ESP with arduino same time.
System can be controlled with button and web page.
Web page is streamed on IP address of ESP so you should be check and switch your IP with in code and write your own SSID and password.
Then you can access page with this IP.
Example web page:
------------------------------
|Click here turn the LED OFF |
|                            |
|Temperature:25.42           |
------------------------------
