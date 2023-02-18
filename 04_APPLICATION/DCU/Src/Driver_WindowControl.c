/*
 * Driver_WindowControl.c
 *
 *  Created on: 12 oct. 2022
 *      Author: uif36103
 */
#include "04_APPLICATION/DCU/Include/WindowControl.h"

#include <stdio.h>
//GENERAL INPUTS

windowState1 driver_state;

//Internal Signals
//uint8 d_inactive_up;
//uint8 d_inactive_down;
//uint8 p_inactive_up;
//uint8 p_inactive_down;
//uint8 rl_inactive_up;
//uint8 rl_inactive_down;
//uint8 rr_inactive_up;
//uint8 rr_inactive_down;
uint8 Flag_AN = 0;


/////////////////////////////////////////////DRIVER FUNCTIONS///////////////////////////////////////////////////////////todo

void Check_Driver_Window_Control_Unit ()
{
  switch (driver_state)
  {
    case DriverVerifyID :
      Check_DriverVerifyID_func();
      break;

    case DriverWindowLocked :
      Check_DriverWindowLocked_func();
      break;
    case DriverAutomaticOpen :
      Check_DriverAutomaticOpen_func();
      break;
    case DriverAutomaticClose :
      Check_DriverAutomaticClose_func();
      break;
    case DriverNoDeviceConnected :
      Check_DriverNoDeviceConnected_func();
      break;
    default :// Only for QAC
      break;
  }
}



void Check_DriverVerifyID_func ()
{
  if (FSM_Data_DCU.dataVector[31] == 0x00)
  {
    driver_state = DriverWindowLocked;
  }
  else
  {
    driver_state = DriverNoDeviceConnected;
    //driver_state = DriverVerifyID;
  }
}

void Check_DriverNoDeviceConnected_func ()
{
  //IfxPort_setPinMode(Entrada del boton, IfxPort_Mode_inputNoPullDevice);
}

void Check_DriverWindowLocked_func ()
{
  if (FSM_Data_DCU.dataVector[W_LOCK] == 1)
  {
    Cancel_Window_Actuation();
    FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowLocked;
    driver_state = DriverWindowLocked;
    FSM_Data_DCU.dataVector[D_W_DOWN] = 0;
    FSM_Data_DCU.dataVector[D_W_UP] = 0;
  }
  else
  {

    if ((FSM_Data_DCU.dataVector[Driver_W_UP] == 0 && FSM_Data_DCU.dataVector[Driver_W_DOWN] == 0)
        || (FSM_Data_DCU.dataVector[Driver_W_UP] == 1 && FSM_Data_DCU.dataVector[Driver_W_DOWN] == 1))
    {
      Cancel_Window_Actuation();
      driver_state = DriverWindowLocked;
    }
    else
    {
      if(FSM_Data_DCU.dataVector[D_W_DOWN] == buttonStuck && FSM_Data_DCU.dataVector[D_W_UP] == shortpressRequest
      && FSM_Data_DCU.dataVector[Driver_W_UP] == 0 && FSM_Data_DCU.dataVector[Driver_W_DOWN] == 0)
      {
        driver_state = DriverAutomaticClose;
        FSM_Data_DCU.dataVector[D_W_UP] = 0;
      }
      else if(FSM_Data_DCU.dataVector[D_W_UP] == buttonStuck && FSM_Data_DCU.dataVector[D_W_DOWN] == shortpressRequest
          && FSM_Data_DCU.dataVector[Driver_W_DOWN] == 0 && FSM_Data_DCU.dataVector[Driver_W_UP] == 0)
      {
        driver_state = DriverAutomaticOpen;
        FSM_Data_DCU.dataVector[D_W_DOWN] = 0;
      }
    }
    if (FSM_Data_DCU.dataVector[Driver_W_DOWN] == 0 &&
         FSM_Data_DCU.dataVector[Driver_W_UP] == 0 &&
         FSM_Data_DCU.dataVector[D_W_DOWN] == shortpressRequest &&
         FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open )
    {
      driver_state = DriverAutomaticOpen;
      FSM_Data_DCU.dataVector[D_W_DOWN] = 0;
    }
    else if (FSM_Data_DCU.dataVector[D_W_UP] == shortpressRequest && FSM_Data_DCU.dataVector[Driver_W_UP] == 0
        && FSM_Data_DCU.dataVector[Driver_W_DOWN] == 0 && FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close)
    {
      driver_state = DriverAutomaticClose;
      FSM_Data_DCU.dataVector[D_W_UP] = 0;
    }
    else if (FSM_Data_DCU.dataVector[D_W_UP] == longpressRequest && FSM_Data_DCU.dataVector[Driver_W_UP] == 1
        && FSM_Data_DCU.dataVector[Driver_W_DOWN] == 0 && FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close)
    {
      Close_Window_Actuation();
      driver_state = DriverWindowLocked;
      FSM_Data_DCU.dataVector[D_W_UP] = 0;
    }
    else if (FSM_Data_DCU.dataVector[Driver_W_UP] == windowButton_idle
        && FSM_Data_DCU.dataVector[D_W_DOWN] == longpressRequest && FSM_Data_DCU.dataVector[Driver_W_DOWN] == 1
        && FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open)
    {
      Open_Window_Actuation();
      driver_state = DriverWindowLocked;
      FSM_Data_DCU.dataVector[D_W_DOWN] = 0;
    }
    else
    {
      // Only for QAC
    }
  }
}

void Check_DriverAutomaticOpen_func ()
{

  if (FSM_Data_DCU.dataVector[W_LOCK] == 1)
  {
    Cancel_Window_Actuation();
    FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowLocked;
    driver_state = DriverWindowLocked;
  }
  else if (FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open && FSM_Data_DCU.dataVector[W_LOCK] == 0)
  {
    if (FSM_Data_DCU.dataVector[A_PINCH_S] == 1 || Flag_AN ==1)
    {
      Open_Window_Actuation();
      FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
      FSM_Data_DCU.dataVector[D_W_UP] = 0;
      driver_state = DriverAutomaticOpen;
    }
    else if (FSM_Data_DCU.dataVector[D_W_UP] == shortpressRequest &&
             FSM_Data_DCU.dataVector[Driver_W_UP] == 0 &&
             FSM_Data_DCU.dataVector[Driver_W_DOWN] == 0 &&
             FSM_Data_DCU.dataVector[A_PINCH_S] == 0)
    {
      Close_Window_Actuation();
      FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
      FSM_Data_DCU.dataVector[D_W_DOWN] = 0;
      driver_state = DriverAutomaticClose;
    }
    else if (FSM_Data_DCU.dataVector[D_W_UP] == longpressRequest &&
             FSM_Data_DCU.dataVector[Driver_W_DOWN] == 0 &&
             FSM_Data_DCU.dataVector[Driver_W_UP] == 1 &&
             FSM_Data_DCU.dataVector[A_PINCH_S] == 0)
    {
      Close_Window_Actuation();
      FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
      FSM_Data_DCU.dataVector[D_W_DOWN] = 0;
      driver_state = DriverWindowLocked;
    }
    else if ((FSM_Data_DCU.dataVector[Driver_W_UP] == 1 && FSM_Data_DCU.dataVector[Driver_W_DOWN] == 1)
        || FSM_Data_DCU.dataVector[D_W_UP] == buttonStuck)
    {
      Cancel_Window_Actuation();
      FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
      driver_state = DriverWindowLocked;
      FSM_Data_DCU.dataVector[D_W_DOWN] = 0;
    }
    else
    {
      if(FSM_Data_DCU.dataVector[A_PINCH_S] == 0)
      {
      Open_Window_Actuation();
      FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
      driver_state = DriverAutomaticOpen;
      }
      else
      {

      }
    }
  }
  else if (FSM_Data_DCU.dataVector[W_LOCK] == 0 && FSM_Data_DCU.dataVector[WINDOW_ST] == d_c_open)
  {
    Cancel_Window_Actuation();
    FSM_Data_DCU.dataVector[D_W_DOWN] = 0;
    FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
    driver_state = DriverWindowLocked;
    Flag_AN = 0;
  }
  else
  {
    Cancel_Window_Actuation();
    FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
    driver_state = DriverWindowLocked;
  }
}

void Check_DriverAutomaticClose_func ()
{
  if (FSM_Data_DCU.dataVector[W_LOCK] == 1)
  {
    Cancel_Window_Actuation();
    FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowLocked;
    driver_state = DriverWindowLocked;
  }
  else if (FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close && FSM_Data_DCU.dataVector[W_LOCK] == 0)
  {
    if (FSM_Data_DCU.dataVector[A_PINCH_S] == 1)
    {
      Cancel_Window_Actuation();
      FSM_Data_DCU.dataVector[D_W_UP] = 0;
      FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
      driver_state = DriverAutomaticOpen;
      Flag_AN = 1;
    }
    else if (FSM_Data_DCU.dataVector[D_W_DOWN] == shortpressRequest &&
             FSM_Data_DCU.dataVector[Driver_W_UP] == 0 &&
             FSM_Data_DCU.dataVector[Driver_W_DOWN] == 0)  ///todo check if its necessary Driver_W_Down = 0
    {
      Open_Window_Actuation();
      FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
      FSM_Data_DCU.dataVector[D_W_UP] = 0;
      driver_state = DriverAutomaticOpen;
    }
    else if (FSM_Data_DCU.dataVector[D_W_DOWN] == longpressRequest &&
             FSM_Data_DCU.dataVector[Driver_W_UP] == 0 &&
             FSM_Data_DCU.dataVector[Driver_W_DOWN] == 1)
    {
      Open_Window_Actuation();
      FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
      FSM_Data_DCU.dataVector[D_W_UP] = 0;
      driver_state = DriverWindowLocked;
    }
    else if ((FSM_Data_DCU.dataVector[Driver_W_UP] == 1 && FSM_Data_DCU.dataVector[Driver_W_DOWN] == 1)
        || (FSM_Data_DCU.dataVector[D_W_UP] == buttonStuck))
    {
      Cancel_Window_Actuation();
      FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
      driver_state = DriverWindowLocked;
    }
    else
    {
      Close_Window_Actuation();
      FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
      driver_state = DriverAutomaticClose;
      FSM_Data_DCU.dataVector[D_W_UP] = 0;

    }
  }
  else if (FSM_Data_DCU.dataVector[W_LOCK] == 0 && FSM_Data_DCU.dataVector[WINDOW_ST] == d_c_close)
  {
    Cancel_Window_Actuation();
    FSM_Data_DCU.dataVector[D_W_UP] = 0;
    FSM_Data_DCU.dataVector[W_LOCK_CMD] = windowUnlocked;
    driver_state = DriverWindowLocked;
  }
  else
  {
    //Only for QAC
  }
}


/////////////////////////////////////////////INIT FUNCTIONS///////////////////////////////////////////////////////////
void InitVariables()
{
  //GENERAL OUPUTS
  driver_state     = DriverVerifyID;
  InitPassengerWindow();
  InitRearLeftWindow();
  InitRearRightWindow();
  //passenger_state = PassengerVerifyID;


//  //Internal Signals
//  d_inactive_up           = 0;
//  d_inactive_down         = 0;
//  flag_antipinch =0;
}

/////////////////////////////////////////Execute functions///////////////////////////////////////////////////////////
void Cancel_Window_Actuation ()
{
    FSM_Data_DCU.dataVector[WINDOW_POS] = FSM_Data_DCU.dataVector[WINDOW_ST];
    FSM_Data_DCU.dataVector[WINDOW_OP]  = d_idle;
    FSM_Data_DCU.dataVector[ACT_WINDOW] = no_moving;
}

void Open_Window_Actuation ()
{
      FSM_Data_DCU.dataVector[WINDOW_POS] = FSM_Data_DCU.dataVector[WINDOW_ST];
      FSM_Data_DCU.dataVector[WINDOW_OP] = d_down;
      FSM_Data_DCU.dataVector[ACT_WINDOW] = window_down;
}

void Close_Window_Actuation ()
{
      FSM_Data_DCU.dataVector[WINDOW_POS] = FSM_Data_DCU.dataVector[WINDOW_ST];
      FSM_Data_DCU.dataVector[WINDOW_OP] = d_up;
      FSM_Data_DCU.dataVector[ACT_WINDOW] = window_up;
}



