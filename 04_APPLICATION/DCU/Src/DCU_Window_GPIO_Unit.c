/*
 * DCU_Window_GPIO_Unit.c
 *
 *  Created on: 5 oct. 2022
 *      Author: uif36103
 */

#include "04_APPLICATION/DCU/Include/DCU_Window_GPIO_Unit.h"
#include "02_HAL/IoHw_Mgr/Include/IoHw_Mgr.h"
#include "03_SERVICES/Data_Transfer/Include/Data_Transfer.h"


#ifndef DEBOUNCE_TIME
#define DEBOUNCE_TIME  10
#endif


uint8 Door_counter = 0;
uint16 readed_gpio_buttons [NUM_WINDOW_BTNS];
uint16 btn_vector[NUM_WINDOW_BTNS];
D_window_btn_states btn_states_vector[NUM_WINDOW_BTNS];                                        //This vector stores the state of every window btn
uint8 debounce_counter_vector[NUM_WINDOW_BTNS];                                               //This vector stores the count of debounce of every window btn
uint8 x;


void Btn_Unit ()
{
   DCU_ReadButtons ();
  x =0;
  for (x = 0; x < NUM_WINDOW_BTNS; x++)
  {

    btn_vector[x]=readed_gpio_buttons[x];
    switch (btn_states_vector[x])
    {
      case Polling :
        Polling_func(x);
        break;

      case Debounce :
        Debounce_func(x);
        break;

      case window_Btn_req :
        Btn_Request_func(x);
        break;

      default :
        // Only for QAC
        break;
    }
  }
}

void Polling_func(uint8 t)
{
  if(btn_vector[t] == 0)
  {
    btn_states_vector[t] = Polling;
  }else if(btn_vector[t] == 1)
  {
    btn_states_vector[t] = Debounce;
  }else
  {
    // Only for QAC
  }
}

void Debounce_func(uint8 q)
{
  debounce_counter_vector[q] = debounce_counter_vector[q] + 1;

  if (debounce_counter_vector[q] <= DEBOUNCE_TIME) //following the timer of 1us (check CM_SetUpCounter() on Counter_Mgr.c)
  {
    btn_states_vector[q] = Debounce;
  }
  else if (debounce_counter_vector[q] > DEBOUNCE_TIME)
  {
    if (btn_vector[q] == 0)
    {
      btn_states_vector[q] = Polling;
    }
    else if (btn_vector[q] == 1)
    {
      btn_states_vector[q] = window_Btn_req;
    }
    else
    {
      //just for QAC
    }
    debounce_counter_vector[q] = 0;
  }

}

void Btn_Request_func(uint8 z)
{
  if(btn_vector[z]==1)
  {
      FSM_Data_DCU.dataVector[z]=  buttonpressed;
    //Btn_Request = 1;
    btn_states_vector[z] = window_Btn_req;
  }
  else if(btn_vector[z] == 0)
  {
      FSM_Data_DCU.dataVector[z]=  buttonNOTpressed;
    //Btn_Request = 0;
    btn_states_vector[z] = Polling;
  }
}



void Init_window_vectors(void)
{
                     //This Vector stores the btn of every window btn

  for(uint8 i = 0; i < NUM_WINDOW_BTNS; i++)
  {
    btn_vector[i] = 0;
    btn_states_vector[i] = Polling;
    debounce_counter_vector[i]=0;


  }
}

void DCU_ReadButtons ()
{

    readed_gpio_buttons[0] = IfxPort_getPinState(PIN36); //Driver_W_Down
    readed_gpio_buttons[1] = IfxPort_getPinState(PIN34); //Driver_w_Up
    readed_gpio_buttons[2] = IfxPort_getPinState(PIN40); //Passenger_W_DOWN
    readed_gpio_buttons[3] = IfxPort_getPinState(PIN38); //Passenger_W_UP
    readed_gpio_buttons[4] = IfxPort_getPinState(PIN44); //REARLEFT_W_DOWN
    readed_gpio_buttons[5] = IfxPort_getPinState(PIN42); //REARLEFT_W_UP
    readed_gpio_buttons[6] = IfxPort_getPinState(PIN31); //REARRIGHT_W_DOWN
    readed_gpio_buttons[7] = IfxPort_getPinState(PIN46); //REARRIGHT_W_UP
    readed_gpio_buttons[8] = IfxPort_getPinState(PIN30); //WINDOW_LOCK
    readed_gpio_buttons[9] = IfxPort_getPinState(PIN32); //ANTIPINCH
    FSM_Data_DCU.dataVector[10] =  IfxPort_getPinState(PIN24);
    readed_gpio_buttons[10] = IfxPort_getPinState(PIN24);
    FSM_Data_DCU.dataVector[11] = IfxPort_getPinState(PIN22);
    readed_gpio_buttons[11] = IfxPort_getPinState(PIN22);
}




