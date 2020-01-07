#include "IRremote.h"
#include "IRremoteInt.h"

//==============================================================================
//                          Radiofrecuencia para cortinas
//==============================================================================
#define FRECUENCY 70
#define TIMEMS 354
//+=============================================================================
#if SEND_RF_CURTAIN
void  IRsend::sendRF (unsigned long data,  int nbits, int frecuency, int timems)
{
	timems=TIMEMS;
	enableIROut(FRECUENCY);
if (frecuency==1) {
	mark(3829);

	space(1487);
	
	// DBG_PRINTLN("Hola");
}



	for (unsigned long  mask = 1UL << (nbits - 1);  mask;  mask >>= 1) {
		if (data & mask) {
			mark(TIMEMS);
			mark(TIMEMS);
			space(TIMEMS);
			// DBG_PRINT("1");

		} else {
			mark(TIMEMS);
			space(TIMEMS);
			space(TIMEMS);
			// DBG_PRINT("0");
		}

	}
//DBG_PRINTLN(" ");
	if (frecuency==2) {
    // DBG_PRINTLN("Adios");
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		space(TIMEMS);
		//space(0);  // Always end with the LED off
	}







}
#endif
