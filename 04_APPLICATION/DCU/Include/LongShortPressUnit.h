/*
 * LongShortPressUnit.h
 *
 *  Created on: 5 oct. 2022
 *      Author: uif36103
 */

#ifndef DCU_INCLUDE_LONGSHORTPRESSUNIT_H_
#define DCU_INCLUDE_LONGSHORTPRESSUNIT_H_

#include "04_APPLICATION/DCU/Include/DCU_Window_GPIO_Unit.h"
#include "02_HAL/IoHw_Mgr/Include/IoHw_Mgr.h"

#ifndef SHORT_TIME
#define SHORT_TIME         250               //250Time used to check 500 msec in short press (the module is read every 2 msec)
#endif

#ifndef LONG_TIME
#define LONG_TIME          5000               //5000Time used to check 500 msec in short press (the module is read every 2 msec)
#endif


#ifndef windowButton_idle
#define windowButton_idle    0
#endif
#ifndef shortpressRequest
#define shortpressRequest    1
#endif
#ifndef longpressRequest
#define longpressRequest     2
#endif
#ifndef buttonStuck
#define buttonStuck          3
#endif

#ifndef MAX_WINDOW_BTNS
#define MAX_WINDOW_BTNS      8
#endif



void longShortpress_func(void);
void ls_Polling_func(uint8);
void shortPress_func(uint8);
void Debounce_shortPress_func(uint8);
void longPress_func(uint8);
void ls_error_func(uint8);
void checkInputs(void);
void Init_Vector_ls (void);


typedef enum
{
  ls_polling = 0,
  shortPress,
  longPress,
  ls_error,
}LongShortStates;





#endif /* DCU_INCLUDE_LONGSHORTPRESSUNIT_H_ */
