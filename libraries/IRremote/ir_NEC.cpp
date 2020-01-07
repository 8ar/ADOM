#include "IRremote.h"
#include "IRremoteInt.h"
#include <stdio.h>
#include <string.h>



//==============================================================================
//                           N   N  EEEEE   CCCC
//                           NN  N  E      C
//                           N N N  EEE    C
//                           N  NN  E      C
//                           N   N  EEEEE   CCCC
//==============================================================================

// #define NEC_BITS         104
// #define NEC_HDR_MARK    9000
// #define NEC_HDR_SPACE   4500
// #define NEC_BIT_MARK     560
// #define NEC_ONE_SPACE   1690
// #define NEC_ZERO_SPACE   560
// #define NEC_RPT_SPACE   2250

#define NEC_BITS         32
#define NEC_HDR_MARK    9000
#define NEC_HDR_SPACE   4500

#define NEC_BIT_MARK     450


#define NEC_ONE_SPACE   1800
#define NEC_ZERO_SPACE   700

#define NEC_RPT_SPACE   2250



//+=============================================================================
#if SEND_NEC
void  IRsend::sendNEC (unsigned long data,  int nbits, int n_bit)
{
	// Set IR carrier frequency
	enableIROut(38);
if (n_bit>0) {
	// Header
	if (n_bit==1) {
		mark(NEC_HDR_MARK);
		space(NEC_HDR_SPACE);
	}


	// Data
	for (unsigned long  mask = 1UL << (nbits - 1);  mask;  mask >>= 1) {
		if (data & mask) {
			mark(NEC_BIT_MARK);
			space(NEC_ONE_SPACE);
		} else {
			mark(NEC_BIT_MARK);
			space(NEC_ZERO_SPACE);
		}
	}

	// Footer
	if (n_bit==4) {
		mark(NEC_BIT_MARK);
		space(0);  // Always end with the LED off
	}
}


}
#endif

//+=============================================================================
// NECs have a repeat only 4 items long
//
#if DECODE_NEC
bool  IRrecv::decodeNEC (decode_results *results)
//---ORIGINAL
// {
// 	long  data   = 0;  // We decode in to here; Start with nothing
// 	int   offset = 1;  // Index in to results; Skip first entry!?
//
// 	// Check header "mark"
// 	if (!MATCH_MARK(results->rawbuf[offset], NEC_HDR_MARK))  return false ;
// 	offset++;
//
// 	// Check for repeat
// 	if ( (irparams.rawlen == 4)
// 	    && MATCH_SPACE(results->rawbuf[offset  ], NEC_RPT_SPACE)
// 	    && MATCH_MARK (results->rawbuf[offset+1], NEC_BIT_MARK )
// 	   ) {
// 		results->bits        = 0;
// 		results->value       = REPEAT;
// 		results->decode_type = NEC;
// 		return true;
// 	}
//
// 	// Check we have enough data
// 	if (irparams.rawlen < (2 * NEC_BITS) + 4)  return false ;
//
// 	// Check header "space"
// 	if (!MATCH_SPACE(results->rawbuf[offset], NEC_HDR_SPACE))  return false ;
// 	offset++;
//
// 	// Build the data
// 	for (int i = 0;  i < NEC_BITS;  i++) {
// 		// Check data "mark"
// 		if (!MATCH_MARK(results->rawbuf[offset], NEC_BIT_MARK))  return false ;
// 		offset++;
//         // Suppend this bit
// 		if      (MATCH_SPACE(results->rawbuf[offset], NEC_ONE_SPACE ))  data = (data << 1) | 1 ;
// 		else if (MATCH_SPACE(results->rawbuf[offset], NEC_ZERO_SPACE))  data = (data << 1) | 0 ;
// 		else                                                            return false ;
// 		offset++;
// 	}
//
// 	// Success
// 	results->bits        = NEC_BITS;
// 	results->value       = data;
// 	results->decode_type = NEC;
//
// 	return true;
// }
//--- ORIGINAL
{
	long  data    = 0;  // We decode in to here; Start with nothing
	long  data2   = 0;  // We decode in to here; Start with nothing
	long  data3   = 0;  // We decode in to here; Start with nothing
	long  data4   = 0;  // We decode in to here; Start with nothing
	int   bits1   = 0;
	int   bits2   = 0;
	int   bits3   = 0;
	int   bits4   = 0;

	int   offset  = 1;  // Index in to results; Skip first entry!?
	int bits=(results->rawlen-1)/2;
	int bp=0;

	// Check header "mark"
	if (!MATCH_MARK(results->rawbuf[offset], NEC_HDR_MARK))  return false ;
	offset++;

	// Check for repeat
	if ( (irparams.rawlen == 4)
	    && MATCH_SPACE(results->rawbuf[offset  ], NEC_RPT_SPACE)
	    && MATCH_MARK (results->rawbuf[offset+1], NEC_BIT_MARK )
	   ) {
		results->bits        = 0;
		results->value       = REPEAT;
		results->decode_type = NEC;
		return true;
	}
	//
	// // Check we have enough data
	// if (irparams.rawlen < (2 * NEC_BITS) + 4)  return false ;

	// Check header "space"
	if (!MATCH_SPACE(results->rawbuf[offset], NEC_HDR_SPACE))  return false ;
	offset++;
  // bp=(offset-1)/2;
	// Build the data
	for (int i = 0;  i < bits-1;  i++) {
		// Check data "mark"
    bp=(offset-1)/2;
		if (bp>=1 && bp<=32) {
			/* code */
			if (!MATCH_MARK(results->rawbuf[offset], NEC_BIT_MARK))  return false ;
			offset++;
	        // Suppend this bit
			if      (MATCH_SPACE(results->rawbuf[offset], NEC_ONE_SPACE ))  data = (data << 1) | 1 ;
			else if (MATCH_SPACE(results->rawbuf[offset], NEC_ZERO_SPACE))  data = (data << 1) | 0 ;
			else                                                            return false ;
			bits1++;
			offset++;
		} else if (bp>=33 && bp<=64) {
			/* code */
			if (!MATCH_MARK(results->rawbuf[offset], NEC_BIT_MARK))  return false ;
			offset++;
	        // Suppend this bit
			if      (MATCH_SPACE(results->rawbuf[offset], NEC_ONE_SPACE ))  data2 = (data2 << 1) | 1 ;
			else if (MATCH_SPACE(results->rawbuf[offset], NEC_ZERO_SPACE))  data2 = (data2 << 1) | 0 ;
			else                                                            return false ;
			bits2++;
			offset++;
		}
		else if (bp>=65 && bp<=96) {
			/* code */
			if (!MATCH_MARK(results->rawbuf[offset], NEC_BIT_MARK))  return false ;
			offset++;
	        // Suppend this bit
			if      (MATCH_SPACE(results->rawbuf[offset], NEC_ONE_SPACE ))  data3 = (data3 << 1) | 1 ;
			else if (MATCH_SPACE(results->rawbuf[offset], NEC_ZERO_SPACE))  data3 = (data3 << 1) | 0 ;
			else                                                            return false ;
			bits3++;
			offset++;
		}
		else if (bp>=97 && bp<=128) {
			/* code */
			if (!MATCH_MARK(results->rawbuf[offset], NEC_BIT_MARK))  return false ;
			offset++;
	        // Suppend this bit
			if      (MATCH_SPACE(results->rawbuf[offset], NEC_ONE_SPACE ))  data4 = (data4 << 1) | 1 ;
			else if (MATCH_SPACE(results->rawbuf[offset], NEC_ZERO_SPACE))  data4 = (data4 << 1) | 0 ;
			else                                                            return false ;
			bits4++;
			offset++;
		}

DBG_PRINTLN(bp);

	}

	// Success
	results->bits        = bits;

	results->bits1       = bits1;
	results->bits2       = bits2;
	results->bits3       = bits3;
	results->bits4       = bits4;



	results->value       = data;
	results->value2       = data2;
	results->value3       = data3;
	results->value4       = data4;
	results->decode_type = NEC;

	return true;
}



#endif
