# lamp-control
Arduino and web based lamp automation with ESP01

Requirements:\n
Arduino\n
ESP01(ESP8266)\n
5v RELAY\n
LM35 Temperature sensor\n
Push Button\n
\n
Connections:\n
Arduino.TX---------ESP.RX\n
Arduino.RX---------ESP.TX\n
Arduino.8----------BUTTON\n
Arduino.9----------RELAY\n
Arduino.A5---------LM35\n
\n
Begin of running this code on arduino, may needed to reset ESP with arduino same time.\n
System can be controlled with button and web page.\n
Web page is streamed on IP address of ESP so you should be check and switch your IP with in code and write your own SSID and password.\n
Then you can access page with this IP.\n
Example web page:\n
\n
Click here turn the LED OFF \n
                            \n
Temperature:25.42           \n
