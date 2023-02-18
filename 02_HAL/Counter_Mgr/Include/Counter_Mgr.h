// Counter manager module
//
// This module defines some macros to convert the time base, also some prototypes of the counter manager module.

#ifndef COUNTER_MGR_COUNTER_MGR_H_
#define COUNTER_MGR_COUNTER_MGR_H_

#include "02_HAL/Counter_Mgr/Include/CounterMgr_DataTypes.h"

// Macro to get the clock frequency
#define SOURCE_CLOCK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)
// Macro to convert a microsecond period to raw count value
#define US_TO_COUNT(us, clockFreqInHz) (uint64_t)((uint64_t)us * clockFreqInHz / 1000000U)
// Macro to convert a raw count value to millisecond */
#define MS_TO_COUNT(ms, clockFreqInHz) (uint64_t)((uint64_t)ms * clockFreqInHz / 1000U)

// Exported global functions
void CM_SetUpCounter (unsigned int Time);
void CM_StartCounter (CM_CallbackFunction CallbackFunction);
void CM_StopCounter (CM_CallbackFunction CallbackFunction);
unsigned int CM_GetCounter (void);

#endif
