/**
 * \file IfxCpu_Intrinsics.h
 * \ingroup IfxLld_Cpu_Intrinsics Intrinsics
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
 * \defgroup IfxLld_Cpu_Intrinsics Intrinsics
 * \ingroup IfxLld_Cpu_Std
 *
 */
#ifndef IFXCPU_INTRINSICS_H
#define IFXCPU_INTRINSICS_H
/******************************************************************************/
#include "../../../../../../Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/Ifx_Types.h"

#if defined(__DCC__)
#include "../../../../../../Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/IfxCpu_IntrinsicsDcc.h"

#elif defined(__HIGHTEC__)
#include "../../../../../../Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/IfxCpu_IntrinsicsGnuc.h"

#elif defined(__TASKING__)
#include "../../../../../../Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/IfxCpu_IntrinsicsTasking.h"

#elif defined(__ghs__)
#include "../../../../../../Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/IfxCpu_IntrinsicsGhs.h"

#else
#error Compiler unsupported
#endif

#define IFX_ALIGN_8   (1)            // Align on 8 bit Boundary
#define IFX_ALIGN_16  (2)            // Align on 16 bit Boundary
#define IFX_ALIGN_32  (4)            // Align on 32 bit Boundary
#define IFX_ALIGN_64  (8)            // Align on 64 bit Boundary
#define IFX_ALIGN_128 (16)           // Align on 128 bit Boundary
#define IFX_ALIGN_256 (32)           // Align on 256 bit Boundary

#define Ifx_AlignOn256(Size) ((((Size) + (IFX_ALIGN_256 - 1)) & (~(IFX_ALIGN_256 - 1))))
#define Ifx_AlignOn128(Size) ((((Size) + (IFX_ALIGN_128 - 1)) & (~(IFX_ALIGN_128 - 1))))
#define Ifx_AlignOn64(Size)  ((((Size) + (IFX_ALIGN_64 - 1)) & (~(IFX_ALIGN_64 - 1))))
#define Ifx_AlignOn32(Size)  ((((Size) + (IFX_ALIGN_32 - 1)) & (~(IFX_ALIGN_32 - 1))))
#define Ifx_AlignOn16(Size)  ((((Size) + (IFX_ALIGN_16 - 1)) & (~(IFX_ALIGN_16 - 1))))
#define Ifx_AlignOn8(Size)   ((((Size) + (IFX_ALIGN_8 - 1)) & (~(IFX_ALIGN_8 - 1))))

#define Ifx_COUNTOF(x)       (sizeof(x) / sizeof(x[0]))

//______________________________________________________________________________

/** Convert context pointer to address pointer
 * \param[in] cx context pointer
 * \return address pointer
 */
IFX_INLINE void *__cx_to_addr(uint32 cx)
{
    uint32 seg_nr = __extru(cx, 16, 4);
    return (void *)__insert(seg_nr << 28, cx, 6, 16);
}


/** Convert address pointer to context pointer
 * \param[in] addr address pointer
 * \return context pointer
 */
IFX_INLINE uint32 __addr_to_cx(void *addr)
{
    uint32 seg_nr, seg_idx;
    seg_nr  = __extru((int)addr, 28, 4) << 16;
    seg_idx = __extru((int)addr, 6, 16);
    return seg_nr | seg_idx;
}


/******************************************************************************/
IFX_INLINE void __ldmst_c(volatile void *address, unsigned mask, unsigned value)
{
    *(volatile uint32 *)address = (*(volatile uint32 *)address & ~(mask)) | (mask & value);
}


/** 32bit load operation
 */
IFX_INLINE uint32 __ld32(void *addr)
{
    return *(volatile uint32 *)addr;
}


/** 32bit store operation
 */
IFX_INLINE void __st32(void *addr, uint32 value)
{
    *(volatile uint32 *)addr = value;
}


/** 64bit load operation
 */
IFX_INLINE uint64 __ld64(void *addr)
{
    return *(volatile uint64 *)addr;
}


/** 64bit store operation
 */
IFX_INLINE void __st64(void *addr, uint64 value)
{
    *(volatile uint64 *)addr = value;
}


/** 64bit load operation which returns the lower and upper 32bit word
 */
IFX_INLINE void __ld64_lu(void *addr, uint32 *valueLower, uint32 *valueUpper)
{
    register uint64 value;
    value       = __ld64(addr);
    *valueLower = (uint32)value;
    *valueUpper = (uint32)(value >> 32);
}


/** 64bit store operation which stores a lower and upper 32bit word
 */
IFX_INLINE void __st64_lu(void *addr, uint32 valueLower, uint32 valueUpper)
{
    register uint64 value = ((uint64)valueUpper << 32) | valueLower;
    __st64(addr, value);
}


/******************************************************************************/
#endif /* IFXCPU_INTRINSICS_H */
