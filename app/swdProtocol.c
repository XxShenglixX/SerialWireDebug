#include "swdProtocol.h"

/**
 *  Initialise SWD on the target by 
 * 1. Perform a line reset and switch SWJ-DP from JTAG to SWD
 * 2. Perform a line reset again and generate idle clock cycles
 * 3. Send 8 bits of SWD request header (Address of IDCODE register 0x00,Debug Port access,Read)
 * 4. Switch to input mode and generate turn around
 * 5. Read 3 bits of ACK response from the target
 * 6. Read 32 bits of IDCODE data replied by the target
 * 7. Read 1 bit of parity bit replied by the target
 * 8. Generate a turn around and switch to output mode
 * 9. Generate idle clock cycles to prepare for next transaction / stop
 */
void SWD_Initialisation()
{
	int ACK = 0, Parity = 0  ;
	uint32_t IDCODE = 0 ;

	switchJTAGtoSWD();
	readIDCODEReg();

	SWDIO_InputMode();
	turnAround();

	read3bit(&ACK);
	read32bit(&IDCODE);
	Parity = readBit();

	SWDIO_OutputMode();
	turnAround();
	extraIdleClock(8);
}

/**
 * Perform the switching of SWJ-DP from JTAG to SWD as SWJ-DP is in JTAG mode on POR
 * This is done by performing a line reset first followed by sending a 16 bits of 
 * JTAG to SWD switching sequence (0xE79E) and then perform a line reset and extra idle clock cycles
 *
 */
void switchJTAGtoSWD()
{
	//SWDIO_OutputMode();
	lineReset(55);
	send16bit(0xE79E);
	lineReset(55);

	extraIdleClock(3);
}
