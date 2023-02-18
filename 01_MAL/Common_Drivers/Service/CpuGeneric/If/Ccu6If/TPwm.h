/**
 * \file TPwm.h
 * \brief TPWM interface
 *
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 * $Date: 2014-02-27 20:08:18 GMT$
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * \defgroup library_srvsw_if_tpwm TPWM interface
 * \ingroup library_srvsw_if
 *
 */

#ifndef TPWM_H_
#define TPWM_H_ 1

#include "../../../../../Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/Ifx_Types.h"

typedef struct TPwm_s TPwm;
typedef void        (*TPwm_Start)(TPwm *handle);
typedef void        (*TPwm_Pause)(TPwm *handle);
typedef void        (*TPwm_Resume)(TPwm *handle);
typedef void        (*TPwm_Stop)(TPwm *handle);

typedef struct
{
    TPwm_Start  start;
    TPwm_Pause  pause;
    TPwm_Resume resume;
    TPwm_Stop   stop;
} TPwm_Functions;

/** \brief Structure of the TPwm interface */
struct TPwm_s
{
    float32        frequency;      /**< \brief Actual frequency */
    Ifx_TimerValue period;         /**< \brief Actual timer period */
#if IFX_CFG_USE_STANDARD_INTERFACE
    TPwm_Functions functions;      /**< \brief Actual timer period */
#endif
};

/** \brief Configuration structure of the TPwm interface */
typedef struct
{
    float32         frequency;     /**< \brief Specify expected PWM frequency in Hertz */
    Ifx_TimerValue  waitingTime;   /**< \brief Specify the expected ticks before timer starts (TWAIT) */
    Ifx_TimerValue  activeCount;   /**< \brief Specify active PWM period (TCOUNT) */
    Ifx_TimerValue  period;        /**< \brief Specify expected PWM period in ticks. */
    Ifx_ActiveState activeState;   /**< \brief Active state select for PWM output. Active high means that the PWM edge is rising at the elapsed of waitingTicks */
} TPwm_Config;

#if IFX_CFG_USE_STANDARD_INTERFACE
IFX_INLINE void TPwm_start(TPwm *handle)  {handle->functions.start(handle); }
IFX_INLINE void TPwm_pause(TPwm *handle)  {handle->functions.pause(handle); }
IFX_INLINE void TPwm_resume(TPwm *handle) {handle->functions.resume(handle); }
IFX_INLINE void TPwm_stop(TPwm *handle)   {handle->functions.stop(handle); }
#endif

#endif /* TPWM_H_ */
