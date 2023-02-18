/*
 * Passenger_WindowControl.c
 *
 *  Created on: 12 oct. 2022
 *      Author: uif36103
 */

#include "04_APPLICATION/DCU/Include/WindowControl.h"
#include <stdio.h>
//GENERAL INPUTS
windowState2 passenger_state;
uint8 Flag_AN2 = 0;


///////////////////////////////////////////////PASSENGER FUNCTIONS///////////////////////////////////////////////////////////TODO

void Passenger_Window_Control_Unit ()
{
  switch (passenger_state)
  {
    case PassengerVerifyID :
      PassengerVerifyID_func();
      break;
    case Passenger_Driver_State :
      Passenger_Driver_State_func();
      break;
    case PassengerWindowLocked :
      PassengerWindowLocked_func();
      break;
    case PassengerAutomaticOpen :
      PassengerAutomaticOpen_func();
      break;
    case PassengerAutomaticClose :
      PassengerAutomaticClose_func();
      break;
    case PassengerNoDeviceConnected :
      PassengerNoDeviceConnected_func();
      break;
    default :// Only for QAC
      break;
  }
}


void PassengerVerifyID_func ()
{
  if (FSM_Data_DCU.dataVector[31] == 0x01)
  {
    passenger_state = PassengerWindowLocked;
  }
  else if(FSM_Data_DCU.dataVector[31] == 0x00)
  {
    passenger_state = Passenger_Driver_State;
  }
  else
  {
    passenger_state = PassengerNoDeviceConnected;
  }
}



void PassengerNoDeviceConnected_func ()
{
  //IfxPort_setPinMode(Entrada del boton, IfxPort_Mode_inputNoPullDevice);
}



void PassengerWindowLocked_func ()
{
  if (FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 1)
  {
    Cancel_Window_Actuation();
    passenger_state = PassengerWindowLocked;
    FSM_Data_DCU.dataVector[P_W_DOWN] = 0;
    FSM_Data_DCU.dataVector[P_W_UP] = 0;

  }
  else
  {
    if ((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & PASS_MASK4) == windowNo_req||
        (FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & PASS_MASK4) == PASS_MASK4)
    {

      if ((FSM_Data_DCU.dataVector[Passenger_W_UP] == 0 && FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 0)
          || (FSM_Data_DCU.dataVector[Passenger_W_UP] == 1 && FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 1))
      {
        Cancel_Window_Actuation();
        passenger_state = PassengerWindowLocked;
      }
      else
      {

      }
      if (FSM_Data_DCU.dataVector[P_W_DOWN] == shortpressRequest &&
          FSM_Data_DCU.dataVector[Passenger_W_UP] == 0 &&
          FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 0 &&
          FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open)
      {
        passenger_state = PassengerAutomaticOpen;
        FSM_Data_DCU.dataVector[P_W_DOWN] = 0;

      }
      else if (FSM_Data_DCU.dataVector[P_W_UP] == shortpressRequest &&
               FSM_Data_DCU.dataVector[P_W_DOWN] == 0 &&
               FSM_Data_DCU.dataVector[Passenger_W_UP] == 0 &&
               FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close)
      {
        passenger_state = PassengerAutomaticClose;
        FSM_Data_DCU.dataVector[P_W_UP] = 0;
      }
      else if (FSM_Data_DCU.dataVector[P_W_UP] == longpressRequest && FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 0
            && FSM_Data_DCU.dataVector[Passenger_W_UP] == 1 && FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close)
      {
        Close_Window_Actuation();
        passenger_state = PassengerWindowLocked;
        FSM_Data_DCU.dataVector[P_W_UP] = 0;
      }
      else if (FSM_Data_DCU.dataVector[Passenger_W_UP] == 0 && FSM_Data_DCU.dataVector[P_W_DOWN] == longpressRequest &&
               FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 1 && FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open)
      {
        Open_Window_Actuation();
        passenger_state = PassengerWindowLocked;
        FSM_Data_DCU.dataVector[P_W_DOWN] = 0;
      }
      else
      {
        // Only for QAC
      }
    }
    else if((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & PASS_MASK4) == PASS_MASK3)
    {
      Close_Window_Actuation();
      passenger_state = PassengerWindowLocked;
      FSM_Data_DCU.dataVector[P_W_UP] = 0;
    }
    else if ((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & PASS_MASK4) == PASS_MASK2)
    {
      Open_Window_Actuation();
      passenger_state = PassengerWindowLocked;
      FSM_Data_DCU.dataVector[P_W_DOWN] = 0;
    }
    else
    {
      // Only for QAC
    }
  }
}

void PassengerAutomaticOpen_func ()
{
  if (FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 1)
  {
    Cancel_Window_Actuation ();
    passenger_state = PassengerWindowLocked;
  }
  else if (FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open && FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 0 &&
         ((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & PASS_MASK4) == 0 || (FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & PASS_MASK4)== PASS_MASK4))
  {

    if (FSM_Data_DCU.dataVector[A_PINCH_S] == 1 || Flag_AN2 ==1)
    {
      Open_Window_Actuation ();
      FSM_Data_DCU.dataVector[P_W_UP] = 0;
      passenger_state = PassengerAutomaticOpen;
    }

    else if (FSM_Data_DCU.dataVector[P_W_UP] == shortpressRequest &&
        FSM_Data_DCU.dataVector[Passenger_W_UP] == 0 &&
        FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 0 &&
        FSM_Data_DCU.dataVector[A_PINCH_S] == 0)
    {
      Close_Window_Actuation ();
      FSM_Data_DCU.dataVector[P_W_DOWN] = 0;
      passenger_state = PassengerAutomaticClose;
    }
    else if (FSM_Data_DCU.dataVector[P_W_UP] == longpressRequest &&
        FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 0 &&
        FSM_Data_DCU.dataVector[Passenger_W_UP] == 1 &&
        FSM_Data_DCU.dataVector[A_PINCH_S] == 0)
    {
      Open_Window_Actuation ();
      FSM_Data_DCU.dataVector[P_W_DOWN] = 0;
      passenger_state = PassengerWindowLocked;
    }
    else if  ((FSM_Data_DCU.dataVector[Passenger_W_UP]==1 && FSM_Data_DCU.dataVector[Passenger_W_DOWN] ==1)||
              FSM_Data_DCU.dataVector[P_W_UP]==buttonStuck)
              {
                Cancel_Window_Actuation ();
                passenger_state = PassengerWindowLocked;
                FSM_Data_DCU.dataVector[P_W_DOWN] = 0;
              }
    else
    {
      if(FSM_Data_DCU.dataVector[A_PINCH_S] == 0)
      {
      Open_Window_Actuation();
      passenger_state = PassengerAutomaticOpen;
      }
      else
      {

      }
    }
  }
  else if (FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_open && FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 0 &&
          (FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & PASS_MASK4) == PASS_MASK3)
  {
    Close_Window_Actuation ();
    passenger_state = PassengerCloseWindow;
  }
  else if (FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 0 && FSM_Data_DCU.dataVector[WINDOW_ST] == d_c_open)
  {
    Cancel_Window_Actuation ();
    FSM_Data_DCU.dataVector[P_W_DOWN] = 0;
    passenger_state = PassengerWindowLocked;
    Flag_AN2 = 0;
  }
  else
  {
    Cancel_Window_Actuation ();
    passenger_state = PassengerWindowLocked;
  }
}



void PassengerAutomaticClose_func()
{
  if (FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 1)
  {
    Cancel_Window_Actuation ();
    passenger_state = PassengerWindowLocked;
  }
  else if (FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close && FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 0 &&
         ((FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & PASS_MASK4) == 0 ||(FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & PASS_MASK4) == PASS_MASK4))
  {
    if (FSM_Data_DCU.dataVector[A_PINCH_S] == 1)
    {
      Cancel_Window_Actuation ();
      FSM_Data_DCU.dataVector[P_W_UP] = 0;
      passenger_state = PassengerAutomaticOpen;
      Flag_AN2 =1;
    }
    else if (FSM_Data_DCU.dataVector[P_W_DOWN] == shortpressRequest  &&
             FSM_Data_DCU.dataVector[Passenger_W_UP] == 0 &&
             FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 0)
    {
      Open_Window_Actuation ();
      FSM_Data_DCU.dataVector[P_W_UP] = 0;
      passenger_state = PassengerAutomaticOpen;
    }
    else if (FSM_Data_DCU.dataVector[P_W_DOWN] == longpressRequest &&
             FSM_Data_DCU.dataVector[Passenger_W_UP] == 0 &&
             FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 1)
    {
      Open_Window_Actuation ();
      FSM_Data_DCU.dataVector[P_W_UP] = 0;
      passenger_state  = PassengerWindowLocked;
    }
    else if  ((FSM_Data_DCU.dataVector[P_W_UP]==shortpressRequest && FSM_Data_DCU.dataVector[P_W_DOWN] ==shortpressRequest)||
              (FSM_Data_DCU.dataVector[P_W_UP]==buttonStuck ))
    {
      Cancel_Window_Actuation ();
      passenger_state = PassengerWindowLocked;
    }
    else
    {
        Close_Window_Actuation ();
        FSM_Data_DCU.dataVector[P_W_UP] = 0;
        passenger_state  = PassengerAutomaticClose;
    }
  }
  else if (FSM_Data_DCU.dataVector[WINDOW_ST] != d_c_close && FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 0 &&
          (FSM_Data_DCU.dataVector[CAN2_W_CONTROL] & PASS_MASK4)== PASS_MASK2)
  {
    if (FSM_Data_DCU.dataVector[A_PINCH_S] == 1)
    {
      Cancel_Window_Actuation ();
      FSM_Data_DCU.dataVector[P_W_UP] = 0;
      passenger_state = PassengerAutomaticOpen;
      Flag_AN2 = 1;
    }
    else
    {
    Open_Window_Actuation ();
    FSM_Data_DCU.dataVector[P_W_UP] = 0;
    passenger_state  = PassengerWindowLocked;
    }
  }
  else if(FSM_Data_DCU.dataVector[CAN2_W_LOCK] == 0 && FSM_Data_DCU.dataVector[WINDOW_ST] == d_c_close)
  {
    Cancel_Window_Actuation ();
    FSM_Data_DCU.dataVector[P_W_UP] = 0;
    passenger_state  = PassengerWindowLocked;
  }
  else
  {
      //Only for QAC
  }
}

void Passenger_Driver_State_func ()
{
  if (FSM_Data_DCU.dataVector[W_LOCK] == 0)
  {
    if ((FSM_Data_DCU.dataVector[P_W_DOWN] == shortpressRequest || FSM_Data_DCU.dataVector[P_W_DOWN] == longpressRequest)
        && FSM_Data_DCU.dataVector[Passenger_W_UP] == 0 && FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 1)
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = ((FSM_Data_DCU.dataVector[W_CONTROL]) & PASS_MASK1) | PASS_MASK2;
    }
    else if ((FSM_Data_DCU.dataVector[P_W_UP] == shortpressRequest || FSM_Data_DCU.dataVector[P_W_UP] == longpressRequest)
        && FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 0 && FSM_Data_DCU.dataVector[Passenger_W_UP] == 1)
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = ((FSM_Data_DCU.dataVector[W_CONTROL]) & PASS_MASK1) | PASS_MASK3;
    }
    else if ((FSM_Data_DCU.dataVector[Passenger_W_UP] == 0 && FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 0)
        || (FSM_Data_DCU.dataVector[Passenger_W_UP] == 1 && FSM_Data_DCU.dataVector[Passenger_W_DOWN] == 1))
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = (FSM_Data_DCU.dataVector[W_CONTROL]) & PASS_MASK1;
    }
    else
    {
      FSM_Data_DCU.dataVector[W_CONTROL] = (FSM_Data_DCU.dataVector[W_CONTROL]) & PASS_MASK1;
    }
  }
  else if (FSM_Data_DCU.dataVector[W_LOCK] == 1)
  {
    FSM_Data_DCU.dataVector[W_CONTROL] = (FSM_Data_DCU.dataVector[W_CONTROL]) & PASS_MASK1;
  }
  else
  {

  }
}

void InitPassengerWindow()
{
  passenger_state = PassengerVerifyID;
}


