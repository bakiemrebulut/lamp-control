# lamp-control
Arduino and LAN based lamp automation with ESP01  
  
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
  
System can be controlled with button and web page.  
Web page is streamed on IP address of ESP so you should be write your own SSID&password in code and check your IP on serial monitor.  
Then you can access page with this IP.  
System is reset each approximately 1 hour cycle if no request arrived to ESP for eliminate connection fails and sleep of ESP.
You can check the system is whether or not ready for conection by led on pin 13. 

Example web page:  
Click here turn the OFF   
                              
Temperature:25.42
