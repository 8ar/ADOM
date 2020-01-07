#include <SoftwareSerial.h>
#include <IRremote.h>
#include <ArduinoJson.h>
#define buff 255
//Definicion de comunicacion de pines
SoftwareSerial ArduinoUno(10,2);


const size_t capacity = 3*JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(4) + 30;
DynamicJsonDocument doc(capacity);
IRsend irsend;

unsigned long          bits;
unsigned long          value;

void setup(){
  Serial.begin(9600);
  ArduinoUno.begin(4800);  
  }


 void loop()
 {
 
irsend.sendRF(0b10110110011110010111111000000000, 32,1,400);
irsend.sendRF(0b00110011, 8,2,400);
delay(1000);

  //FOR LOOP END
  
 }

  
  
