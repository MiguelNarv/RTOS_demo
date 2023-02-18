// Time manager data types module
//
// Time structure and interrupt period definition.

#ifndef TIME_MGR_TIMEMGR_DATATYPES_H_
#define TIME_MGR_TIMEMGR_DATATYPES_H_

#include "01_MAL/Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/Platform_Types.h"

// Time base selected for the tasks execution
#define interruptPeriodInUS 1000U

typedef struct t_TIME_UNITS
{
    char TimeUnit;         // Index of the time unit [TimeUnit0, TimeUnit1, ...]
    unsigned int CounterVal;       // Last value counter
    unsigned int TimeSinceCounter; // Last time value
    boolean InitStatus;       // Status of the time unit, is Initialized? [true. false]
} TIME_UNITS;

typedef void (*TM_CallbackFunction) (void);

typedef unsigned int TimeInMicroseconds;

#endif
