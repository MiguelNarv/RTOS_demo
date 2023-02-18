/*
 * Window_Actuation_Unit.c
 *
 *  Created on: 12 oct. 2022
 *      Author: uif36103
 */
#include "04_APPLICATION/DCU/Include/Window_Actuation_Unit.h"

WindowAct_States PositionOfWindow;
uint16 Window_CNT = 625;

void Window_Act_Unit ()
{
  switch (PositionOfWindow)
  {
    case Completely_Open :
      Completely_Open_func();
      break;
    case Window_InBetween :
      Window_InBetween_func();
      break;
    case Completely_Close :
      Completely_Close_func();
      break;
    default : // Only for QAC
      break;
  }
}

void Completely_Open_func ()
{
  WindowCounter_func();
  if (Window_CNT == 0)
  {
    PositionOfWindow = Completely_Open;
    FSM_Data_DCU.dataVector[WINDOW_ST] = d_c_open;
  }
  else if (Window_CNT > 0)
  {
    PositionOfWindow = Window_InBetween;
    FSM_Data_DCU.dataVector[WINDOW_ST] = d_inBetween;
  }
  W_LED_POS ();
}

void Completely_Close_func()
{
  WindowCounter_func();
  if (Window_CNT == MAX_TIME_WINDOW_MOVING)
  {
    PositionOfWindow = Completely_Close;
    FSM_Data_DCU.dataVector[WINDOW_ST] = d_c_close;
  }
  else if (Window_CNT < MAX_TIME_WINDOW_MOVING)
  {
    PositionOfWindow = Window_InBetween;
    FSM_Data_DCU.dataVector[WINDOW_ST] = d_inBetween;
  }
  W_LED_POS ();
}


void Window_InBetween_func()
{
  WindowCounter_func();
  if (Window_CNT >= MAX_TIME_WINDOW_MOVING)
  {
    PositionOfWindow = Completely_Close;
    FSM_Data_DCU.dataVector[WINDOW_ST] = d_c_close;
  }
  else if (Window_CNT <= 0)
  {
    PositionOfWindow = Completely_Open;
    FSM_Data_DCU.dataVector[WINDOW_ST] = d_c_open;
  }
  else
  {
    PositionOfWindow = Window_InBetween;
    FSM_Data_DCU.dataVector[WINDOW_ST] = d_inBetween;
  }
  W_LED_POS ();
}

void WindowCounter_func ()
{
  if (FSM_Data_DCU.dataVector[ACT_WINDOW] == window_down)
  {
    if (Window_CNT == 0)
    {
      Window_CNT = 0;
    }
    else
    {
      Window_CNT--;
    }
  }
  else if (FSM_Data_DCU.dataVector[ACT_WINDOW] == window_up)
  {
    if (Window_CNT >= MAX_TIME_WINDOW_MOVING)
    {
      Window_CNT = MAX_TIME_WINDOW_MOVING;
    }
    else
    {
      Window_CNT++;
    }
  }
  else
  {
    //Only for QAC
  }
}

void W_LED_POS ()
{
  if (Window_CNT == 0)
  {
    IfxPort_setPinState(PIN35, IfxPort_State_low);
    IfxPort_setPinState(PIN37, IfxPort_State_low);
    IfxPort_setPinState(PIN39, IfxPort_State_low);
    IfxPort_setPinState(PIN41, IfxPort_State_low);
    IfxPort_setPinState(PIN43, IfxPort_State_low);
    IfxPort_setPinState(PIN45, IfxPort_State_low);
    IfxPort_setPinState(PIN47, IfxPort_State_low);
    IfxPort_setPinState(PIN49, IfxPort_State_low);
    IfxPort_setPinState(PIN51, IfxPort_State_low);
    IfxPort_setPinState(PIN53, IfxPort_State_low);
  }
  else if (Window_CNT > 0 && Window_CNT <= FIRSTLED)
  {
    IfxPort_setPinState(PIN35, IfxPort_State_high);
    IfxPort_setPinState(PIN37, IfxPort_State_low);
    IfxPort_setPinState(PIN39, IfxPort_State_low);
    IfxPort_setPinState(PIN41, IfxPort_State_low);
    IfxPort_setPinState(PIN43, IfxPort_State_low);
    IfxPort_setPinState(PIN45, IfxPort_State_low);
    IfxPort_setPinState(PIN47, IfxPort_State_low);
    IfxPort_setPinState(PIN49, IfxPort_State_low);
    IfxPort_setPinState(PIN51, IfxPort_State_low);
    IfxPort_setPinState(PIN53, IfxPort_State_low);
  }
  else if (Window_CNT > FIRSTLED && Window_CNT <= SECONDLED)
  {
    IfxPort_setPinState(PIN35, IfxPort_State_high);
    IfxPort_setPinState(PIN37, IfxPort_State_high);
    IfxPort_setPinState(PIN39, IfxPort_State_low);
    IfxPort_setPinState(PIN41, IfxPort_State_low);
    IfxPort_setPinState(PIN43, IfxPort_State_low);
    IfxPort_setPinState(PIN45, IfxPort_State_low);
    IfxPort_setPinState(PIN47, IfxPort_State_low);
    IfxPort_setPinState(PIN49, IfxPort_State_low);
    IfxPort_setPinState(PIN51, IfxPort_State_low);
    IfxPort_setPinState(PIN53, IfxPort_State_low);
  }
  else if (Window_CNT > SECONDLED && Window_CNT <= THIRDLED)
  {
    IfxPort_setPinState(PIN35, IfxPort_State_high);
    IfxPort_setPinState(PIN37, IfxPort_State_high);
    IfxPort_setPinState(PIN39, IfxPort_State_high);
    IfxPort_setPinState(PIN41, IfxPort_State_low);
    IfxPort_setPinState(PIN43, IfxPort_State_low);
    IfxPort_setPinState(PIN45, IfxPort_State_low);
    IfxPort_setPinState(PIN47, IfxPort_State_low);
    IfxPort_setPinState(PIN49, IfxPort_State_low);
    IfxPort_setPinState(PIN51, IfxPort_State_low);
    IfxPort_setPinState(PIN53, IfxPort_State_low);
  }
  else if (Window_CNT > THIRDLED && Window_CNT <= FOURTHLED)
  {
    IfxPort_setPinState(PIN35, IfxPort_State_high);
    IfxPort_setPinState(PIN37, IfxPort_State_high);
    IfxPort_setPinState(PIN39, IfxPort_State_high);
    IfxPort_setPinState(PIN41, IfxPort_State_high);
    IfxPort_setPinState(PIN43, IfxPort_State_low);
    IfxPort_setPinState(PIN45, IfxPort_State_low);
    IfxPort_setPinState(PIN47, IfxPort_State_low);
    IfxPort_setPinState(PIN49, IfxPort_State_low);
    IfxPort_setPinState(PIN51, IfxPort_State_low);
    IfxPort_setPinState(PIN53, IfxPort_State_low);
  }
  else if (Window_CNT > FOURTHLED && Window_CNT <= MIDLELED)
  {
    IfxPort_setPinState(PIN35, IfxPort_State_high);
    IfxPort_setPinState(PIN37, IfxPort_State_high);
    IfxPort_setPinState(PIN39, IfxPort_State_high);
    IfxPort_setPinState(PIN41, IfxPort_State_high);
    IfxPort_setPinState(PIN43, IfxPort_State_high);
    IfxPort_setPinState(PIN45, IfxPort_State_low);
    IfxPort_setPinState(PIN47, IfxPort_State_low);
    IfxPort_setPinState(PIN49, IfxPort_State_low);
    IfxPort_setPinState(PIN51, IfxPort_State_low);
    IfxPort_setPinState(PIN53, IfxPort_State_low);
  }
  else if (Window_CNT > MIDLELED && Window_CNT <= SIXTHLED)
  {
    IfxPort_setPinState(PIN35, IfxPort_State_high);
    IfxPort_setPinState(PIN37, IfxPort_State_high);
    IfxPort_setPinState(PIN39, IfxPort_State_high);
    IfxPort_setPinState(PIN41, IfxPort_State_high);
    IfxPort_setPinState(PIN43, IfxPort_State_high);
    IfxPort_setPinState(PIN45, IfxPort_State_high);
    IfxPort_setPinState(PIN47, IfxPort_State_low);
    IfxPort_setPinState(PIN49, IfxPort_State_low);
    IfxPort_setPinState(PIN51, IfxPort_State_low);
    IfxPort_setPinState(PIN53, IfxPort_State_low);
  }
  else if (Window_CNT > SIXTHLED && Window_CNT <= SEVENTHLED)
  {
    IfxPort_setPinState(PIN35, IfxPort_State_high);
    IfxPort_setPinState(PIN37, IfxPort_State_high);
    IfxPort_setPinState(PIN39, IfxPort_State_high);
    IfxPort_setPinState(PIN41, IfxPort_State_high);
    IfxPort_setPinState(PIN43, IfxPort_State_high);
    IfxPort_setPinState(PIN45, IfxPort_State_high);
    IfxPort_setPinState(PIN47, IfxPort_State_high);
    IfxPort_setPinState(PIN49, IfxPort_State_low);
    IfxPort_setPinState(PIN51, IfxPort_State_low);
    IfxPort_setPinState(PIN53, IfxPort_State_low);
  }
  else if (Window_CNT > SEVENTHLED && Window_CNT <= EIGTHLED)
  {
    IfxPort_setPinState(PIN35, IfxPort_State_high);
    IfxPort_setPinState(PIN37, IfxPort_State_high);
    IfxPort_setPinState(PIN39, IfxPort_State_high);
    IfxPort_setPinState(PIN41, IfxPort_State_high);
    IfxPort_setPinState(PIN43, IfxPort_State_high);
    IfxPort_setPinState(PIN45, IfxPort_State_high);
    IfxPort_setPinState(PIN47, IfxPort_State_high);
    IfxPort_setPinState(PIN49, IfxPort_State_high);
    IfxPort_setPinState(PIN51, IfxPort_State_low);
    IfxPort_setPinState(PIN53, IfxPort_State_low);
  }
  else if (Window_CNT > EIGTHLED && Window_CNT <= NINTHLED)
  {
    IfxPort_setPinState(PIN35, IfxPort_State_high);
    IfxPort_setPinState(PIN37, IfxPort_State_high);
    IfxPort_setPinState(PIN39, IfxPort_State_high);
    IfxPort_setPinState(PIN41, IfxPort_State_high);
    IfxPort_setPinState(PIN43, IfxPort_State_high);
    IfxPort_setPinState(PIN45, IfxPort_State_high);
    IfxPort_setPinState(PIN47, IfxPort_State_high);
    IfxPort_setPinState(PIN49, IfxPort_State_high);
    IfxPort_setPinState(PIN51, IfxPort_State_high);
    IfxPort_setPinState(PIN53, IfxPort_State_low);
  }
  else
  {
    IfxPort_setPinState(PIN35, IfxPort_State_high);
    IfxPort_setPinState(PIN37, IfxPort_State_high);
    IfxPort_setPinState(PIN39, IfxPort_State_high);
    IfxPort_setPinState(PIN41, IfxPort_State_high);
    IfxPort_setPinState(PIN43, IfxPort_State_high);
    IfxPort_setPinState(PIN45, IfxPort_State_high);
    IfxPort_setPinState(PIN47, IfxPort_State_high);
    IfxPort_setPinState(PIN49, IfxPort_State_high);
    IfxPort_setPinState(PIN51, IfxPort_State_high);
    IfxPort_setPinState(PIN53, IfxPort_State_high);
  }
}



