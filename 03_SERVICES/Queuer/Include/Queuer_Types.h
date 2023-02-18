/*
 * Queuer_Types.h
 *
 *  Created on: 26 sep. 2022
 *      Author: uif36100
 */

#ifndef QUEUER_QUEUER_TYPES_H_
#define QUEUER_QUEUER_TYPES_H_

#include "01_MAL/Common_Drivers/iLLD/TC27D/Tricore/Cpu/Std/Ifx_Types.h"

// Definition of the queue size.
#define QUEUE_SIZE 6u
//
typedef enum
{
  noRequest = 0u, requestType1, requestType2, requestType3
} e_RequestType;

typedef enum
{
  e_false = 0u, e_true, e_error, e_full, e_empty
} e_QueueStatus;

typedef struct
{
    signed char first;
    signed char last;
    uint8 vector [QUEUE_SIZE];
} t_QUEUE;

#endif /* QUEUER_QUEUER_TYPES_H_ */
