/*
 * doorLockStatusUnit.c
 *
 *  Created on: 10 oct. 2022
 *      Author: uif36101
 */
#include "doorLockStatusUnitDCU.h"
#include "Data_Transfer.h"

typedef enum
{
    Polling_state = 0u, Lock_comparison_state, Execution_state, LastLLUItem
} DLSUStates;

DLSUStates state = Polling_state;
uint8 gpio22 = 0, gpio24 = 0, lockingReqX = 0, lockingReqY1 = 0, lockingReqY2 = 0, doorLockStatus = 0, remoteKeyCMD = 0,
        lockUnlockState = 0, actLockUnlock = 0, id = 0;

DLSUStates polling (void);
DLSUStates lockComparison (void);
DLSUStates execution (void);

void DLSU (void)
{
    switch (state)
    {
        case Polling_state :
            state = polling();
            break;
        case Lock_comparison_state :
            state = lockComparison();
            break;
        case Execution_state :
            state = execution();
            break;
        default :
            // Only for QAC
            break;
    }
}

DLSUStates polling (void)
{
    DLSUStates returnValue = Polling_state;

    id = (uint8) FSM_Data_DCU.dataVector[31];
    gpio22 = (uint8) FSM_Data_DCU.dataVector[10];
    gpio24 = (uint8) FSM_Data_DCU.dataVector[11];

    if (id == 0)
    {
        lockingReqY2 = (uint8) FSM_Data_DCU.dataVector[37];
    }
    else
    {
        lockingReqY1 = 0;
    }

    if (id == 1)
    {
        lockingReqY1 = (uint8) FSM_Data_DCU.dataVector[36];
    }
    else
    {
        lockingReqY2 = 0;
    }

    if (id == 2 || id == 3)
    {
        lockingReqY1 = (uint8) FSM_Data_DCU.dataVector[36];
        lockingReqY2 = (uint8) FSM_Data_DCU.dataVector[37];
    }

    remoteKeyCMD = (uint8) FSM_Data_DCU.dataVector[30];

    if ((gpio22 != gpio24) || (lockingReqY1 != 0 || lockingReqY2 != 0 || remoteKeyCMD != 0))
    {
        returnValue = Lock_comparison_state;
    }
    else if (gpio22 == gpio24)
    {
        returnValue = Polling_state;
    }
    else
    {
        // Only for QAC.
        returnValue = Polling_state;
    }

    return returnValue;
}

DLSUStates lockComparison (void)
{
    DLSUStates returnValue = 0;

    if (remoteKeyCMD == 1)
    {

        //Lock door
        actLockUnlock = 1;
        returnValue = Execution_state;

    }
    else if (remoteKeyCMD == 2 && id == 0)
    {
        //Unlock door
        actLockUnlock = 2;
        returnValue = Execution_state;

    }
    else if (remoteKeyCMD == 3 && id != 0)
    {
        actLockUnlock = 2;
        returnValue = Execution_state;
    }
    else
    {
        //No RemoteKeyCMD request
        if (lockingReqY1 == 1)
        {
            //Lock door
            actLockUnlock = 1;
            returnValue = Execution_state;
        }
        else if (lockingReqY1 == 2)
        {
            //Unlock door
            actLockUnlock = 2;
            returnValue = Execution_state;
        }
        else
        {

            if (lockingReqY2 == 1)
            {
                //Lock door
                actLockUnlock = 1;
                returnValue = Execution_state;
            }
            else if (lockingReqY2 == 2)
            {
                //Unlock door
                actLockUnlock = 2;
                returnValue = Execution_state;
            }
            else
            {

                //No driver request
                if (gpio22 == 1)
                {
                    //Lock door
                    actLockUnlock = 1;
                    returnValue = Execution_state;
                }
                else if (gpio24 == 1)
                {
                    //Unlock door
                    actLockUnlock = 2;
                    returnValue = Execution_state;
                }
                else
                {
                    //Fault, no requests.
                    actLockUnlock = 0;
                    returnValue = Polling_state;
                }
            }
        }

    }

    return returnValue;
}

DLSUStates execution (void)
{
    DLSUStates returnValue = 0;

    FSM_Data_DCU.dataVector[34] = (uint16) actLockUnlock;
    if (id == 0 || id == 1)
    {
        FSM_Data_DCU.dataVector[32] = (uint16) lockingReqX;
    }

    FSM_Data_DCU.dataVector[33] = (uint16) FSM_Data_DCU.dataVector[35];

    returnValue = Polling_state;

    return returnValue;
}

