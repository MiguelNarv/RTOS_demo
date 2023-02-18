// Time manager module
//
// Time global prototypes.

#ifndef TIME_MGR_TIME_MGR_H_
#define TIME_MGR_TIME_MGR_H_

#include "03_SERVICES/Time_Mgr/Include/TimeMgr_DataTypes.h"

// Initialized by scheduler
void TIME_SetUpModule (TimeInMicroseconds Time);
void TIME_StartModule (TM_CallbackFunction CallbackFunction);
void TIME_StopModule (TM_CallbackFunction CallbackFunction);

// Used by scheduler
void TIME_SaveTimeCounter (unsigned int* const counterTime);

// General purpose for measure time lapse
void TIME_StartChannel (unsigned short TimeChannel);
void TIME_StopChannel (unsigned short Channel);
float TIME_GetTimeSinceChannelStarted (unsigned short Channel);

#endif /* TIME_MGR_TIME_MGR_H_ */
