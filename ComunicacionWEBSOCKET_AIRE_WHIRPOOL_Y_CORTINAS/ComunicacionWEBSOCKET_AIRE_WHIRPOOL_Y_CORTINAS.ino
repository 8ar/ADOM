#include <SoftwareSerial.h>
#include <IRremote.h>
#include <ArduinoJson.h>
#define buff 255
//Definicion de comunicacion de pines
SoftwareSerial ArduinoUno(10,2);
//SoftwareSerial ArduinoUno(3,8);

const size_t capacity = 4*JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(5) + 30;
DynamicJsonDocument doc(capacity);
IRsend irsend;

unsigned long          bits;
unsigned long          value;
unsigned long          type;

void setup(){
  Serial.begin(9600);
  ArduinoUno.begin(4800);  
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
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
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        int N_M =doc["N_M"];
        type=doc[String("type")];
                if (type==1){
                    
                    digitalWrite(4, HIGH);
                    for (int i=0; i<N_M; i++) {
                          value=doc[String("values")][i];
                          bits=doc[String("bits")][i];
                          int order=doc[String("order")][i];                  
                          irsend.sendNEC(value, bits,order);
                    } 
                  digitalWrite(4, LOW);
                
                              
                 }else if (type==3){
                  digitalWrite(5, HIGH);
                  
                    for(int j=0;j<=12;j++){
                      value=doc[String("values")][0];
                      bits=doc[String("bits")][0];
                      int order=doc[String("order")][0];  
                      irsend.sendRF(value, bits,order,400);
                      value=doc[String("values")][1];
                      bits=doc[String("bits")][1];
                      order=doc[String("order")][1];  
                      irsend.sendRF(value, bits,order,400);
                     }
                 digitalWrite(5, LOW);
                 Serial.println("Fin mensaje de Radio frecuencia");
                 }

    
    }
   }

  
}
