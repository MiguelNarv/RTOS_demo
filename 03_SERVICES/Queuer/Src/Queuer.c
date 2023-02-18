// TODO Description

#include "03_SERVICES/Queuer/Include/Queuer.h"

// Private function definition.
void shiftRightQueue (t_QUEUE* p_queue, uint8 index);
void shiftLeftQueue (t_QUEUE* p_queue, uint8 index);
e_QueueStatus isFull (t_QUEUE* p_queue);
e_QueueStatus isEmpty (t_QUEUE* p_queue);

void initializeQueue (t_QUEUE* p_queue)
{
  p_queue->first = -1;
  p_queue->last = -1;

  flushAllQueue (p_queue);
}

e_QueueStatus pushQueue (t_QUEUE* p_queue, uint8 request)
{
  e_QueueStatus status = e_error;

  // p_queue full status check. status can be found on queue_datatypes.h
  status = isFull (p_queue);

  // status validation.
  if (status == e_true)
  {
    // The p_queue is full, no elements can be queued.
    status = e_full;
  }
  else if (status == e_false)
  {
    // The p_queue is not full, new elements can be queued.

    // p_queue empty status check.
    status = isEmpty (p_queue);

    if (status == e_true)
    {
      // The p_queue is empty, so the first p_queue state is initialized to 0.
      // This and last states help us to get and validate the status of the p_queue in
      // functions isEmpty and isFull.
      p_queue->first = 0;
    }
    // The value of the last state is incresead by 1.
    p_queue->last = p_queue->last + 1;

    // The request type is added into the last position available of the p_queue.vector element.
    p_queue->vector [p_queue->last] = request;

  }
  else
  {

    // The p_queue status is neither empty nor full. An error has occured.
    status = e_error;
  }

  return status;

}

e_QueueStatus pushForceIndexQueue (t_QUEUE* p_queue, uint8 request, uint8 index)
{
  e_QueueStatus status = e_error;

  // p_queue full status check. status can be found on queue_datatypes.h
  status = isFull (p_queue);

  // status validation.
  if (status == e_true)
  {
    // The p_queue is full, no elements can be queued.
    status = e_full;
  }
  else if (status == e_false)
  {
    // The p_queue is not full, new elements can be queued.

    // p_queue empty status check.
    status = isEmpty (p_queue);

    if (status == e_true)
    {
      // The p_queue is empty, so the first p_queue state is initialized to 0.
      // This and last states help us to get and validate the status of the p_queue in
      // functions isEmpty and isFull.
      p_queue->first = 0;
    }
    // The value of the last state is increased by 1.
    p_queue->last = p_queue->last + 1;

    shiftLeftQueue (p_queue, index);

    // The request type is added into the last position available of the p_queue.vector element.
    p_queue->vector [index + 1] = request;

  }
  else
  {

    // The p_queue status is neither empty nor full. An error has occured.
    status = e_error;
  }

  return status;
}

e_QueueStatus pushForceQueue (t_QUEUE* p_queue, uint8 request)
{
  e_QueueStatus status = e_error;

  // p_queue full status check. status can be found on queue_datatypes.h
  status = isFull (p_queue);

  // status validation.
  if (status == e_true)
  {
    // The p_queue is full, no elements can be queued.
    status = e_full;
  }
  else if (status == e_false)
  {
    // The p_queue is not full, new elements can be queued.

    // p_queue empty status check.
    status = isEmpty (p_queue);

    if (status == e_true)
    {
      // The p_queue is empty, so the first p_queue state is initialized to 0.
      // This and last states help us to get and validate the status of the p_queue in
      // functions isEmpty and isFull.
      p_queue->first = 0;
    }
    // The value of the last state is incresead by 1.
    p_queue->last = p_queue->last + 1;

    shiftLeftQueue (p_queue, 0);

    // The request type is added into the last position available of the p_queue.vector element.
    p_queue->vector [0] = request;

  }
  else
  {

    // The p_queue status is neither empty nor full. An error has occured.
    status = e_error;
  }

  return status;
}

uint8 fetchQueue (t_QUEUE* p_queue)
{
  e_QueueStatus status = e_error;
  uint8 fetch;

  // p_queue empty status check. status can be found on queue_datatypes.h
  status = isEmpty (p_queue);

  if (status == e_true)
  {
    // If the p_queue is empty do nothing.
  }
  else
  {
    // Fetches the initial element of the p_queue.
    fetch = p_queue->vector [0];

    shiftRightQueue (p_queue, 0);

  }

  // The fetched value is returned.
  return fetch;
}

void flushAllQueue (t_QUEUE* p_queue)
{
  // p_queue.vector (QUEUE_SIZE) elements initialization to 0.
  for (size_t i = 0; i < QUEUE_SIZE; i++)
  {
    (void) (p_queue->vector [i] = noRequest);
  }
}

void shiftRightQueue (t_QUEUE* p_queue, uint8 index)
{
  // Shifts to the right, from last to initial position, every element of the p_queue except the last element.
  for (size_t i = index; i < (QUEUE_SIZE - 1); i++)
  {
    p_queue->vector [i] = p_queue->vector [i + 1];
  }

  // The last element of the p_queue is set to noRequest (0).
  p_queue->vector [QUEUE_SIZE - 1] = 0;

  // The last value state of the p_queue is decreased by 1, so a new space is available.
  p_queue->last = p_queue->last - 1;
}

void shiftLeftQueue (t_QUEUE* p_queue, uint8 index)
{
  //uint8 lastval = p_queue->vector [index];

  // Shifts to the right, from last to initial position, every element of the p_queue except the last element.
  for (size_t i = (QUEUE_SIZE - 1); i >= (index + 1); i--)
  {
    p_queue->vector [i] = p_queue->vector [i - 1];
  }

  // The last value state of the p_queue is decreased by 1, so a new space is available.
  p_queue->last = p_queue->last - 1;
}

e_QueueStatus isFull (t_QUEUE* p_queue)
{
  e_QueueStatus status = e_error;

  // Validation of the last state of the p_queue.
  if (p_queue->last == (QUEUE_SIZE))
  {
    // The last element is equal to the available spaces in the p_queue, so the p_queue is full.
    status = e_true;
  }
  else
  {
    // The last element is not equal to the available spaces in the p_queue, so the p_queue is not full.
    status = e_false;
  }

  return status;
}

e_QueueStatus isEmpty (t_QUEUE* p_queue)
{
  e_QueueStatus status = e_error;

  // Validation of the last state of the p_queue.
  if (p_queue->last == -1)
  {
    // The last element is equal to -1 (Initialization value), so no element has been added. The p_queue is empty.
    status = e_true;
  }
  else
  {
    // The last element is not equal to -1, so a new element has been added and the p_queue is no longer empty.
    status = e_false;
  }

  return status;
}

