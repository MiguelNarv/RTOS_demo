/*============================================================================*/
/*                        ADC READING                                         */
/*============================================================================*/
/* C Source:        ADC_Single_Channel.c                                      */
/* version:         1                                                         */
/* created_by:      uif36101                                                  */
/* date_created:    Sep 24 2022                                               */
/*============================================================================*/
/* DESCRIPTION : C source file                                                */
/*============================================================================*/
/* FUNCTION COMMENT : This file is for acquiring the readings from ADC for the*/
/*  speed algorithm                                                           */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  0.2.2    | 03/10/2022  |                               | D. Licona        */
/* Integration under Continuous CM                                            */
/*============================================================================*/

#include <ADC_Drivers/Include/IfxVadc_Adc.h>
#include "ADC_Single_Channel.h"
#include "IoHw_Definitions.h"
#include "03_SERVICES/Data_Transfer/Include/Data_Transfer.h"

/*********************************************************************************************************************/
/*----------------------------------Functions macros, constants, types and datas-------------------------------------*/
/*********************************************************************************************************************/

const float m = 255.75 / 4095;

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/


typedef struct
{
    IfxVadc_Adc               vadc;               /* VADC configuration     */
    IfxVadc_Adc_Group         adcGroup;           /* Group configuration    */
    IfxVadc_Adc_ChannelConfig adcChannelConfig;   /* Channel configuration  */
    IfxVadc_Adc_Channel       adcChannel;         /* Channel                */
} ApplicationVadcBackgroundScan;


ApplicationVadcBackgroundScan g_vadcBackgroundScan;

//----------
uint16 indicateConversionValue(void);



/**************************************************************
 *  Name                 : indicateConversionValue
 *  Description          : This function retrieves the conver-
 *  sion value
 *  Parameters           : [void]
 *  Return               : [void]
 *  Critical/explanation : [yes / No]
 **************************************************************/
uint16 indicateConversionValue (void)
{
    volatile Ifx_VADC_RES conversionResult;
    volatile uint16 analogSpeed;

    //Retrieve the conversion value until valid flag of the result register is true
    do
    {
        conversionResult = IfxVadc_Adc_getResult(&g_vadcBackgroundScan.adcChannel);
    }while (!conversionResult.B.VF);
    analogSpeed = conversionResult.B.RESULT;
    return analogSpeed;
}

/**************************************************************
 *  Name                 : vadcBackgroundScanInit
 *  Description          : The VADC module and group are initia-
 *  lized
 *  Parameters           : [void]
 *  Return               : [void]
 *  Critical/explanation : [yes / No]
 **************************************************************/
void vadcBackgroundScanInit (void)
{
    // VADC module configuration
    // Create VADC configuration
    IfxVadc_Adc_Config adcConfig;

    // Initialize the VADC configuration with default values
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    // Initialize the VADC module using the VADC configuration
    IfxVadc_Adc_initModule(&g_vadcBackgroundScan.vadc, &adcConfig);

    // VADC group configuration
    // Create group configuration
    IfxVadc_Adc_GroupConfig adcGroupConfig;

    // Initialize the group configuration with default values
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &g_vadcBackgroundScan.vadc);

    // Define which ADC group is going to be used
    adcGroupConfig.groupId = VADC_GROUP;
    adcGroupConfig.master = VADC_GROUP;

    // Enable background scan source
    adcGroupConfig.arbiter.requestSlotBackgroundScanEnabled = TRUE;

    // Enable background auto scan mode
    adcGroupConfig.backgroundScanRequest.autoBackgroundScanEnabled = TRUE;

    // Enable the gate in "always" mode (no edge detection)
    adcGroupConfig.backgroundScanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;

    // Initialize the group using the group configuration
    IfxVadc_Adc_initGroup(&g_vadcBackgroundScan.adcGroup, &adcGroupConfig);
}


/**************************************************************
 *  Name                 : vadcBackgroundScanRun
 *  Description          : The input channels to be used are se-
 *  tup and the VADC is set into run mode
 *  Parameters           : [void]
 *  Return               : [void]
 *  Critical/explanation : [yes / No]
 **************************************************************/
void vadcBackgroundScanRun (void)
{
    // Initialize the channel configuration of application handle g_vadcBackgroundScan with default values
    IfxVadc_Adc_initChannelConfig(&g_vadcBackgroundScan.adcChannelConfig, &g_vadcBackgroundScan.adcGroup);

    g_vadcBackgroundScan.adcChannelConfig.channelId = (IfxVadc_ChannelId) CHANNEL_ID;
    g_vadcBackgroundScan.adcChannelConfig.resultRegister = (IfxVadc_ChannelResult) CHANNEL_RESULT_REGISTER;
    g_vadcBackgroundScan.adcChannelConfig.backgroundChannel = TRUE;



    // Initialize the channel of application handle g_VadcBackgroundScan using the channel configuration
    IfxVadc_Adc_initChannel(&g_vadcBackgroundScan.adcChannel, &g_vadcBackgroundScan.adcChannelConfig);

    // Enable background scan for the channel
    IfxVadc_Adc_setBackgroundScan(&g_vadcBackgroundScan.vadc, &g_vadcBackgroundScan.adcGroup,
            (1 << (IfxVadc_ChannelId) CHANNEL_ID), (1 << (IfxVadc_ChannelId) CHANNEL_ID));

    // Start background scan conversion
    IfxVadc_Adc_startBackgroundScan(&g_vadcBackgroundScan.vadc);
}

/**************************************************************
 *  Name                 : speedCalculation
 *  Description          : This function converts analog read-
 *  ings to digital value
 *  Parameters           : [void]
 *  Return               : [digitalSpeed]
 *  Critical/explanation : [No / No]
 **************************************************************/
uint16 speedCalculation (void)
{
    uint16 digitalSpeed = 0;
    uint16 analogSpeed = 0;
    analogSpeed = (uint16) indicateConversionValue();
    digitalSpeed = (analogSpeed * m);
    return digitalSpeed;
}
