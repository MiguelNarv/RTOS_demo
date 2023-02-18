/*
 * WindowControl.h
 *
 *  Created on: 5 oct. 2022
 *      Author: uif36103
 */

#ifndef DCU_INCLUDE_WINDOWCONTROL_H_
#define DCU_INCLUDE_WINDOWCONTROL_H_


#include <stdio.h>
#include <stdlib.h>
#include "02_HAL/IoHw_Mgr/Include/IoHw_Mgr.h"
#include "03_SERVICES/Data_Transfer/Include/Data_Transfer.h"
#include "04_APPLICATION/DCU/Include/LongShortPressUnit.h"
#include "04_APPLICATION/DCU/Include/DCU_Window_GPIO_Unit.h"
//////////////////////////////////////INPUTS Positions///////////////////////////////////////////////////////////

#define Driver_W_DOWN        0
#define Driver_W_UP          1
#define Passenger_W_DOWN     2
#define Passenger_W_UP       3
#define REARLEFT_W_DOWN      4
#define REARLEFT_W_UP        5
#define REARRIGHT_W_DOWN     6
#define REARRIGHT_W_UP       7


#define W_LOCK          8
#define A_PINCH_S       9
#define D_W_DOWN        14
#define D_W_UP          15
#define P_W_DOWN        16
#define P_W_UP          17
#define RL_W_DOWN       18
#define RL_W_UP         19
#define RR_W_DOWN       20
#define RR_W_UP         21
#define WINDOW_ST       22
#define CAN2_W_CONTROL  23

//////////////////////////////////////OUTPUTS Positions///////////////////////////////////////////////////////////
#define W_CONTROL       24
#define WINDOW_POS      25
#define WINDOW_OP       26
#define ACT_WINDOW      27
#define W_LOCK_CMD      28
#define CAN2_W_LOCK     29

#define PASS_MASK1      207    //11 00 11 11
#define PASS_MASK2      32     //00 10 00 00
#define PASS_MASK3      16     //00 01 00 00
#define PASS_MASK4      48     //00 11 00 00

#define RL_MASK1        243    //11 11 00 11
#define RL_MASK2        8      //00 00 10 00
#define RL_MASK3        4      //00 00 01 00
#define RL_MASK4        12     //00 00 11 00

#define RR_MASK1        252    //11 11 11 00
#define RR_MASK2        2      //00 00 00 10
#define RR_MASK3        1      //00 00 00 01
#define RR_MASK4        3      //00 00 00 11

//#define DATAVECTOR      26
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



typedef enum
{
    DriverVerifyID = 0,
    DriverWindowLocked,
    DriverAutomaticOpen,
    DriverAutomaticClose,
    DriverOpenWindow,
    DriverCloseWindow,
    DriverNoDeviceConnected
}windowState1;

typedef enum
{
    PassengerVerifyID = 0,
    PassengerWindowLocked,
    PassengerAutomaticOpen,
    PassengerAutomaticClose,
    PassengerOpenWindow,
    PassengerCloseWindow,
    PassengerNoDeviceConnected,
    Passenger_Driver_State
}windowState2;

typedef enum
{
    RearRightVerifyID = 0,
    RearRightWindowLocked,
    RearRightWindowUnlocked,
    RearRightOpenWindow,
    RearRightCloseWindow,
    RearRightNoDeviceConnected,
    RearRight_Driver_State
}windowState3;

typedef enum
{
    RearLeftVerifyID = 0,
    RearLeftWindowLocked,
    RearLeftWindowUnlocked,
    RearLeftOpenWindow,
    RearLeftCloseWindow,
    RearLeftNoDeviceConnected,
    RearLeft_Driver_State
}windowState4;

typedef enum
{
    d_idle = 0,
    d_up,
    d_down
}D_WindowOp;

typedef enum
{
    d_inBetween =0,
    d_c_open,
    d_c_close,
    d_error
}D_WindowPos;

typedef enum
{
  no_moving = 0,
  window_down,
  window_up
}actuateWindowReq;

typedef enum
{
  windowUnlocked = 0,
  windowLocked
}windowLockCmd;

typedef enum
{
  windowNo_req = 0,
  windowUp_req,
  windowDown_req,
  windowInvalid
}WindowControlCmd;

//typedef enum
//{
//  No_req = 0,
//  Short_req,
//  Long_req,
//  Error_req
//}longshortReq;

//prototypes
void InitVariables(void);
void Cancel_Window_Actuation (void);
void Open_Window_Actuation (void);
void Close_Window_Actuation (void);
void Antipinch_func(void);

void Check_Driver_Window_Control_Unit(void);
void Check_DriverInactivateWindow(void);
void Check_DriverVerifyID_func (void);
void Check_DriverNoDeviceConnected_func (void);
void Check_DriverWindowLocked_func (void);
void Check_DriverAutomaticOpen_func(void);
void Check_DriverAutomaticClose_func(void);
void Check_DriverOpenWindow_func(void);
void Check_DriverCloseWindow_func(void);
//void Driver_Window_Control_Unit(void);
//void DriverInactivateWindow(void);
//void DriverVerifyID_func (void);
//void DriverNoDeviceConnected_func (void);
//void DriverWindowLocked_func (void);
//void DriverAutomaticOpen_func(void);
//void DriverAutomaticClose_func(void);
//void DriverOpenWindow_func(void);
//void DriverCloseWindow_func(void);

void InitPassengerWindow(void);
void Passenger_Window_Control_Unit(void);
void PassengerInactivateWindow(void);
void PassengerVerifyID_func (void);
void PassengerNoDeviceConnected_func (void);
void Passenger_Driver_State_func(void);
void PassengerWindowLocked_func (void);
void PassengerAutomaticOpen_func(void);
void PassengerAutomaticClose_func(void);
void PassengerOpenWindow_func(void);
void PassengerCloseWindow_func(void);

void InitRearLeftWindow(void);
void RearLeft_Window_Control_Unit(void);
void RearLeftInactivateWindow(void);
void RearLeftVerifyID_func (void);
void RearLeftNoDeviceConnected_func (void);
void RearLeft_Driver_State_func(void);
void RearLeftWindowLocked_func (void);
void RearLeftOpenWindow_func(void);
void RearLeftCloseWindow_func(void);

void InitRearRightWindow(void);
void RearRight_Window_Control_Unit(void);
void RearRightInactivateWindow(void);
void RearRightVerifyID_func (void);
void RearRightNoDeviceConnected_func (void);
void RearRight_Driver_State_func(void);
void RearRightWindowLocked_func (void);
void RearRightOpenWindow_func(void);
void RearRightCloseWindow_func(void);


#endif /* DCU_INCLUDE_WINDOWCONTROL_H_ */
