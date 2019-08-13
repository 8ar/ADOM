/*
 * IRrecord: record and play back IR signals as a minimal 
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * An IR LED must be connected to the output PWM pin 3.
 * A button must be connected to the input BUTTON_PIN; this is the
 * send button.
 * A visible LED can be connected to STATUS_PIN to provide status.
 *
 * The logic is:
 * If the button is pressed, send the IR code.
 * If an IR code is received, record it.
 *
 * Version 0.11 September, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

//Declaracion de constantes

  //Botones

#define BUTTON_PIN_ONOFF 9
#define BUTTON_PIN_FAN 5
#define BUTTON_PIN_ION 6 
#define BUTTON_PIN_MOVE 7 
#define BUTTON_PIN_TIMER 8 
#define BUTTON_WHIRPOOL_ONOFF 4

  //DATOS PARA ENVIAR
    //ON OFF
//const unsigned int rawCodes1[]={ 1150 , 500 , 1150 , 550 , 300 , 1350 , 1150 , 500 , 1150 , 550 , 300 , 1350 , 300 , 1400 , 250 , 1400 , 300 , 1350 , 300 , 1400 , 300 , 1350 , 1150};
const unsigned int rawCodes1[]={ 8800 ,4750 ,400  ,1850 ,450  ,1800 ,350  ,750  ,400  ,800  ,450  ,700  ,0  ,350  ,65486  ,900  ,300  ,1950 ,350  ,1900 ,350  ,1900 ,350  ,1950 ,300  ,2000 ,300  ,800  ,400  ,750  ,350  ,800  ,300  ,1950 ,300  ,900  ,350  ,800  ,300  ,900  ,300  ,800  ,250  ,900  ,300  ,750  ,400  ,1900 ,350  ,1900 ,350  ,2000 ,300  ,850  ,300  ,900  ,200  ,850  ,300  ,800  ,350  ,850  ,300  ,800  ,350  ,850  ,100  ,1000 ,300  ,900  ,250  ,850  ,300  ,850  ,300  ,850  ,250  ,900  ,200  ,2050 ,250  ,900  ,400  ,750  ,250  ,850  ,450  ,1000 ,50 ,900  ,200  ,900  ,350  ,800  ,250  ,850  ,350  ,1850 ,400  ,800};

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

decode_results results;
  


  
void setup()
{
  Serial.begin(9600);
 
  //Declaracion de pines como entrada para poderlas usar como botones
  pinMode(BUTTON_PIN_ONOFF, INPUT);
  /*pinMode(BUTTON_PIN_FAN, INPUT);
  pinMode(BUTTON_PIN_ION, INPUT);
  pinMode(BUTTON_PIN_MOVE, INPUT);
  pinMode(BUTTON_PIN_TIMER, INPUT);*/
  
}

// Storage for the recorded code
int codeType = -1; // The type of code
unsigned long codeValue; // The code value if not raw
unsigned int rawCodes[RAWBUF]; // The durations if raw

int toggle = 0; // The RC5/6 toggle state




void loop() {
  // SI EL BOTON ES PRESIONADO ESTE MANDA LA SEÑAL DE ON OFF DEL AIRE CONDICIONADO
  int codeLen = 23; // The length of the code

for (int i=4;i<5;i++)  {
  
  int buttonState = digitalRead(i);

  if (buttonState) {
    
    Serial.println("Pressed, sending");

    switch (i) {
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

    case BUTTON_WHIRPOOL_ONOFF:
    // statements
    irsend.sendRaw(rawCodes1, codeLen, 38);
    
    break;
    
    
    
  default:
    // Sin accion
    break;
}

    
   

    delay(50); // Wait a bit between retransmissions
  
  
                    }
  
  

    
                       }

     
}
