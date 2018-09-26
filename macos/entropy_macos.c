/*
 * mbed TLS platform-specific entropy implementation for classic Mac OS and Carbon
 *
 * Copyright (C) 2018, Brendan Shanks, All Rights Reserved
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <Events.h>
#include <Processes.h>

static struct
{
	Point mouseLoc;
	UInt32 ticks;
	ProcessSerialNumber PSN;
	long processCount;
	ProcessInfoRec processInfo;
} randomdata;

int mbedtls_hardware_poll( void *data, unsigned char *output, size_t len, size_t *olen )
{
	ProcessInfoRec ProcessInfo;
	int d;

    GetMouse( &randomdata.mouseLoc );
    randomdata.ticks = TickCount( );
    
    // set processCount
    GetNextProcess (kNoProcess);
	while (GetNextProcess (&randomdata.PSN) == noErr)
		randomdata.processCount++;
	GetFrontProcess (&randomdata.PSN);

	// set processInfo
    randomdata.processInfo.processInfoLength = sizeof( randomdata.processInfo );
	randomdata.processInfo.processName = nil;
	randomdata.processInfo.processAppSpec = nil;
	GetProcessInformation( &randomdata.PSN, &randomdata.processInfo );

    *olen = sizeof( randomdata ) > len ? len : sizeof( randomdata );
    memcpy( output, &randomdata, *olen );
    
    //printf("%d", sizeof(randomdata));

    return 0;
}