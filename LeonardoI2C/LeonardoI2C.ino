#include <SoftwareSerial.h>
//Definicion de comunicacion de pines
SoftwareSerial ArduinoUno(10,2);

//Declaracion de constantes


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
  e=char(ArduinoUno.read());
  //condicion de principio de mensajes
  if(e=="{" and messageflag1== true){
    d=d+e;
    messageflag1=false;
    } else if(messageflag1== false and e!="}"){
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
    Serial.println(d);
    delay(100);
  }
