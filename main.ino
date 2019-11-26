#define BUTTON 8
#define RELAY 9
#define TEMP A5
#define ssid <SSID>
#define pass <password>
String text;
bool state=true;
String request;
float temperature;
  
void serverSet()
{
    while(!Serial.find("OK"))
    {
      Serial.println("AT+CIPSERVER=1,80");
      delay(500);
    }
}
void connectNetwork(String ssid,String password)
{
    while(!Serial.available());
    Serial.println("AT+CWMODE=1"); 
    while(!Serial.find("OK"))
    {
      Serial.println("AT+CWMODE=1"); 
      delay(500);
    }
    while(!Serial.find("WIFI GOT IP"))
    {
      Serial.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");
      delay(5000);
    }
    delay(5000);
    Serial.println("AT+CIPMUX=1");
    while(!Serial.find("OK"))
    {
      Serial.println("AT+CIPMUX=1");
      delay(500);
    }                                
}
float readTemp()
{
  int analogData = analogRead(TEMP);
  float mVoltage = (float(analogData)/1023)*5000;
  float temperature = mVoltage / 10.0;
  return temperature;
}
void setup() {
    Serial.begin(115200);
    while(!Serial.available());
    
    connectNetwork( ssid, pass);  
    pinMode(RELAY,OUTPUT);
    pinMode(BUTTON,INPUT);//button
    while(!Serial.find("OK"))
    {
      Serial.println("AT");
      delay(500);
    }
    serverSet();
    
}


void loop() { 
  while(!Serial.find(",CONNECT"))
  {
    if(digitalRead(BUTTON))
    {
      state=!state;
    }
    if(state)//state is on
    {
      text="<br>Click <a href=\"/LED=OFF\">here</a> turn the OFF<br>";
      digitalWrite(RELAY,HIGH);
    }
    else//state is off
    {
      text="<br>Click <a href=\"/LED=ON\">here</a> turn the ON<br>";
      digitalWrite(RELAY,LOW);
    }
  }
  request=Serial.readStringUntil("\n");
//   mySerial.begin(115200);
//  mySerial.println(request);


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
      text="<br>Click <a href=\"/LED=OFF\">here</a> turn the OFF<br>";
      digitalWrite(RELAY,HIGH);
    }
    else//state is off
    {
      text="<br>Click <a href=\"/LED=ON\">here</a> turn the ON<br>";
      digitalWrite(RELAY,LOW);
    }
  temperature=readTemp();
  String sendData=String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\nConnection: close\r\n\r\n<!DOCTYPE HTML>" +"<html>"+text+"<br>Temperature:"+String(temperature)+"<br></html>\r\n";

  Serial.print("AT+CIPSEND=0,");
  Serial.println(sendData.length());
  while(!Serial.find(">"));
  Serial.println(sendData);
  while(!Serial.find("SEND OK"));
  Serial.println("AT+CIPCLOSE=0");

    delay(200);
  

}
