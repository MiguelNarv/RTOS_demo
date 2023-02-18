/*
 * Data_Transfer.c
 *
 *  Created on: 28 sep. 2022
 *      Author: uif36100
 */

#include "03_SERVICES/Data_Transfer/Include/Data_Transfer.h"

FSM_Data_Struct_BCM FSM_Data_BCM;
FSM_Data_Struct_DCU FSM_Data_DCU;

void initDataStruct (void)
{
    for (uint8 i = 0; i < DATAVECTOR_BCM; i++)
    {
        FSM_Data_BCM.dataVector[i] = 0;

    }
    for (uint8 i = 0; i < DATAVECTOR_DCU; i++)
    {
        FSM_Data_DCU.dataVector[i] = 0;

    }
    for (uint8 i = 0; i < DATAVECTOR_DCU; i++)
    {
        FSM_Data_BCM.dataVector[i] = 0;

    }
    for (uint8 i = 0; i < DATAVECTOR_DCU; i++)
    {
        FSM_Data_DCU.dataVector[i] = 0;

    }
    for (uint8 i = 0; i < CANVECTOR_BCM; i++)
    {
        FSM_Data_BCM.canVector[i] = 0;

    }
}

void initIDs (uint8 IDVal)
{
    if (IDVal > 3)
    {
        FSM_Data_DCU.dataVector[31] = 0x00;
    }
    else
    {
        FSM_Data_DCU.dataVector[31] = IDVal;
    }

}
