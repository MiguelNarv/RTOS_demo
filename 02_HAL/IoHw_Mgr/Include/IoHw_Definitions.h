/*
 * IoHw_Definitions.h
 *
 *  Created on: 2 oct. 2022
 *      Author: uif36100
 */

#ifndef IOHW_MGR_INCLUDE_IOHW_DEFINITIONS_H_
#define IOHW_MGR_INCLUDE_IOHW_DEFINITIONS_H_

#include "01_MAL/Common_Drivers/Infra/Sfr/TC27D/_Reg/IfxPort_reg.h"
#include "01_MAL/Common_Drivers/iLLD/TC27D/Tricore/_PinMap/IfxGtm_PinMap.h"


//TODO Include necessary definitions for ADC and CAN

// Used pins for BCM

// >>> ADC PIN

#ifndef AD0
// Pin: A0
// Net: ADC_Pin
// ECU: BCM
#define VADC_GROUP                  IfxVadc_GroupId_4
#define CHANNEL_ID                  7
#define CHANNEL_RESULT_REGISTER     0
#define AD0  //&MODULE_P14, 0
#endif



// >>> PWM PINS

#ifndef PWM2
// Pin: PWM2
// Net: LEDBar_01
// ECU: BCM
#define PWM2  (IfxGtm_TOM1_8_TOUT0_P02_0_OUT)
#endif

#ifndef PWM3
// Pin: PWM3
// Net: LEDBar_02
// ECU: BCM
#define PWM3  (IfxGtm_TOM1_9_TOUT1_P02_1_OUT)
#endif

#ifndef PWM4
// Pin: PWM4
// Net: LEDBar_03
// ECU: BCM
#define PWM4  (IfxGtm_TOM2_6_TOUT106_P10_4_OUT)
#endif

#ifndef PWM5
// Pin: PWM5
// Net: LEDBar_04
// ECU: BCM
#define PWM5  (IfxGtm_TOM0_11_TOUT3_P02_3_OUT)
#endif

#ifndef PWM6
// Pin: PWM6
// Net: LEDBar_05
// ECU: BCM
#define PWM6  (IfxGtm_TOM0_12_TOUT4_P02_4_OUT)
#endif

#ifndef PWM7
// Pin: PWM7
// Net: LEDBar_06
// ECU: BCM
#define PWM7  (IfxGtm_TOM0_13_TOUT5_P02_5_OUT)
#endif

#ifndef PWM8
// Pin: PWM7
// Net: LEDBar_06
// ECU: BCM
#define PWM8  (IfxGtm_TOM0_14_TOUT6_P02_6_OUT)
#endif



// Used pins for DCU

// >>> GPIO PINS

#ifndef PIN23
// Pin: 23
// Net: ID0
// ECU: DCU
#define PIN23  &MODULE_P14, 1
#endif

#ifndef PIN25
// Pin: 25
// Net: ID01
// ECU: DCU
#define PIN25  &MODULE_P00, 0
#endif

#ifndef PIN26
// Pin: 26
// Net: DCU_1LockLed_Signal
// ECU: DCU
#define PIN26  &MODULE_P00, 8
#endif


#ifndef PIN28
// Pin: 28
// Net: DCU_1UnlockLed_Signal
// ECU: DCU
#define PIN28  &MODULE_P00, 9
#endif


#ifndef PIN30
// Pin: 30
// Net: WindowLock_BTN
// ECU: DCU
#define PIN30  &MODULE_P00, 10
#endif

#ifndef PIN31
// Pin: 31
// Net: RearRightWindowDown_BTN
// ECU: DCU
#define PIN31  &MODULE_P00, 3
#endif

#ifndef PIN32
// Pin: 32
// Net: AntiPinch_Signal
// ECU: DCU
#define PIN32  &MODULE_P00, 11
#endif


#ifndef PIN34
// Pin: 34
// Net: DriverWindowUp_BTN
// ECU: DCU
#define PIN34  &MODULE_P00, 12
#endif

#ifndef PIN35
// Pin: 35
// Net: LEDBar_01
// ECU: DCU
#define PIN35  &MODULE_P00, 5
#endif

#ifndef PIN36
// Pin: 36
// Net: DriverWindowDown_BTN
// ECU: DCU
#define PIN36  &MODULE_P33, 2
#endif

#ifndef PIN37
// Pin: 37
// Net: LEDBar_02
// ECU: DCU
#define PIN37  &MODULE_P00, 6
#endif

#ifndef PIN38
// Pin: 38
// Net: PassengerWindowUp_BTN
// ECU: DCU
#define PIN38  &MODULE_P33, 1
#endif

#ifndef PIN39
// Pin: 39
// Net: LEDBar_03
// ECU: DCU
#define PIN39  &MODULE_P00, 7
#endif

#ifndef PIN40
// Pin: 40
// Net: PassengerWindowDown_BTN
// ECU: DCU
#define PIN40  &MODULE_P33, 0
#endif

#ifndef PIN41
// Pin: 41
// Net: LEDBar_04
// ECU: DCU
#define PIN41  &MODULE_P11, 9
#endif

#ifndef PIN42
// Pin: 42
// Net: RearLeftWindowUp_BTN
// ECU: DCU
#define PIN42  &MODULE_P11, 10
#endif

#ifndef PIN43
// Pin: 43
// Net: LEDBar_05
// ECU: DCU
#define PIN43  &MODULE_P11, 11
#endif

#ifndef PIN44
// Pin: 44
// Net: RearLeftWindowDown_BTN
// ECU: DCU
#define PIN44  &MODULE_P33, 3
#endif

#ifndef PIN45
// Pin: 45
// Net: LEDBar_06
// ECU: DCU
#define PIN45  &MODULE_P11, 2
#endif

#ifndef PIN46
// Pin: 46
// Net: RearRightWindowUp_BTN
// ECU: DCU
#define PIN46  &MODULE_P11, 3
#endif

#ifndef PIN47
// Pin: 47
// Net: LEDBar_07
// ECU: DCU
#define PIN47  &MODULE_P11, 6
#endif

#ifndef PIN49
// Pin: 49
// Net: LEDBar_08
// ECU: DCU
#define PIN49  &MODULE_P21, 0
#endif

#ifndef PIN51
// Pin: 51
// Net: LEDBar_09
// ECU: DCU
#define PIN51  &MODULE_P02, 8
#endif

#ifndef PIN53
// Pin: 53
// Net: LEDBar_10
// ECU: DCU
#define PIN53  &MODULE_P11, 12
#endif



//Both boards defined pins

// >>> CAN PINS

#ifndef CANTX
// Pin: CANTX0
// Net: CAN_Tx
// ECU: BCM/DCU
#define CANTX  //&MODULE_P14, 0
#endif

#ifndef CANRX
// Pin: CANRX0
// Net: CAN_Rx
// ECU: BCM/DCU
#define CANRX  //&MODULE_P14, 0
#endif

// >>> GPIO PINS

#ifndef PIN22
// Pin: 22
// Net: Unlock_BTN
// ECU: BCM/DCU
#define PIN22  &MODULE_P14, 0
#endif

#ifndef PIN24
// Pin: 24
// Net: Lock_BTN
// ECU: BCM/DCU
#define PIN24  &MODULE_P15, 6
#endif





#endif /* IOHW_MGR_INCLUDE_IOHW_DEFINITIONS_H_ */
