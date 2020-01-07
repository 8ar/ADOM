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
 
 bool messageflag1 = true;
 bool messageflag2 = true;
 int tries=0;
 String d="";
 String e ="";
  while(ArduinoUno.available()>0 or messageflag1 or messageflag2){
  

    if(ArduinoUno.available()>0){
    e=char(ArduinoUno.read());
      //condicion de principio de mensajes
  if(e=="{" and messageflag1== true ){
    d=d+e;
    messageflag1=false;
    } else if(messageflag1== true and e=="⸮"){
      // Esta condicion espera que no haya caracteres especiales
    }else if(messageflag1== false and e!="}"){
      // Este mensaje espera que ya haya llegado el primer caracter del formato json
      d=d+e;
    } else if(messageflag1== false and e=="}"){
      // Este mensaje espera que haya llegado el ultimo caracter del formato json para poder ternerlo todo en un string
      d=d+e;
      messageflag2=false;
    } else if(messageflag1== true and e=="}"){
      // Este mensaje espera que haya llegado el ultimo caracter del formato json para poder ternerlo todo en un string
      d="";
    }   
      }
  
  
    }


        
    if(d!=""){
      Serial.println(d);
      
    DeserializationError error = deserializeJson(doc, d);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
   //IF ERROR END
  } else{
  int N_M =doc["N_M"];



  for (int i=0; i<N_M; i++) {
  value=doc[String("values")][i];
  bits=doc[String("bits")][i];
  int order=doc[String("order")][i];
 // Serial.println("Enviandose ");
 // Serial.println(value,BIN);
 //Serial.println(bits,DEC);
  //Serial.println(order,DEC);
  //Serial.println("Enviandose ");
  irsend.sendRF(value, bits,order,400);
   //Serial.println("Enviado ");
    } 
  

    
    }
  //FOR LOOP END
  
 }

  
  }
