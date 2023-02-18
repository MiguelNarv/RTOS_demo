// Scheduler tasks module
//
// Here can be made more tasks prototypes

#ifndef SCHEDULER_SCHM_TASKS_H_
#define SCHEDULER_SCHM_TASKS_H_

// Tasks prototypes
void SchM_ReadGPIOs_Task (void);
void SchM_Processing_Task (void);
void SchM_Executing_Task (void);
void SchM_Idle_Task (void);
//void SchM_50MS_Task (void);
//void SchM_100MS_Task (void);

void TaskInit (void);

#endif
