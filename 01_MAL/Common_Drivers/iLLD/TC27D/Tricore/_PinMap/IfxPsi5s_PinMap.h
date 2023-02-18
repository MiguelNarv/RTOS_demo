/**
 * \file IfxPsi5s_PinMap.h
 * \brief PSI5S I/O map
 * \ingroup IfxLld_Psi5s
 *
 * \version iLLD_1_0_1_12_0_1
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
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
 * \defgroup IfxLld_Psi5s_pinmap PSI5S Pin Mapping
 * \ingroup IfxLld_Psi5s
 */

#ifndef IFXPSI5S_PINMAP_H
#define IFXPSI5S_PINMAP_H

#include "../../../../../Common_Drivers/iLLD/TC27D/Tricore/_Impl/IfxPsi5s_cfg.h"
#include "../../../../../Common_Drivers/Infra/Sfr/TC27D/_Reg/IfxPsi5s_reg.h"
#include "../../../../../GPIO_Drivers/Include/IfxPort.h"

/** \addtogroup IfxLld_Psi5s_pinmap
 * \{ */

/** \brief RX pin mapping structure */
typedef const struct
{
    Ifx_PSI5S*         module;    /**< \brief Base address */
    IfxPort_Pin        pin;       /**< \brief Port pin */
    Ifx_RxSel          select;    /**< \brief Input multiplexer value */
} IfxPsi5s_Rx_In;

/** \brief TX pin mapping structure */
typedef const struct
{
    Ifx_PSI5S*         module;    /**< \brief Base address */
    IfxPort_Pin        pin;       /**< \brief Port pin */
    IfxPort_OutputIdx  select;    /**< \brief Port control code */
} IfxPsi5s_Tx_Out;

/** \brief CLK pin mapping structure */
typedef const struct
{
    Ifx_PSI5S*         module;    /**< \brief Base address */
    IfxPort_Pin        pin;       /**< \brief Port pin */
    IfxPort_OutputIdx  select;    /**< \brief Port control code */
} IfxPsi5s_Clk_Out;

IFX_EXTERN IfxPsi5s_Clk_Out IfxPsi5s_CLK_P02_4_OUT;  /**< \brief PSI5S_CLK: PSI5-S output */
IFX_EXTERN IfxPsi5s_Clk_Out IfxPsi5s_CLK_P33_10_OUT;  /**< \brief PSI5S_CLK: PSI5-S output */
IFX_EXTERN IfxPsi5s_Rx_In IfxPsi5s_RXA_P00_3_IN;  /**< \brief PSI5S_RXA: PSI5-S input */
IFX_EXTERN IfxPsi5s_Rx_In IfxPsi5s_RXB_P02_5_IN;  /**< \brief PSI5S_RXB: PSI5-S input */
IFX_EXTERN IfxPsi5s_Rx_In IfxPsi5s_RXC_P33_5_IN;  /**< \brief PSI5S_RXC: PSI5-S input */
IFX_EXTERN IfxPsi5s_Tx_Out IfxPsi5s_TX_P00_4_OUT;  /**< \brief PSI5S_TX: PSI5-S output */
IFX_EXTERN IfxPsi5s_Tx_Out IfxPsi5s_TX_P02_6_OUT;  /**< \brief PSI5S_TX: PSI5-S output */
IFX_EXTERN IfxPsi5s_Tx_Out IfxPsi5s_TX_P33_6_OUT;  /**< \brief PSI5S_TX: PSI5-S output */

/** \brief Table dimensions */
#define IFXPSI5S_PINMAP_NUM_MODULES 1
#define IFXPSI5S_PINMAP_CLK_OUT_NUM_ITEMS 2
#define IFXPSI5S_PINMAP_RX_IN_NUM_ITEMS 3
#define IFXPSI5S_PINMAP_TX_OUT_NUM_ITEMS 3


/** \brief IfxPsi5s_Clk_Out table */
IFX_EXTERN const IfxPsi5s_Clk_Out *IfxPsi5s_Clk_Out_pinTable[IFXPSI5S_PINMAP_NUM_MODULES][IFXPSI5S_PINMAP_CLK_OUT_NUM_ITEMS];

/** \brief IfxPsi5s_Rx_In table */
IFX_EXTERN const IfxPsi5s_Rx_In *IfxPsi5s_Rx_In_pinTable[IFXPSI5S_PINMAP_NUM_MODULES][IFXPSI5S_PINMAP_RX_IN_NUM_ITEMS];

/** \brief IfxPsi5s_Tx_Out table */
IFX_EXTERN const IfxPsi5s_Tx_Out *IfxPsi5s_Tx_Out_pinTable[IFXPSI5S_PINMAP_NUM_MODULES][IFXPSI5S_PINMAP_TX_OUT_NUM_ITEMS];

/** \} */

#endif /* IFXPSI5S_PINMAP_H */
