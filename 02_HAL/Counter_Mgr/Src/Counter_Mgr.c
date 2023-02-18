// Counter manager module
//
// This module initializes and gets the current count based on the ISR interrupt defined on timer module.

#include "02_HAL/Counter_Mgr/Include/Counter_Mgr.h"
#include "01_MAL/Common_Drivers/Service/CpuGeneric/SysSe/Bsp/Bsp.h"
#include "01_MAL/TIM_Drivers/Include/IfxStm.h"

// Static global variables
static CM_CallbackFunction Callback;
static IfxStm_CompareConfig g_STMConf;  // STM configuration structure
static Ifx_TickTime g_ticksFor1us;      // Variable to store the number of ticks to wait
static volatile unsigned int CounterVal = 0;

#define ISR_PRIORITY_STM        40                              //Priority for interrupt ISR
#define STM                     &MODULE_STM0                    // STM0 is used

IFX_INTERRUPT(isrSTM, 0, ISR_PRIORITY_STM);

// SetUp Counter Module

// The the timer will expire every Time
void CM_SetUpCounter (unsigned int Time)
{
  g_ticksFor1us = IfxStm_getTicksFromMicroseconds (BSP_DEFAULT_TIMER, Time);

  IfxStm_initCompareConfig (&g_STMConf); // Initialize the configuration structure with default values

  g_STMConf.triggerPriority = ISR_PRIORITY_STM; // Set the priority of the interrupt
  g_STMConf.typeOfService = IfxSrc_Tos_cpu0;    // Set the service provider for the interrupts
  g_STMConf.ticks = (uint32) g_ticksFor1us;

}

// Start (Periodic Interrupt Timer) Module
void CM_StartCounter (CM_CallbackFunction CallbackFunction)
{
  Callback = CallbackFunction;
  IfxStm_initCompare (STM, &g_STMConf);
}

// Stops (Periodic Interrupt Timer) Module
void CM_StopCounter (CM_CallbackFunction CallbackFunction)
{
  Callback = CallbackFunction;
  // TODO Stop counter implementation
}

// Get Counter Value
unsigned int CM_GetCounter (void)
{
  return CounterVal;
}

//ISR Function
void isrSTM (void)
{
  // Clear the STM status flag
  IfxStm_increaseCompare (STM, g_STMConf.comparator, (uint32) g_ticksFor1us);

  // Count increase
  CounterVal++;

  // Call the callback
  Callback ();
}

