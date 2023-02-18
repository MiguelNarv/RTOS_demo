/**
 * \file Ifx_Console.h
 * \brief Main Console module header file
 *
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 * $Date: 2014-02-28 14:15:36 GMT$
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
 * \defgroup library_srvsw_sysse_comm_console Console
 * This module implements "Main Console" functions
 * \ingroup library_srvsw_sysse_comm
 *
 */
#ifndef IFX_CONSOLE_H
#define IFX_CONSOLE_H               1

#include "../../../../../Common_Drivers/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.h"

//----------------------------------------------------------------------------------------
#if !defined(IFX_CFG_CONSOLE_INDENT_SIZE)
#define IFX_CFG_CONSOLE_INDENT_SIZE (4) /**<\brief Default indentation/alignment size */
#endif

typedef struct
{
    IfxStdIf_DPipe *standardIo;       /**<\brief Pointer to the \ref IfxStdIf_DPipe object used as general console */
    sint16          align;            /**<\brief Variable for storing the actual (left)indentation level of the \ref Ifx_g_console */
} Ifx_Console;

IFX_EXTERN Ifx_Console Ifx_g_console; /**< \brief Default main console global variable */

//----------------------------------------------------------------------------------------
/** \addtogroup library_srvsw_sysse_comm_console
 * \{ */

#ifndef CONSOLE

/* FIXME (Alann to discuss with Dian) there is no requirement to define multiple console, CONSOLE should be removed, and APIs used instead */
/** \brief Alias \ref Ifx_g_console object (by value) */
#define CONSOLE Ifx_g_console

/** \brief Return pointer to the default console object
 *
 * User can override this function by defining new \ref CONSOLE macro and this function
 * externally, e.g. inside Ifx_Cfg.h file.*/
IFX_INLINE IfxStdIf_DPipe *Ifx_Console_getIo(void)
{
    return Ifx_g_console.standardIo;
}


#endif

IFX_EXTERN void    Ifx_Console_init(IfxStdIf_DPipe *standardIo);
IFX_EXTERN boolean Ifx_Console_print(pchar format, ...);
IFX_EXTERN boolean Ifx_Console_printAlign(pchar format, ...);

/**
 * \brief Decrement the alignment/indentation using the given value
 * \param value the increment. If value == 0, \ref IFX_CFG_CONSOLE_INDENT_SIZE will be used.
 */
IFX_INLINE void Ifx_Console_decrAlign(sint16 value)
{
    value               = (sint16)(Ifx_g_console.align - ((value == 0U) ? IFX_CFG_CONSOLE_INDENT_SIZE : value));
    Ifx_g_console.align = (value > 0) ? value : 0;
}


/**
 * \brief Increment the alignment/indentation using the given value
 * \param value the increment. If value == 0, \ref IFX_CFG_CONSOLE_INDENT_SIZE will be used.
 */
IFX_INLINE void Ifx_Console_incrAlign(sint16 value)
{
    Ifx_g_console.align += ((value == 0) ? (sint16)IFX_CFG_CONSOLE_INDENT_SIZE : value);
}


/** \} */
//----------------------------------------------------------------------------------------
#endif
