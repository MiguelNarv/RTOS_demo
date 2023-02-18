#include <DCU/Include/Btn_Unit.h>
#include "IoHw_Mgr.h"
#include "IfxPort.h"
#include "Ifx_Types.h"
#include "Bsp.h"
#include "03_SERVICES/Data_Transfer/Include/Data_Transfer.h"


//#define UNLOCK_BUTTON                      &MODULE_P14,0   // PIN 22
//#define LOCK_BUTTON                        &MODULE_P00,3   // PIN 24

#define DEBOUNCE_COUNTS 10

uint16 lockBtn = 0;
uint16 unlockBtn = 0;

typedef enum
{
  e_pollingGBU = 0u, e_debounce, e_btnRequest
} DoorStates;


static DoorStates door_state = e_pollingGBU;
static uint16 doorCounter = 0;
static uint16 lockReq;


void pollingGBUFcn (void);
void debounceFcn (void);
void btnRequestFcn (void);

void btnUnit (void)
{
  switch (door_state)
  {
    case e_pollingGBU :
      pollingGBUFcn ();
      break;

    case e_debounce :
      debounceFcn ();
      break;

    case e_btnRequest :
      btnRequestFcn ();
      break;

    default :
      // Only for QAC
      break;
  }
}

void pollingGBUFcn (void)
{
  if (lockBtn == 1 && unlockBtn == 0)
  {
    door_state = e_debounce;
  }
  else if (lockBtn == 0 && unlockBtn == 1)
  {
    door_state = e_debounce;
  }
  else
  {
    door_state = e_pollingGBU;
  }
}

void debounceFcn (void)
{
  doorCounter++;
  if (doorCounter <= DEBOUNCE_COUNTS)
  {
    door_state = e_debounce;
  }
  else if (doorCounter > DEBOUNCE_COUNTS)
  {
    lockBtn = FSM_Data_BCM.inputVector [0];
    unlockBtn = FSM_Data_BCM.inputVector [1];
    if (lockBtn == 0 && unlockBtn == 0)
    {
      door_state = e_pollingGBU;
    }
    else if (lockBtn == 1 || unlockBtn == 1)
    {
      door_state = e_btnRequest;
    }
    else
    {
      //just for QAC
    }
    doorCounter = 0;
  }

}

void btnRequestFcn (void)
{
  lockBtn = FSM_Data_DCU.dataVector[10];
  unlockBtn =  FSM_Data_DCU.dataVector[11];
  if (lockBtn == 1 && unlockBtn == 0)
  {
    lockReq = 2;
    door_state = e_btnRequest;
  }
  else if (lockBtn == 0 && unlockBtn == 1)
  {
    lockReq = 1;
    door_state = e_btnRequest;
  }
  else
  {
    lockReq = 0;
    door_state = e_pollingGBU;
    doorCounter = 0;
  }

  // RETURN
  FSM_Data_BCM.dataVector[2] = lockReq;
}
