#include "01_MAL/Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/IfxCpu.h"
#include "01_MAL/Common_Drivers/iLLD/TC27D/Tricore/Scu/Std/IfxScuWdt.h"
#include "02_HAL/IoHw_Mgr/Include/IoHw_Mgr.h"
#include "02_HAL/PWM_Mgr/Include/PWM_Mgr.h"
#include "02_HAL/CAN_Mgr/Include/CAN_Mgr.h"
#include "03_SERVICES/Scheduler/Include/SchM.h"
#include "03_SERVICES/Data_Transfer/Include/Data_Transfer.h"
#include "03_SERVICES/ADC_Read/Include/ADC_Single_Channel.h"
#include "04_APPLICATION/Tasks/Include/App_Tasks.h"
#include "04_APPLICATION/DCU/Include/DCU_Window_GPIO_Unit.h"
#include "04_APPLICATION/DCU/Include/LongShortPressUnit.h"
#include "04_APPLICATION/DCU/Include/WindowControl.h"
#include "CAN_Unit.h"
#include "CAN_Mgr.h"
#include "doorLockStatusUnitDCU.h"
#include "LockLEDUnit.h"


IfxCpu_syncEvent g_cpuSyncEvent = 0;

void initSystem (void);

int core0_main (void)
{
  // Enable interrupts
  IfxCpu_enableInterrupts ();

  IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());
  IfxScuWdt_disableSafetyWatchdog (IfxScuWdt_getSafetyWatchdogPassword ());

  // Wait for CPU sync event
  IfxCpu_emitEvent (&g_cpuSyncEvent);
  IfxCpu_waitEvent (&g_cpuSyncEvent, 1);

  initSystem ();

  return (1);
}

void initSystem (void)
{
  // Initialize GPIO module
  initGPIOs ();
  // Initialize data transfer vectors
  initDataStruct ();
  //Init vector used un GPIO
  Init_window_vectors();
  Init_Vector_ls ();
  //Init variables for window
  InitVariables();
  // Initialize ADC
  vadcBackgroundScanInit ();
  vadcBackgroundScanRun ();
  // Initalize CAN
  initMultican();
  // Initialize PWM
  initPWM ();
  // Configure PWM pins
  configPwm (0, PWM2);
  configPwm (1, PWM3);
  configPwm (2, PWM4);
  configPwm (3, PWM5);
  configPwm (4, PWM6);
  configPwm (5, PWM7);
  configPwm (6, PWM8);

  // ---->>>>>>> init IDs
  initIDs(1);

  // Initialize tasks module
  TaskInit ();
  // Set scheduler parameters
  SchM_Init ();
  // Start the scheduler
  SchM_Start ();
}
