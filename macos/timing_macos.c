/* 
 * mbed TLS timing implementation for classic Mac OS
 *
 * Copyright (C) 2017, Brendan Shanks, All Rights Reserved
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "timing_alt.h"

#include <stdlib.h>

#include <Timer.h>

volatile int mbedtls_timing_alarmed;
static int task_inserted = 0;

static struct myTMTaskStruct
{
    TMTask task;
    volatile int *timing_alarmed;
} tmTask;

// TODO: atexit() works for SIOUX apps (like benchmark) but would not
// for normal apps.
// Probably need to patch ExitToShell() or maybe use the new mbed TLS
// platform init/exit() functions
static void atexit_func( void )
{
    RmvTime( (QElemPtr)&(tmTask.task) );
}

static pascal void timerProc( TMTaskPtr tmTaskPtr )
{
    struct myTMTaskStruct *myTMTask = (struct myTMTaskStruct *)tmTaskPtr;
    *(myTMTask->timing_alarmed) = 1;
}

/**
 * \brief          Return the CPU cycle counter value
 *
 * \warning        This is only a best effort! Do not rely on this!
 *                 In particular, it is known to be unreliable on virtual
 *                 machines.
 */
unsigned long mbedtls_timing_hardclock( void )
{
    // TODO: implement
    return 0;
}

/**
 * \brief          Return the elapsed time in milliseconds
 *
 * \param val      points to a timer structure
 * \param reset    if set to 1, the timer is restarted
 */
unsigned long mbedtls_timing_get_timer( struct mbedtls_timing_hr_time *val, int reset )
{
    // TODO: implement
    return 0;
}

/**
 * \brief          Setup an alarm clock
 *
 * \param seconds  delay before the "mbedtls_timing_alarmed" flag is set
 *
 * \warning        Only one alarm at a time  is supported. In a threaded
 *                 context, this means one for the whole process, not one per
 *                 thread.
 */
void mbedtls_set_alarm( int seconds )
{
    if( !task_inserted )
    {
        tmTask.timing_alarmed = &mbedtls_timing_alarmed;
        tmTask.task.tmAddr = NewTimerUPP(timerProc);
        tmTask.task.tmCount = 0;
        InsTime( (QElemPtr)&(tmTask.task) );

        atexit( atexit_func );
        task_inserted = 1;
    }
    mbedtls_timing_alarmed = 0;
    PrimeTime( (QElemPtr)&(tmTask.task), seconds * 1000 );
}

/**
 * \brief          Set a pair of delays to watch
 *                 (See \c mbedtls_timing_get_delay().)
 *
 * \param data     Pointer to timing data
 *                 Must point to a valid \c mbedtls_timing_delay_context struct.
 * \param int_ms   First (intermediate) delay in milliseconds.
 * \param fin_ms   Second (final) delay in milliseconds.
 *                 Pass 0 to cancel the current delay.
 */
void mbedtls_timing_set_delay( void *data, uint32_t int_ms, uint32_t fin_ms )
{
    // TODO: implement
}

/**
 * \brief          Get the status of delays
 *                 (Memory helper: number of delays passed.)
 *
 * \param data     Pointer to timing data
 *                 Must point to a valid \c mbedtls_timing_delay_context struct.
 *
 * \return         -1 if cancelled (fin_ms = 0)
 *                  0 if none of the delays are passed,
 *                  1 if only the intermediate delay is passed,
 *                  2 if the final delay is passed.
 */
int mbedtls_timing_get_delay( void *data )
{
    // TODO: implement
    return 2;
}