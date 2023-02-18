// Input output hardware manager module
//
// Here can defined the GPIOs and other peripheral pin route, so this types are later available in any
// section of the code.

#ifndef IOHW_MGR_IOHW_MGR_H_
#define IOHW_MGR_IOHW_MGR_H_


#include "01_MAL/GPIO_Drivers/Include/IfxPort.h"
#include "02_HAL/IoHw_Mgr/Include/IoHw_Definitions.h"


void initGPIOs (void);

#endif
