//
//
//

#include "01_MAL/Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/Ifx_Types.h"
#include "02_HAL/PWM_Mgr/Include/PWM_Mgr.h"

static IfxGtm_Tom_Pwm_Config g_tomConfig [PWM_OUTPUTS_NUMBER];
static IfxGtm_Tom_Pwm_Driver g_tomDriver [PWM_OUTPUTS_NUMBER];

// This function inits the PWM peripheral
void initPWM (void)
{
  IfxGtm_enable (&MODULE_GTM);                                     // Enable GTM
  IfxGtm_Cmu_enableClocks (&MODULE_GTM, IFXGTM_CMU_CLKEN_FXCLK);   // Enable the FXU clock
}

// This function registers the PWM pins. Index from 0 to PWM_OUTPUTS_NUMBER.
void configPwm (uint8 index, IfxGtm_Tom_ToutMap pin)
{
  if (index != 6)
  {

    //Initialize the configuration structure with default parameters
    IfxGtm_Tom_Pwm_initConfig (&g_tomConfig [index], &MODULE_GTM);

    g_tomConfig [index].tom = pin.tom;                                      // Select the TOM depending on the LED
    g_tomConfig [index].tomChannel = pin.channel;                           // Select the channel depending on the LED
    g_tomConfig [index].period = PWM_FREQ;                                // Set the timer period
    g_tomConfig [index].pin.outputPin = &pin;                               // Set the LED port pin as output
    g_tomConfig [index].synchronousUpdateEnabled = TRUE;                    // Enable synchronous update

    IfxGtm_Tom_Pwm_init (&g_tomDriver [index], &g_tomConfig [index]);                // Initialize the GTM TOM
    IfxGtm_Tom_Pwm_start (&g_tomDriver [index], TRUE);                       // Start the PWM
  }
  else
  {
    //Initialize the configuration structure with default parameters
    IfxGtm_Tom_Pwm_initConfig (&g_tomConfig [index], &MODULE_GTM);

    g_tomConfig [index].tom = pin.tom;                                      // Select the TOM depending on the LED
    g_tomConfig [index].tomChannel = pin.channel;                           // Select the channel depending on the LED
    g_tomConfig [index].period = BUZ_FREQ;                                // Set the timer period
    g_tomConfig [index].pin.outputPin = &pin;                               // Set the LED port pin as output
    g_tomConfig [index].synchronousUpdateEnabled = TRUE;                    // Enable synchronous update

    IfxGtm_Tom_Pwm_init (&g_tomDriver [index], &g_tomConfig [index]);                // Initialize the GTM TOM
    IfxGtm_Tom_Pwm_start (&g_tomDriver [index], TRUE);                       // Start the PWM
  }
}


// This function sets the duty cycle of the PWM. Index from 0 to PWM_OUTPUTS_NUMBER.
void setDutyCycle (uint8 index, uint32 dutyCycle)
{
  g_tomConfig [index].dutyCycle = dutyCycle;                              // Change the value of the duty cycle
  IfxGtm_Tom_Pwm_init (&g_tomDriver [index], &g_tomConfig [index]);                // Re-initialize the PWM
}
