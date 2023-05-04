#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>

#define FIREBASE_HOST "new-app-development-1a6c3.firebaseio.com"                     
#define FIREBASE_AUTH "tbhy8EM2suiorUAzIipSRO8b9UO8L44yw5iGUN3m"                       
#define WIFI_SSID "OPPO Reno 10x Zoom"                                               
#define WIFI_PASSWORD "angadkumar"                                     
#define Relay1 16 //D5
int rel1;
void setup() 
{
  Serial.begin(115200);                                                   
  pinMode(Relay1,OUTPUT);
 
  digitalWrite(Relay1,HIGH);
  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt("S1",0);                     
  
  
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }

void loop() 
{
  if (Firebase.failed())
      {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }
      
  rel1=Firebase.getString("S1").toInt();  
    
  
  if(rel1==1)                                                            
     {
      digitalWrite(Relay1,LOW);
      Serial.println("Relay 1 ON");
    }
 if(rel1==0)                                                     
    {                                      
      digitalWrite(Relay1,HIGH);
      Serial.println("Relay 1 OFF");
    }

}
