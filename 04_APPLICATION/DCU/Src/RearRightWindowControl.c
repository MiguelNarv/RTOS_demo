/*
 * RearRightWindowControl.c
 *
 *  Created on: 12 oct. 2022
 *      Author: uif36103
 */
#include "04_APPLICATION/DCU/Include/WindowControl.h"
#include <stdio.h>
//GENERAL INPUTS
windowState3 rr_state;



///////////////////////////////////////////////REARRIGHT FUNCTIONS/////////////////////////////////////////////todo

void RearRight_Window_Control_Unit ()
{
  switch (rr_state)
  {
    case RearRightVerifyID :
      RearRightVerifyID_func();
      break;
    case RearRight_Driver_State :
      RearRight_Driver_State_func();
      break;
    case RearRightWindowLocked :
      RearRightWindowLocked_func();
      break;
    case RearRightNoDeviceConnected :
      RearRightNoDeviceConnected_func();
      break;
    default :// Only for QAC
      break;
  }
}

void RearRightVerifyID_func ()
{
  if (FSM_Data_DCU.dataVector[31] == 0x03)
  {
    rr_state = RearRightWindowLocked;
  }
  else if(FSM_Data_DCU.dataVector[31] == 0x00)
  {
    rr_state = RearRight_Driver_State;
  }
  else
  {
    rr_state = RearRightNoDeviceConnected;
    //driver_state = DriverVerifyID;
  }
}

void RearRightNoDeviceConnected_func ()
{
  //IfxPort_setPinMode(Entrada del boton, IfxPort_Mode_inputNoPullDevice);
}

void RearRightWindowLocked_func ()
{
  if (FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 1)
  {
    Cancel_Window_Actuation ();
    rr_state = RearRightWindowLocked;
  }
  else
  {
    if ((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & RR_MASK4) == windowNo_req||
        (FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & RR_MASK4) == RR_MASK4)
    {

      if ((FSM_Data_DCU.dataVector[REARRIGHT_W_UP] == 0 && FSM_Data_DCU.dataVector[REARRIGHT_W_DOWN] == 0)
       || (FSM_Data_DCU.dataVector[REARRIGHT_W_UP] == 1 && FSM_Data_DCU.dataVector[REARRIGHT_W_DOWN] == 1))
      {
        Cancel_Window_Actuation ();
        rr_state = RearRightWindowLocked;
      }
      else
      {

      }
      if ((FSM_Data_DCU.dataVector[RR_W_UP] == longpressRequest || FSM_Data_DCU.dataVector[RR_W_UP] == shortpressRequest) &&
           FSM_Data_DCU.dataVector[REARRIGHT_W_DOWN] == 0 &&
           FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close)
      {
        Close_Window_Actuation();
        rr_state = RearRightWindowLocked;
        FSM_Data_DCU.dataVector[RR_W_UP] = 0;
      }
      else if (FSM_Data_DCU.dataVector[REARRIGHT_W_UP] == 0 &&
              (FSM_Data_DCU.dataVector[RR_W_DOWN] == shortpressRequest || FSM_Data_DCU.dataVector[RR_W_DOWN] == longpressRequest) &&
               FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open)
      {
        Open_Window_Actuation();
        rr_state = RearRightWindowLocked;
        FSM_Data_DCU.dataVector[RR_W_DOWN] = 0;
      }
      else
      {
        // Only for QAC
      }
    }
    else if((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & RR_MASK4) == RR_MASK3 && FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close)
    {
      Close_Window_Actuation();
      rr_state = RearRightWindowLocked;
      FSM_Data_DCU.dataVector[RR_W_UP] = 0;
    }
    else if ((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & RR_MASK4) == RR_MASK2 && FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open)
    {
      Open_Window_Actuation();
      rr_state = RearRightWindowLocked;
      FSM_Data_DCU.dataVector[RR_W_DOWN] = 0;
    }
    else
    {
      // Only for QAC
    }
  }
}




void RearRight_Driver_State_func ()
{
  if (FSM_Data_DCU.dataVector[W_LOCK] == 0)
  {
    if ((FSM_Data_DCU.dataVector[RR_W_DOWN] == shortpressRequest || FSM_Data_DCU.dataVector[RR_W_DOWN] == longpressRequest)
      && FSM_Data_DCU.dataVector[REARRIGHT_W_UP] == 0 && FSM_Data_DCU.dataVector[REARRIGHT_W_DOWN] == 1)
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = ((FSM_Data_DCU.dataVector[W_CONTROL]) & RR_MASK1)
          | RR_MASK2;
    }
    else if ((FSM_Data_DCU.dataVector[RR_W_UP] == shortpressRequest || FSM_Data_DCU.dataVector[RR_W_UP] == longpressRequest)
           && FSM_Data_DCU.dataVector[REARRIGHT_W_DOWN] == 0 && FSM_Data_DCU.dataVector[REARRIGHT_W_UP] == 1)
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = ((FSM_Data_DCU.dataVector[W_CONTROL]) & RR_MASK1)
          | RR_MASK3;
    }
    else if ((FSM_Data_DCU.dataVector[REARRIGHT_W_UP] == 0 || FSM_Data_DCU.dataVector[REARRIGHT_W_DOWN] == 0)
          && (FSM_Data_DCU.dataVector[REARRIGHT_W_UP] == 1 || FSM_Data_DCU.dataVector[REARRIGHT_W_DOWN] == 1))
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = (FSM_Data_DCU.dataVector[W_CONTROL]) & RR_MASK1;
    }
    else
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = (FSM_Data_DCU.dataVector[W_CONTROL]) & RR_MASK1;
    }
  }
  else if (FSM_Data_DCU.dataVector[W_LOCK] == 1)
  {
    FSM_Data_DCU.dataVector[W_CONTROL] = (FSM_Data_DCU.dataVector[W_CONTROL]) & RR_MASK1;
  }
  else
  {

  }
}

void InitRearRightWindow()
{
  rr_state = RearRightVerifyID;
}



