#define BUTTON 8
#define RELAY 9
#define TEMP A5
#include <avr/wdt.h>

const String ssid="ssid";
const String pass="password";
String text;
bool state=true;
String request;
float temperature;
  
void serverSet()
{
    Serial.println("AT+CIPSERVER=1,80");
    (!Serial.find("OK"));
}
void connectNetwork(String ssid,String password)
{
    Serial.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");
    while(!Serial.find("WIFI GOT IP"));
    delay(10);
    Serial.println("AT+CWMODE=1"); 
    while(!Serial.find("OK"));
    delay(10);
    Serial.println("AT+CIPMUX=1");
    while(!Serial.find("OK"));
    delay(10);
}
float readTemp()
{
  int analogData = analogRead(TEMP);
  float mVoltage = (float(analogData)/1023)*5000;
  float temperature = mVoltage / 10.0;
  return temperature;
}
void setup() {
    pinMode(13,OUTPUT);
    digitalWrite(13,LOW);
    Serial.begin(115200);
    wdt_enable(WDTO_8S);
    wdt_reset();
    connectNetwork( ssid, pass);  
    wdt_reset();
    pinMode(BUTTON,INPUT);//button
    Serial.println("AT");
    while(!Serial.find("OK"));
    serverSet();
    wdt_reset();
    Serial.println("AT+CIFSR");
    Serial.println(Serial.readString());
    Serial.println("AT");
    while(!Serial.find("OK"));
    pinMode(RELAY,OUTPUT);
    wdt_reset();
    loop();
}

int count;
void loop() { 
  count=0;
  while(!Serial.find(",CONNECT"))
  {
    wdt_reset();
    digitalWrite(13,HIGH);
    if(digitalRead(BUTTON))
    {
      state=!state;
    }
    if(state)//state is on
    {
      text="<br>Click <a href=\"/LED=OFF\">here</a> turn the LED OFF<br>";
      digitalWrite(RELAY,HIGH);
    }
    else//state is off
    {
      text="<br>Click <a href=\"/LED=ON\">here</a> turn the LED ON<br>";
      digitalWrite(RELAY,LOW);
    }
    count++;
    if(count==3600)//reset every 1 hour if no request arrived
    {
      setup();
    }
  }
  request=Serial.readStringUntil("\n");
    if(request.indexOf(" /LED=ON")!=-1)// on valid
    {
      state=true;
    }
    if(request.indexOf(" /LED=OFF")!=-1)// off valid
    {
      state=false;
    }

    if(state)//state is on
    {
      text="<br>Click <a href=\"/LED=OFF\">here</a> turn the LED OFF<br>";
      digitalWrite(RELAY,HIGH);
    }
    else//state is off
    {
      text="<br>Click <a href=\"/LED=ON\">here</a> turn the LED ON<br>";
      digitalWrite(RELAY,LOW);
    }
  temperature=readTemp();
  String sendData=String("HTTP/1.1 200 OK\r\n") +
  "Content-Type: text/html\r\nConnection: close\r\n\r\n<!DOCTYPE HTML>" +
  "<html>"+text+"<br>Temperature:"+String(temperature)+"<br></html>\r\n";

  Serial.print("AT+CIPSEND=0,");
  Serial.println(sendData.length());
  while(!Serial.find(">"));
  Serial.println(sendData);
  while(!Serial.find("SEND OK"));
  Serial.println("AT+CIPCLOSE=0");

    delay(200);
  

}
