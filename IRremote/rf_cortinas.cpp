#include "IRremote.h"
#include "IRremoteInt.h"

//==============================================================================
//                          Radiofrecuencia para cortinas
//==============================================================================

//+=============================================================================
#if SEND_RF_CURTAIN
void  IRsend::sendRF (unsigned long data,  int nbits, int frecuency, int timems)
{
	enableIROut(frecuency);

	for (unsigned long  mask = 1UL << (nbits - 1);  mask;  mask >>= 1) {
		if (data & mask) {
			mark(timems);
		} else {
			space(timems);

		}
	}
	space(0);  // Always end with the LED off
}
#endif
