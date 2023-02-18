/*
 * Window_Actuation_Unit.h
 *
 *  Created on: 6 oct. 2022
 *      Author: uif36103
 */

#ifndef DCU_INCLUDE_WINDOW_ACTUATION_UNIT_H_
#define DCU_INCLUDE_WINDOW_ACTUATION_UNIT_H_

#include "04_APPLICATION/DCU/Include/DCU_Window_GPIO_Unit.h"
#include "03_SERVICES/Data_Transfer/Include/Data_Transfer.h"
#include "04_APPLICATION/DCU/Include/WindowControl.h"

#ifndef MAX_TIME_WINDOW_MOVING
#define MAX_TIME_WINDOW_MOVING    625
#endif

//////////////////Window limits///////////////////////////////
#ifndef FIRSTLED
#define FIRSTLED    63
#endif

#ifndef SECONDLED
#define SECONDLED   126
#endif

#ifndef THIRDLED
#define THIRDLED    189
#endif

#ifndef FOURTHLED
#define FOURTHLED   252
#endif

#ifndef MIDLELED
#define MIDLELED    315
#endif

#ifndef SIXTHLED
#define SIXTHLED    378
#endif

#ifndef SEVENTHLED
#define SEVENTHLED  441
#endif

#ifndef EIGTHLED
#define EIGTHLED    504
#endif

#ifndef NINTHLED
#define NINTHLED    577
#endif

#ifndef LASTLED
#define LASTLED     625
#endif

void Window_Act_Unit (void);
void Completely_Open_func (void);
void Completely_Close_func (void);
void Window_InBetween_func(void);
void WindowCounter_func (void);
void W_LED_POS (void);

typedef enum
{
  Completely_Open =0,
  Window_InBetween,
  Completely_Close
}WindowAct_States;



#endif /* DCU_INCLUDE_WINDOW_ACTUATION_UNIT_H_ */
