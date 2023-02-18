/**
 * \file IfxEmem.h
 * \brief EMEM  basic functionality
 * \ingroup IfxLld_Emem
 *
 * \version iLLD_1_0_1_12_0_1
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
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
 * \defgroup IfxLld_Emem_Std_Enumerations Enumerations
 * \ingroup IfxLld_Emem_Std
 * \defgroup IfxLld_Emem_Std_Module Module Functions
 * \ingroup IfxLld_Emem_Std
 */

#ifndef IFXEMEM_H
#define IFXEMEM_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "../../../../../../Common_Drivers/iLLD/TC27D/Tricore/_Impl/IfxEmem_cfg.h"
#include "../../../../../../Common_Drivers/iLLD/TC27D/Tricore/Scu/Std/IfxScuWdt.h"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Emem_Std_Enumerations
 * \{ */
/** \brief EMEM lock state defined in MODULE_EMEM.SBRCTR.B.STBLOCK.
 */
typedef enum
{
    IfxEmem_LockedState_locked   = 0, /**< \brief EMEM locked state. */
    IfxEmem_LockedState_unlocked = 1  /**< \brief EMEM unlocked state. */
} IfxEmem_LockedState;

/** \brief EMEM module clock enabled or disabled state defined in MODULE_EMEM.CLC.B.DISR.
 */
typedef enum
{
    IfxEmem_State_disabled = 0,  /**< \brief EMEM module clock disabled state. */
    IfxEmem_State_enabled  = 1   /**< \brief EMEM module clock enabled state. */
} IfxEmem_State;

/** \brief EMEM tile configuration mode defined in MODULE_EMEM.TILECONFIG.B.Tx( x = 0,1,..).
 */
typedef enum
{
    IfxEmem_TileConfigMode_calibMode = 0  /**< \brief EMEM tile mode to calibration memory. */
} IfxEmem_TileConfigMode;

/** \brief Tile Number
 */
typedef enum
{
    IfxEmem_TileNumber_0 = 0,      /**< \brief Tile Number0  */
    IfxEmem_TileNumber_1,          /**< \brief Tile Number1  */
    IfxEmem_TileNumber_2,          /**< \brief Tile Number2  */
    IfxEmem_TileNumber_3,          /**< \brief Tile Number3  */
    IfxEmem_TileNumber_4,          /**< \brief Tile Number4  */
    IfxEmem_TileNumber_5,          /**< \brief Tile Number5  */
    IfxEmem_TileNumber_6,          /**< \brief Tile Number6  */
    IfxEmem_TileNumber_7,          /**< \brief Tile Number7  */
    IfxEmem_TileNumber_8,          /**< \brief Tile Number8  */
    IfxEmem_TileNumber_9,          /**< \brief Tile Number9  */
    IfxEmem_TileNumber_10,         /**< \brief Tile Number10  */
    IfxEmem_TileNumber_11,         /**< \brief Tile Number11  */
    IfxEmem_TileNumber_12,         /**< \brief Tile Number12  */
    IfxEmem_TileNumber_13,         /**< \brief Tile Number13  */
    IfxEmem_TileNumber_14,         /**< \brief Tile Number14  */
    IfxEmem_TileNumber_15          /**< \brief Tile Number15  */
} IfxEmem_TileNumber;

/** \} */

/** \addtogroup IfxLld_Emem_Std_Module
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Returns the status of module enabled or disabled
 * \return Status (TRUE / FALSE)
 */
IFX_INLINE boolean IfxEmem_isModuleEnabled(void);

/** \brief Sets all EMEM tiles to calibration memory mode.
 * \param mode EMEM tile configuration mode.
 * \param tile tile number
 * \return None
 */
IFX_INLINE void IfxEmem_setTileConfigMode(const IfxEmem_TileConfigMode mode, IfxEmem_TileNumber tile);

/** \brief Sets Unlock standby lock flag.
 * \param flag Unlock standby lock flag value.
 * \return None
 */
IFX_INLINE void IfxEmem_setUnlockStandbyLockFlag(const uint8 flag);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Gets the EMEM stand RAM lock state.
 * \return EMEM stand RAM lock state.
 */
IFX_EXTERN IfxEmem_LockedState IfxEmem_getLockedState(void);

/** \brief Sets state of the EMEM module clock.
 * Note: Do not use this API for enabling and disabling EMEM without handling Endinit protection in application.
 * for complete enable and disable of EMEM with endint protection handling, please use the following APIs
 * /ref IfxEmem_enableModule
 * /ref IfxEmem_disableModule
 * \param state EMEM module clock enabled or disabled state.
 * \return None
 */
IFX_EXTERN void IfxEmem_setClockEnableState(const IfxEmem_State state);

/** \} */

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE boolean IfxEmem_isModuleEnabled(void)
{
    return (MODULE_EMEM.CLC.B.DISS == 0) ? TRUE : FALSE;
}


IFX_INLINE void IfxEmem_setTileConfigMode(const IfxEmem_TileConfigMode mode, IfxEmem_TileNumber tile)
{
    uint32 shift = tile * 2;
    uint32 mask  = ~(0x3 << shift);
    uint32 value = (uint32)mode << shift;
    MODULE_EMEM.TILECONFIG.U = (MODULE_EMEM.TILESTATE.U & mask) | value;
}


IFX_INLINE void IfxEmem_setUnlockStandbyLockFlag(const uint8 flag)
{
    if (8 > flag)
    {
        MODULE_EMEM.SBRCTR.B.STBULK = flag;
    }
}


#endif /* IFXEMEM_H */
