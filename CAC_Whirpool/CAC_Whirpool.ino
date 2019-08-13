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
#define BUTTON_WHIRPOOL_OFF 5
#define BUTTON_SPEED 6 
#define BUTTON_PIN_MOVE 7 
#define BUTTON_PIN_TIMER 8 
#define BUTTON_WHIRPOOL_ON 4

  //DATOS PARA ENVIAR
    //ON
//const unsigned int rawCodes1[]={ 1150 , 500 , 1150 , 550 , 300 , 1350 , 1150 , 500 , 1150 , 550 , 300 , 1350 , 300 , 1400 , 250 , 1400 , 300 , 1350 , 300 , 1400 , 300 , 1350 , 1150};
const unsigned int rawCodes1[]={8850  ,4700 ,400  ,1850 ,400  ,1850 ,450  ,700  ,400  ,700  ,450  ,700  ,450  ,700  ,450  ,1850 ,450  ,1800 ,450  ,1850 ,400  ,1850 ,450  ,1850 ,400  ,750  ,400  ,700  ,450  ,700  ,450  ,1800 ,450  ,700  ,500  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,1800 ,450  ,1850 ,450  ,1800 ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,650  ,450  ,700  ,450  ,700  ,500  ,650  ,500  ,650  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,650  ,500  ,1750 ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,450  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,1750 ,550  ,600  ,500  ,700  ,450  ,700  ,450  ,650  ,500  ,650  ,500  ,650  ,500  ,600  ,500  ,650  ,500  ,650  ,500  ,700  ,450  ,650  ,500  ,650  ,500  ,650  ,450  ,700  ,450  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,450  ,700  ,450  ,700  ,450  ,650  ,450  ,1800 ,500  ,650  ,500  ,650  ,500  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,650  ,500  ,650  ,500  ,1800 ,450  ,700  ,450  ,1800 ,450  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,1800 ,450  ,1800 ,450  ,1850 ,450  ,1800 ,450  ,700  ,450  ,650  ,500  ,1800 ,450  ,700  ,450};
    //OFF
const unsigned int rawCodes2[]={ 8850 ,4650 ,450  ,1800 ,500  ,1800 ,450  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,1750 ,500  ,1800 ,500  ,1750 ,500  ,1800 ,450  ,1800 ,500  ,1750 ,500  ,650  ,500  ,650  ,500  ,1750 ,500  ,650  ,500  ,700  ,450  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,450  ,1800 ,500  ,1750 ,500  ,1800 ,500  ,650  ,500  ,600  ,500  ,700  ,450  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,450  ,650  ,500  ,650  ,450  ,700  ,450  ,700  ,450  ,1800 ,500  ,650  ,500  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,650  ,500  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,450  ,700  ,450  ,1800 ,500  ,650  ,500  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,700  ,450  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,650  ,500  ,650  ,500  ,650  ,500  ,1800 ,450  ,700  ,450  ,1800 ,450  ,700  ,450  ,650  ,500  ,650  ,500  ,650  ,500  ,700  ,450  ,1800 ,450  ,1800 ,450  ,1850 ,450  ,650  ,500  ,1750 ,500  ,1800 ,500  ,650  ,450  ,700  ,450};
  //SPEED

const unsigned int rawCodes3[]={ 8900 ,4650 ,450  ,1800 ,450  ,1800 ,500  ,650  ,450  ,700  ,450  ,650  ,500  ,650  ,450  ,1800 ,500  ,1800 ,450  ,1850 ,450  ,1800 ,450  ,1850 ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,1800 ,500  ,650  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,650  ,500  ,700  ,450  ,1800 ,450  ,1800 ,500  ,1750 ,500  ,700  ,450  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,700  ,450  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,700  ,450  ,1800 ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,1800 ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,700  ,450  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,650  ,500  ,1800 ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,700  ,400  ,1850 ,450  ,650  ,500  ,700  ,450  ,650  ,450  ,700  ,450  ,700  ,450  ,700  ,450  ,1800 ,450  ,1850 ,450  ,1800 ,450  ,700  ,450  ,1800 ,500  ,1800 ,450  ,700  ,450};




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
  pinMode(BUTTON_WHIRPOOL_ON, INPUT);
  pinMode(BUTTON_WHIRPOOL_OFF, INPUT);
  pinMode(BUTTON_SPEED, INPUT);
  /*pinMode(BUTTON_PIN_MOVE, INPUT);
  pinMode(BUTTON_PIN_TIMER, INPUT);*/
  
}

// Storage for the recorded code
int codeType = -1; // The type of code
unsigned long codeValue; // The code value if not raw
unsigned int rawCodes[RAWBUF]; // The durations if raw

int toggle = 0; // The RC5/6 toggle state




void loop() {
  // SI EL BOTON ES PRESIONADO ESTE MANDA LA SEÑAL DE ON OFF DEL AIRE CONDICIONADO
  int codeLen = 211; // The length of the code

for (int i=4;i<7;i++)  {
  
  int buttonState = digitalRead(i);

  if (buttonState) {
    
    Serial.println("Pressed, sending");

    switch (i) {
  case BUTTON_WHIRPOOL_ON:
    // statements
    irsend.sendRaw(rawCodes1, codeLen, 38);
    
    break;
  case BUTTON_WHIRPOOL_OFF:
    // statements
    irsend.sendRaw(rawCodes2, codeLen, 38);
    
    break;

  case BUTTON_SPEED:
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

    
   

    delay(50); // Wait a bit between retransmissions
  
  
                    }
  
  

    
                       }

     
}
