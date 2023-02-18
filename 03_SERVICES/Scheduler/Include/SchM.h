// Scheduler module
//
// Number of tasks and channel config and init prototypes

#ifndef SCHEDULER_SCHM_H_
#define SCHEDULER_SCHM_H_

#include "03_SERVICES/Time_Mgr/Include/Time_Mgr.h"
#include "03_SERVICES/Scheduler/Include/SchM_Types.h"
#include "03_SERVICES/Queuer/Include/Queuer_Types.h"

#define Channel_01    0u
#define NUMBEROFTASKS  6u

void SchM_Init (void);
void SchM_Start (void);
void SchM_Stopo (void);

void SchM_Task_Create (SchM_TaskIDType taskID, SchM_TaskMaskType mask, SchM_TaskOffsetType offset,
    SchM_TaskStateType taskState, void (*callback) (void));

#endif
