#ifndef GTM_TOM_PWM_H_
#define GTM_TOM_PWM_H_

/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
#include "01_MAL/PWM_Drivers/Include/IfxGtm_Tom_Pwm.h"

#define PWM_OUTPUTS_NUMBER  10
#define PWM_FREQ          50000
#define BUZ_FREQ          100

void initPWM (void);
void configPwm (uint8 index, IfxGtm_Tom_ToutMap pin);

void setDutyCycle (uint8 index, uint32 dutyCycle);

#endif /* GTM_TOM_PWM_H_ */
