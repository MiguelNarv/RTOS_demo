// Scheduler module
//
// Here are some top level implementations for the scheduler to use timer, counter, and other modules.

#include "01_MAL/Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/Ifx_Types.h"
#include "02_HAL/IoHw_Mgr/Include/IoHw_Mgr.h"
#include "03_SERVICES/Scheduler/Include/SchM.h"
#include "03_SERVICES/Scheduler/Include/SchM_Types.h"

// Static global variables
static unsigned int OS_Tick = 0;

// Private functions declaration

void SchM_OSTick (void);
void SchM_Background (void);

// Tasks definition
SchM_Tasks TASK [NUMBEROFTASKS];

void SchM_Task_Create (SchM_TaskIDType taskID, SchM_TaskMaskType mask, SchM_TaskOffsetType offset,
    SchM_TaskStateType taskState, void (*callback) (void))
{
  static uint8 i = 0;
  if (i < NUMBEROFTASKS)
  {
    TASK [i].TaskID = taskID;
    TASK [i].TaskMask = mask;
    TASK [i].TaskOffset = offset;
    TASK [i].TaskState = taskState;
    TASK [i].SchM_Task = callback;

    i++;
  }

}

// Public functions definitions
void SchM_Init ()
{

  // Initialize TIME Module
  // This module configures a timer module to trigger an interrupt and increment a counter
  // every 781uS
  TIME_SetUpModule (interruptPeriodInUS);
}

void SchM_Start (void)
{
  // Start the count interrupt based (the period is configured in TIME_SetUpModule)
  TIME_StartModule (&SchM_OSTick);

  // Run the scheduler
  while (TRUE)
  {
    SchM_Background ();
  }
}

void SchM_Stopo (void)
{
  // Stops the isr
  TIME_StopModule (&SchM_OSTick);
}

// Private functions definition
void SchM_OSTick (void)
{
  SchM_TaskIDType x = 0u;

  TIME_SaveTimeCounter (&OS_Tick);

  for (x = SCHM_TASKID_READGPIOS; x <= SCHM_TASKID_IDLE; x++)
  {
    if ((TASK [x].TaskMask & OS_Tick) == TASK [x].TaskOffset)
    {
      TASK [x].TaskState = SCHM_TASK_STATE_READY;
    }
  }
}

void SchM_Background (void)
{
  SchM_TaskIDType x = 0u;

  for (x = SCHM_TASKID_READGPIOS; x <= SCHM_TASKID_IDLE; x++)
  {
    if (TASK [x].TaskState == SCHM_TASK_STATE_READY)
    {
      TASK [x].TaskState = SCHM_TASK_STATE_RUNNING;
      TASK [x].SchM_Task ();
      TASK [x].TaskState = SCHM_TASK_STATE_SUSPENDED;
    }
  }
}
