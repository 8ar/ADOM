#include <SoftwareSerial.h>
#include <IRremote.h>
//Definicion de comunicacion de pines
SoftwareSerial ArduinoUno(3,2);

//Declaracion de constantes

  //Botones


#define BUTTON_PIN_ONOFF 4
#define BUTTON_PIN_FAN 5
#define BUTTON_PIN_ION 6 
#define BUTTON_PIN_MOVE 7 
#define BUTTON_PIN_TIMER 8 



  //DATOS PARA ENVIAR
    //ON OFF
const unsigned int rawCodes1[]={8800  ,4750 ,400  ,1850 ,450  ,1800 ,350  ,750  ,400  ,800  ,450  ,700  ,0  ,350  ,65486  ,900  ,300  ,1950 ,350  ,1900 ,350  ,1900 ,350  ,1950 ,300  ,2000 ,300  ,800  ,400  ,750  ,350  ,800  ,300  ,1950 ,300  ,900  ,350  ,800  ,300  ,900  ,300  ,800  ,250  ,900  ,300  ,750  ,400  ,1900 ,350  ,1900 ,350  ,2000 ,300  ,850  ,300  ,900  ,200  ,850  ,300  ,800  ,350  ,850  ,300  ,800  ,350  ,850  ,100  ,1000 ,300  ,900  ,250  ,850  ,300  ,850  ,300  ,850  ,250  ,900  ,200  ,2050 ,250  ,900  ,400  ,750  ,250  ,850  ,450  ,1000 ,50 ,900  ,200  ,900  ,350  ,800  ,250  ,850  ,350  ,1850 ,400  ,800};  
    //TIMER
const unsigned int rawCodes2[]={ 1150, 500, 1150,  550, 300, 1350,  1150,  500, 1150,  550, 300, 1350,  300, 1400,  300, 1350,  1150,  500, 300, 1400,  300, 1350 , 300};
    //cool
const unsigned int rawCodes3[]={ 1100,550, 1150,  500, 350, 1350,  1100,  550, 1150,  550, 250, 1400,  300, 1350,  300, 1400,  250, 1400,  300, 1350,  1150,  550, 250};
    //ION
const unsigned int rawCodes4[]={ 1150, 550, 1100,  550, 300, 1400,  1100,  550, 1100,  550, 300, 1350,  1150,  550, 300, 1400,  250, 1400,  300, 1350,  300, 1400,  300};
    //ROTAR
const unsigned int rawCodes5[]={ 1100, 550, 1100,  550, 300, 1400,  1100,  550, 1100,  600, 250, 1400,  300, 1350,  1100,  600, 300, 1350,  250, 1400,  350, 1350 , 300};
  //Delclaracion de constructores para poder enviar los datos
IRsend irsend;







void setup(){

  Serial.begin(9600);
  
  ArduinoUno.begin(4800);
  
  
  }

 void loop()
 {
  
  while(ArduinoUno.available()>0){


    int val=int(ArduinoUno.parseFloat());
    
    Serial.println(val);
    
            if(ArduinoUno.read()=='\n')
              {
              int codeLen=106;
                  Serial.println(val);
                     switch (val) {
                                    case BUTTON_PIN_ONOFF:
                                      // statements
                                      irsend.sendRaw(rawCodes1, codeLen, 38);
                                      
                                      break;
                                    case BUTTON_PIN_FAN:
                                      // statements
                                      irsend.sendRaw(rawCodes2, codeLen, 38);
                                      
                                      break;
                                  
                                    case BUTTON_PIN_ION:
                                      // statements
                                      irsend.sendRaw(rawCodes3, codeLen, 38);
                                      
                                      break;
                                  
                                      case BUTTON_PIN_MOVE:
                                      // statements
                                      irsend.sendRaw(rawCodes4, codeLen, 38);
                                      
                                      
                                      break;
                                      
                                      case BUTTON_PIN_TIMER:
                                      // statements
                                      irsend.sendRaw(rawCodes5, codeLen, 38);
                                      
                                      break;
                                      
                                    default:
                                      // Sin accion
                                      break;
                                  }
                                  delay(40);

                  
              }
    
    }
    delay(30);
  
  
  }
