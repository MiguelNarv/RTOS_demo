/*
 * Data_Transfer.h
 *
 *  Created on: 28 sep. 2022
 *      Author: uif36100
 */

#ifndef DATA_TRANSFER_DATA_TRANSFER_H_
#define DATA_TRANSFER_DATA_TRANSFER_H_

// ---
#ifndef DATAVECTOR_BCM
#define DATAVECTOR_BCM 3
#endif


#ifndef INPUTVECTOR_BCM
#define INPUTVECTOR_BCM 3
#endif

// ---
#ifndef DATAVECTOR_DCU
#define DATAVECTOR_DCU 45
#endif


#ifndef CANVECTOR_BCM
#define CANVECTOR_BCM 4
#endif


#include  "01_MAL/Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/Ifx_Types.h"

typedef struct
{
    uint16 dataVector [DATAVECTOR_BCM];
    uint16 inputVector [INPUTVECTOR_BCM];
    uint16 canVector [CANVECTOR_BCM];
} FSM_Data_Struct_BCM;

typedef struct
{
    uint16 dataVector [DATAVECTOR_DCU];
    uint16 canVector [CANVECTOR_BCM];
} FSM_Data_Struct_DCU;


void initDataStruct (void);
void initIDs (uint8 IDVal);

extern FSM_Data_Struct_BCM FSM_Data_BCM;
extern FSM_Data_Struct_DCU FSM_Data_DCU;

#endif
