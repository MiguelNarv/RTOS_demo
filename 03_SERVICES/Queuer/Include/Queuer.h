/*
 * Queuer.h
 *
 *  Created on: 26 sep. 2022
 *      Author: uif36100
 */

#ifndef QUEUER_QUEUER_H_
#define QUEUER_QUEUER_H_

#include "03_SERVICES/Queuer/Include/Queuer_Types.h"

// Function prototypes.
void initializeQueue (t_QUEUE* p_queue);
e_QueueStatus pushQueue (t_QUEUE* p_queue, uint8 request);
e_QueueStatus pushForceIndexQueue (t_QUEUE* p_queue, uint8 request, uint8 index);
e_QueueStatus pushForceQueue (t_QUEUE* p_queue, uint8 request);
uint8 fetchQueue (t_QUEUE* p_queue);
void flushAllQueue (t_QUEUE* p_queue);

#endif /* QUEUER_QUEUER_H_ */
