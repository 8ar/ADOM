#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

const char* nname = "DanWifi";
const char* pass = "1234567890";
const int pin = 16;

WiFiServer server(80);


SoftwareSerial ESP8266W(D2,D3);

void setup(){
 // put your setup code here, to run once:
  WiFi.mode(WIFI_AP);
  WiFi.softAP(nname, pass);
  
  Serial.begin(115200);
  pinMode(pin,OUTPUT);
  
  digitalWrite(pin, HIGH);
  //Definicion de frecuencia de comunicacion
  
  ESP8266W.begin(4800);
  server.begin();
  
  
  }

 void loop()
 {

//

WiFiClient client = server.available();
  if(!client) {
     return;
     }

  String req = client.readStringUntil('\r');

  int dato=0;
  
  Serial.println(req);
  client.flush();



for(int i=4;i<9;i++){
  
  if(req.indexOf("/led/"+String(i)) != -1){

    dato=1;
    digitalWrite(pin, HIGH);
    client.print("LED is now om");

    
    }
    
   else if(req.indexOf("/led/off") != -1){
    digitalWrite(pin, LOW);
    client.print("LED is now off");
   }else if (req.indexOf("/") != -1){
    client.print("WELCOME TO LED CONTROL");

    delay(1);
    Serial.println("Client disconnected");} 

    if (dato!=0){
      
      
    ESP8266W.print(String(i));
    ESP8266W.println("\n");
    dato=0;
  
          }
  
      
      }


//

  
  /*

delay(3000);


  ESP8266W.print("5");
  ESP8266W.println("\n");

delay(3000);

  ESP8266W.print("6");
  ESP8266W.println("\n");
  
delay(3000);

  ESP8266W.print("7");
  ESP8266W.println("\n");

delay(3000);


  ESP8266W.print("4");
  ESP8266W.println("\n");
  
  delay(5000);*/
 }
