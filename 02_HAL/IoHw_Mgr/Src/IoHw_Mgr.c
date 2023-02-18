// Input output hardware manager module
//
// Here can be done the initialization and configuration of the hardware peripherals to use.

#include "02_HAL/IoHw_Mgr/Include/IoHw_Mgr.h"

// Global function to init the GPIOs
void initGPIOs ()
{
  // Digital inputs mode
  IfxPort_setPinMode (PIN22, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN23, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN24, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN25, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN30, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN31, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN32, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN34, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN36, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN38, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN40, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN42, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN44, IfxPort_Mode_inputPullDown);
  IfxPort_setPinMode (PIN46, IfxPort_Mode_inputPullDown);

  // Digital outputs mode
  IfxPort_setPinMode (PIN26, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN28, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN35, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN37, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN39, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN41, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN43, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN45, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN47, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN49, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN51, IfxPort_Mode_outputPushPullGeneral);
  IfxPort_setPinMode (PIN53, IfxPort_Mode_outputPushPullGeneral);

  // Digital outputs initial state
  IfxPort_setPinState (PIN26, IfxPort_State_high);
  IfxPort_setPinState (PIN28, IfxPort_State_low);
  IfxPort_setPinState (PIN35, IfxPort_State_high);
  IfxPort_setPinState (PIN37, IfxPort_State_high);
  IfxPort_setPinState (PIN39, IfxPort_State_high);
  IfxPort_setPinState (PIN41, IfxPort_State_high);
  IfxPort_setPinState (PIN43, IfxPort_State_high);
  IfxPort_setPinState (PIN45, IfxPort_State_high);
  IfxPort_setPinState (PIN47, IfxPort_State_high);
  IfxPort_setPinState (PIN49, IfxPort_State_high);
  IfxPort_setPinState (PIN51, IfxPort_State_high);
  IfxPort_setPinState (PIN53, IfxPort_State_high);

}

