// Scheduler tasks module
//
// Here can be implemented the task routine to execute.
#include "02_HAL/IoHw_Mgr/Include/IoHW_Mgr.h"
#include "03_SERVICES/Time_Mgr/Include/Time_Mgr.h"
#include "03_SERVICES/Queuer/Include/Queuer.h"
#include "03_SERVICES/Scheduler/Include/SchM.h"
#include "04_APPLICATION/Tasks/Include/App_Tasks.h"
#include "04_APPLICATION/DCU/Include/DCU_Window_GPIO_Unit.h"
#include "04_APPLICATION/DCU/Include/LongShortPressUnit.h"
#include "04_APPLICATION/DCU/Include/WindowControl.h"
#include "04_APPLICATION/DCU/Include/Window_Actuation_Unit.h"
#include "CAN_Unit.h"
#include "doorLockStatusUnitDCU.h"
#include "LockLEDUnit.h"
#include "DCU_Window_GPIO_Unit.h"

// Local variable for task complete execution.
static volatile unsigned int uno = 0;
static volatile unsigned int dos = 0;
static volatile unsigned int tres = 0;
static volatile unsigned int cuatro = 0;
static volatile float timeLapse = 0;

void SchM_ReadGPIOs_Task (void)
{
  uno++;
  Btn_Unit();
  longShortpress_func();
  readFrames();
}

void SchM_Processing_Task (void)
{
  dos++;
  Check_Driver_Window_Control_Unit ();
  Passenger_Window_Control_Unit ();
  RearLeft_Window_Control_Unit ();
  RearRight_Window_Control_Unit ();
  DLSU();
}
void SchM_Executing_Task (void)
{
  tres++;
  Window_Act_Unit();
  LLUState();
  sendFrame(1);
}
void SchM_Idle_Task (void)
{
  cuatro++;

  // Return the time since channel started in milliseconds.
  timeLapse = TIME_GetTimeSinceChannelStarted (0u);

  // Restart the execution of the tasks.
  TIME_StopChannel (0u);
  TIME_StartChannel (0u);

}

void TaskInit (void)
{
  SchM_Task_Create (SCHM_TASKID_READGPIOS, SCHM_MASK_READGPIOS, SCHM_OFFSET_READGPIOS, SCHM_TASK_STATE_SUSPENDED,
      SchM_ReadGPIOs_Task);
  SchM_Task_Create (SCHM_TASKID_PROCESSING, SCHM_MASK_PROCESSING, SCHM_OFFSET_PROCESSING, SCHM_TASK_STATE_SUSPENDED,
      SchM_Processing_Task);
  SchM_Task_Create (SCHM_TASKID_EXECUTING, SCHM_MASK_EXECUTING, SCHM_OFFSET_EXECUTING, SCHM_TASK_STATE_SUSPENDED,
      SchM_Executing_Task);
  SchM_Task_Create (SCHM_TASKID_IDLE, SCHM_MASK_IDLE, SCHM_OFFSET_IDLE, SCHM_TASK_STATE_SUSPENDED, SchM_Idle_Task);
}
