/*
 * RearLeftWindowControl.c
 *
 *  Created on: 12 oct. 2022
 *      Author: uif36103
 */
#include "04_APPLICATION/DCU/Include/WindowControl.h"
#include <stdio.h>
//GENERAL INPUTS
windowState4 rl_state;



///////////////////////////////////////////////REARLEFT FUNCTIONS/////////////////////////////////////////////todo

void RearLeft_Window_Control_Unit ()
{
  switch (rl_state)
  {
    case RearLeftVerifyID :
      RearLeftVerifyID_func();
      break;
    case RearLeft_Driver_State :
      RearLeft_Driver_State_func();
      break;
    case RearLeftWindowLocked :
      RearLeftWindowLocked_func();
      break;
    case RearLeftNoDeviceConnected :
      RearLeftNoDeviceConnected_func();
      break;
    default :// Only for QAC
      break;
  }
}

void RearLeftVerifyID_func ()
{
  if (FSM_Data_DCU.dataVector[31] == 0x02)
  {
    rl_state = RearLeftWindowLocked;
  }
  else if(FSM_Data_DCU.dataVector[31] == 0x00)
  {
    rl_state = RearLeft_Driver_State;
  }
  else
  {
    rl_state = RearLeftNoDeviceConnected;
    //driver_state = DriverVerifyID;
  }
}

void RearLeftNoDeviceConnected_func ()
{
  //IfxPort_setPinMode(Entrada del boton, IfxPort_Mode_inputNoPullDevice);
}

void RearLeftWindowLocked_func ()
{
  if (FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 1)
  {
    Cancel_Window_Actuation ();
    rl_state = RearLeftWindowLocked;
  }
  else
  {
    if ((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & RL_MASK4) == windowNo_req||
        (FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & RL_MASK4) == RL_MASK4)
    {

      if ((FSM_Data_DCU.dataVector[REARLEFT_W_UP] == 0 && FSM_Data_DCU.dataVector[REARLEFT_W_DOWN] == 0)
       || (FSM_Data_DCU.dataVector[REARLEFT_W_UP] == 1 && FSM_Data_DCU.dataVector[REARLEFT_W_DOWN] == 1))
      {
        Cancel_Window_Actuation ();
        rl_state = RearLeftWindowLocked;
      }
      else
      {

      }
      if ( FSM_Data_DCU.dataVector[RL_W_UP] == longpressRequest &&
           FSM_Data_DCU.dataVector[REARLEFT_W_DOWN] == 0 && FSM_Data_DCU.dataVector[REARLEFT_W_UP] == 1 &&
           FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close)
      {
        Close_Window_Actuation();
        rl_state = RearLeftWindowLocked;
        FSM_Data_DCU.dataVector[RL_W_UP] = 0;
      }
      else if (FSM_Data_DCU.dataVector[REARLEFT_W_UP] == 0 && FSM_Data_DCU.dataVector[REARLEFT_W_DOWN] == 1 &&
               FSM_Data_DCU.dataVector[RL_W_DOWN] == longpressRequest &&
               FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open)
      {
        Open_Window_Actuation();
        rl_state = RearLeftWindowLocked;
        FSM_Data_DCU.dataVector[RL_W_DOWN] = 0;
      }
      else
      {
        // Only for QAC
      }
    }
    else if((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & RL_MASK4) == RL_MASK3 && FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close)
    {
      Close_Window_Actuation();
      rl_state = RearLeftWindowLocked;
      FSM_Data_DCU.dataVector[RL_W_UP] = 0;
    }
    else if ((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & RL_MASK4) == RL_MASK2 && FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open)
    {
      Open_Window_Actuation();
      rl_state = RearLeftWindowLocked;
      FSM_Data_DCU.dataVector[RL_W_DOWN] = 0;
    }
    else
    {
      // Only for QAC
    }
  }
}




void RearLeft_Driver_State_func ()
{
  if (FSM_Data_DCU.dataVector[W_LOCK] == 0)
  {
    if ((FSM_Data_DCU.dataVector[RL_W_DOWN] == shortpressRequest || FSM_Data_DCU.dataVector[RL_W_DOWN] == longpressRequest)
        && FSM_Data_DCU.dataVector[REARLEFT_W_UP] == 0 && FSM_Data_DCU.dataVector[REARLEFT_W_DOWN] == 1)
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = ((FSM_Data_DCU.dataVector[W_CONTROL]) & RL_MASK1)
          | RL_MASK2;
    }
    else if ((FSM_Data_DCU.dataVector[RL_W_UP] == shortpressRequest || FSM_Data_DCU.dataVector[RL_W_UP] == longpressRequest)
        && FSM_Data_DCU.dataVector[REARLEFT_W_DOWN] == 0 && FSM_Data_DCU.dataVector[REARLEFT_W_UP] == 1)
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = ((FSM_Data_DCU.dataVector[W_CONTROL]) & RL_MASK1)
          | RL_MASK3;
    }
    else if ((FSM_Data_DCU.dataVector[REARLEFT_W_UP] == 0 || FSM_Data_DCU.dataVector[REARLEFT_W_DOWN] == 0)
        && (FSM_Data_DCU.dataVector[REARLEFT_W_UP] == 1 || FSM_Data_DCU.dataVector[REARLEFT_W_DOWN] == 1))
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = (FSM_Data_DCU.dataVector[W_CONTROL]) & RL_MASK1;
    }
    else
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = (FSM_Data_DCU.dataVector[W_CONTROL]) & RL_MASK1;
    }
  }
  else if (FSM_Data_DCU.dataVector[W_LOCK] == 1)
  {
    FSM_Data_DCU.dataVector[W_CONTROL] = (FSM_Data_DCU.dataVector[W_CONTROL]) & RL_MASK1;
  }
  else
  {

  }
}


void InitRearLeftWindow()
{
  rl_state = RearLeftVerifyID;
}



