/*
 * DCU_Window_GPIO_Unit.h
 *
 *  Created on: 5 oct. 2022
 *      Author: uif36103
 */

#ifndef DCU_INCLUDE_DCU_WINDOW_GPIO_UNIT_H_
#define DCU_INCLUDE_DCU_WINDOW_GPIO_UNIT_H_

#include <stdio.h>
#include "IfxPort.h"
#include "Ifx_Types.h"
#include "03_SERVICES/Data_Transfer/Include/Data_Transfer.h"


#ifndef NUM_WINDOW_BTNS
#define NUM_WINDOW_BTNS   14
#endif

#ifndef buttonNOTpressed
#define buttonNOTpressed  0
#endif

#ifndef buttonpressed
#define buttonpressed     1
#endif


void Init_window_vectors(void);
void DCU_ReadButtons (void);
void Btn_Unit (void);
void Polling_func(uint8 );
void Debounce_func(uint8 );
void Btn_Request_func(uint8 );

typedef enum
{
  Polling,
  Debounce,
  window_Btn_req
}D_window_btn_states;





#endif /* DCU_INCLUDE_DCU_WINDOW_GPIO_UNIT_H_ */
