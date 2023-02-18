/*
 * LockLEDUnit.c
 *
 *  Created on: 26 sep. 2022
 *      Author: uif36100
 */
#include "LockLEDUnit.h"
#include "Data_Transfer.h"
#include "IoHw_Mgr.h"

typedef enum
{
    Transition_state = 0u, Lock_check_state, Unlock_check_state, Delay_state, Execution_state, LastLLUItem
} LLUStates;

static uint8 actLockUnlock = 0, currentRequest = 0, lockUnlockState = 0, doorLockedInput = 0, doorUnlockedInput = 0;
static LLUStates state = Transition_state;

LLUStates Transition (void);
LLUStates Lock_check (void);
LLUStates Unlock_check (void);
LLUStates Delay (void);
LLUStates Execution (void);

void LLUState (void)
{
    switch (state)
    {
        case Transition_state :
            state = Transition();
            break;
        case Lock_check_state :
            state = Lock_check();
            break;
        case Unlock_check_state :
            state = Unlock_check();
            break;
        case Delay_state :
            state = Delay();
            break;
        case Execution_state :
            state = Execution();
            break;
        default :
            // Only for QAC.
            break;
    }
}

LLUStates Transition (void)
{
    LLUStates returnValue = Transition_state;

    actLockUnlock = (uint8) FSM_Data_DCU.dataVector[34];

    if (actLockUnlock == 0x00)
    {
        returnValue = Transition_state;
    }
    else if (actLockUnlock == 0x01)
    {
        returnValue = Lock_check_state;
    }
    else if (actLockUnlock == 0x02)
    {
        returnValue = Unlock_check_state;
    }
    else
    {
        // Only for QAC.
        returnValue = Transition_state;
    }

    return returnValue;
}

LLUStates Lock_check (void)
{
    LLUStates returnValue = Lock_check_state;

    if (doorLockedInput == 0x01)
    {
        actLockUnlock = 0x00;
        returnValue = Transition_state;
    }
    else if (doorLockedInput == 0x00)
    {
        currentRequest = actLockUnlock;
        returnValue = Delay_state;
    }
    else
    {
        // Only for QAC.
        returnValue = Lock_check_state;
    }

    return returnValue;
}

LLUStates Unlock_check (void)
{
    LLUStates returnValue = Unlock_check_state;

    if (doorUnlockedInput == 0x01)
    {
        actLockUnlock = 0x00;
        returnValue = Transition_state;
    }
    else if (doorUnlockedInput == 0x00)
    {
        currentRequest = actLockUnlock;
        returnValue = Delay_state;
    }
    else
    {
        // Only for QAC.
        returnValue = Unlock_check_state;
    }

    return returnValue;
}


LLUStates Delay (void)
{
    static uint8 counter = 0;
    LLUStates returnValue = Delay_state;

    if(counter >= 12)
    {
        counter = 0;
        returnValue = Execution_state;
    }
    else
    {
        counter ++;
        returnValue = Delay_state;
    }

    return returnValue;
}



LLUStates Execution (void)
{
    LLUStates returnValue = Execution_state;

    if (currentRequest == 0x00)
    {
        // Do nothing.
        returnValue = Transition_state;
    }
    else if (currentRequest == 0x01)
    {
        IfxPort_setPinHigh(PIN26); //LED rojo
        IfxPort_setPinLow(PIN28); // LED verde
        lockUnlockState = 0x01;
        doorUnlockedInput = 0;
        doorLockedInput = 1;
        FSM_Data_DCU.dataVector[35] = lockUnlockState;
        returnValue = Transition_state;
    }
    else if (currentRequest == 0x02)
    {
        IfxPort_setPinHigh(PIN28); // LED verde
        IfxPort_setPinLow(PIN26); //LED rojo
        lockUnlockState = 0x00;
        doorUnlockedInput = 1;
        doorLockedInput = 0;
        FSM_Data_DCU.dataVector[35] = lockUnlockState;
        returnValue = Transition_state;
    }
    else
    {
        // Only for QAC.
        returnValue = Transition_state;
    }

    return returnValue;
}

