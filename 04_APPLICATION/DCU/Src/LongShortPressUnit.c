/*
 * LongShortPressUnit.c
 *
 *  Created on: 5 oct. 2022
 *      Author: uif36103
 */
#include "04_APPLICATION/DCU/Include/DCU_Window_GPIO_Unit.h"
#include "03_SERVICES/Data_Transfer/Include/Data_Transfer.h"
#include "04_APPLICATION/DCU/Include/LongShortPressUnit.h"

LongShortStates ls_states_vector[NUM_WINDOW_BTNS];
uint16 longshort_counter_vector[NUM_WINDOW_BTNS];

void longShortpress_func ()
{
  for (uint8 y = 0; y < MAX_WINDOW_BTNS; y++)            //NUMBER 2 REPRESENT THE OFFSET POSITION INCLUDING ANTIPINCH AND WINDOW LOCK BUTTON
  {
    switch (ls_states_vector[y])
    {
      case ls_polling :
        ls_Polling_func(y);
        break;
      case shortPress :
        shortPress_func(y);
        break;
//      case debounce_shortPress :
//        Debounce_shortPress_func(y);
//        break;
      case longPress :
        longPress_func(y);
        break;
      case ls_error :
        ls_error_func(y);
        break;
      default : // Only for QAC
        break;
    }
  }
}

void ls_Polling_func (uint8 y)
{
  if (FSM_Data_DCU.dataVector[y] == buttonNOTpressed)
  {
    ls_states_vector[y] = ls_polling;
    //FSM_Data_DCU.dataVector[y + NUM_WINDOW_BTNS] = windowButton_idle;
  }
  else if (FSM_Data_DCU.dataVector[y] == buttonpressed)
  {
    if (FSM_Data_DCU.dataVector[31] == 0x00 || FSM_Data_DCU.dataVector[31] == 0x01)
    {
      ls_states_vector[y] = shortPress;
    }
    else if (FSM_Data_DCU.dataVector[31] == 0x02 || FSM_Data_DCU.dataVector[31] == 0x03)
    {
      ls_states_vector[y] = longPress;
    }
    else
    {
      //Only for QAC
    }
  }
  else
  {
    //Only for QAC
  }
}

void shortPress_func (uint8 y)
{
  longshort_counter_vector[y] = longshort_counter_vector[y] + 1;

  if (longshort_counter_vector[y] < SHORT_TIME)
  {
    if (FSM_Data_DCU.dataVector[y] == buttonpressed)
    {
      FSM_Data_DCU.dataVector[y + NUM_WINDOW_BTNS] = windowButton_idle;
      ls_states_vector[y] = shortPress;
    }
    else if (FSM_Data_DCU.dataVector[y] == buttonNOTpressed)
    {
//        FSM_Data_DCU.dataVector[y + NUM_WINDOW_BTNS] = windowButton_idle;
//        ls_states_vector[y] = debounce_shortPress;
        FSM_Data_DCU.dataVector[y + NUM_WINDOW_BTNS] = shortpressRequest;
        longshort_counter_vector[y] = 0;
        ls_states_vector[y] = ls_polling;
    }
    else
    {
      //Only for QAC
    }
  }
  else if (longshort_counter_vector[y] >= SHORT_TIME )
  {
      FSM_Data_DCU.dataVector[y+NUM_WINDOW_BTNS]= windowButton_idle;
      ls_states_vector[y] = longPress;
      //Only for QAC
  }
  else
  {

  }
}


void longPress_func(uint8 y)
{
  longshort_counter_vector[y] = longshort_counter_vector[y] + 1;

   if (longshort_counter_vector[y] < LONG_TIME)
   {
     if (FSM_Data_DCU.dataVector[y] == buttonpressed)
     {
       FSM_Data_DCU.dataVector[y + NUM_WINDOW_BTNS] = longpressRequest;
       ls_states_vector[y] = longPress;
     }
     else if (FSM_Data_DCU.dataVector[y] == buttonNOTpressed)
     {
       FSM_Data_DCU.dataVector[y + NUM_WINDOW_BTNS] = windowButton_idle;
       longshort_counter_vector[y] = 0;
       ls_states_vector[y] = ls_polling;
     }
     else
     {
       //Only for QAC
     }
   }
   else if (longshort_counter_vector[y] >= LONG_TIME)
   {
     if (FSM_Data_DCU.dataVector[y] == buttonpressed)
     {
       FSM_Data_DCU.dataVector[y+NUM_WINDOW_BTNS]= buttonStuck;
       longshort_counter_vector[y] = 0;
       ls_states_vector[y] = ls_error;
     }
     else if (FSM_Data_DCU.dataVector[y] == buttonNOTpressed)
     {
       FSM_Data_DCU.dataVector[y+NUM_WINDOW_BTNS]= windowButton_idle;
       longshort_counter_vector[y] = 0;
       ls_states_vector[y] = ls_polling;
     }
     else
     {
       //Only for QAC
     }
   }
}

void ls_error_func(uint8 y)
{
    FSM_Data_DCU.dataVector[y+NUM_WINDOW_BTNS]= buttonStuck;
}


void Init_Vector_ls ()
{
    for(uint8 i = 0; i < NUM_WINDOW_BTNS; i++)
      {
        ls_states_vector[i] =ls_polling;
        longshort_counter_vector[i] = 0;
      }
}
