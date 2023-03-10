// Scheduler data types module
//
// This types vary according to the selected mask, time, offset, etc.

#ifndef SCHEDULER_SCHM_TYPES_H_
#define SCHEDULER_SCHM_TYPES_H_

// ID enum
typedef enum
{
  SCHM_TASKID_READGPIOS = 0u,
  SCHM_TASKID_PROCESSING,
  SCHM_TASKID_EXECUTING,
  SCHM_TASKID_IDLE
} SchM_TaskIDType;

// Mask enum
typedef enum
{
  SCHM_MASK_READGPIOS = 0x00000001,
  SCHM_MASK_PROCESSING = 0x00000007,
  SCHM_MASK_EXECUTING = 0x00000007,
  SCHM_MASK_IDLE = 0x0000005
} SchM_TaskMaskType;

// Offset enum
typedef enum
{
  SCHM_OFFSET_READGPIOS = 0u,
  SCHM_OFFSET_PROCESSING = 1u,
  SCHM_OFFSET_EXECUTING = 3u,
  SCHM_OFFSET_IDLE = 5u
} SchM_TaskOffsetType;

// Task state enum
typedef enum
{
  SCHM_TASK_STATE_SUSPENDED = 0u, SCHM_TASK_STATE_READY, SCHM_TASK_STATE_RUNNING
} SchM_TaskStateType;

// General attributes of the task
typedef struct t_SchM_TaskType
{
    SchM_TaskIDType TaskID;
    SchM_TaskMaskType TaskMask;
    SchM_TaskOffsetType TaskOffset;
    SchM_TaskStateType TaskState;
    void (*SchM_Task) (void);
} SchM_Tasks;

#endif
