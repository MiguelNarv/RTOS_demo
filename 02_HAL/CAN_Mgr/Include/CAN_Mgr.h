/********************************************************************************************************************
 * \file MULTICAN.h
 * \copyright Copyright (C) Infineon Technologies AG 2019
 *
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are solely in the form of
 * machine-executable object code generated by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************************************************************/

#ifndef CAM_MGR_H_
#define CAN_MGR_H_ 1

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxMultican_Can.h"
#include "IfxMultican.h"
#include "IfxPort.h"                                             /* For GPIO Port Pin Control                        */
#include "CAN_Unit.h"
/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define TX_MESSAGE_OBJECT_ID        (IfxMultican_MsgObjId)0     /* Source message object ID                          */
#define RX_MESSAGE_OBJECT_ID        (IfxMultican_MsgObjId)1     /* Destination message object ID                     */
#define TX_INTERRUPT_SRC_ID         IfxMultican_SrcId_0         /* Transmit interrupt service request ID             */
#define RX_INTERRUPT_SRC_ID         IfxMultican_SrcId_1         /* Receive interrupt service request ID              */
#define INVALID_DATA_VALUE          (uint32)0xDEADBEEF          /* Used to invalidate RX message data content        */
#define INVALID_ID_VALUE            (uint32)0xFFFFFFFF          /* Used to invalidate RX message ID value            */
#define ISR_PRIORITY_CAN_TX         2                           /* Define the CAN TX interrupt priority              */
#define ISR_PRIORITY_CAN_RX         1                           /* Define the CAN RX interrupt priority              */

/*********************************************************************************************************************/
/*--------------------------------------------------Data Structures--------------------------------------------------*/
/*********************************************************************************************************************/
//typedef struct
//{
//    IfxMultican_Can                 can;                   /* CAN module handle to HW module SFR set                 */
//    IfxMultican_Can_Config          canConfig;             /* CAN module configuration structure                     */
//    IfxMultican_Can_Node            canNode;               /* CAN source node handle data structure                  */
//    IfxMultican_Can_NodeConfig      canNodeConfig;         /* CAN node configuration structure                       */
//    IfxMultican_Can_MsgObj          canTxMsgObj;           /* CAN source message object handle data structure        */
//    IfxMultican_Can_MsgObj          canRxMsgObj;           /* CAN destination message object handle data structure   */
//    IfxMultican_Can_MsgObjConfig    canMsgObjConfig;       /* CAN message object configuration structure             */
//    IfxMultican_Message             txMsg;                 /* Transmitted CAN message structure                      */
//    IfxMultican_Message             rxMsg;                 /* Received CAN message structure                         */
//} AppMulticanType;


/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
void canIsrTxHandler(void);
void canIsrRxHandler(void);
void initMultican(void);
void transmitCanMessage(FrameIdentify,uint32,uint32);
uint32 getBcmDataLow(void);
uint32 getBcmDataHigh(void);
uint32 getDcu01DataLow(void);
uint32 getDcu01DataHigh(void);
uint32 getDcu02DataLow(void);
uint32 getDcu02DataHigh(void);

#endif /* CAN_Mgr_H_ */
