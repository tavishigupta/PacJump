#ifndef __QEI_H__
#define __QEI_H__

#include "driver_defines.h"

#define QEI_EN							0x00000001
#define QEI_FLTR_EN					0x00002000
#define QEI_FLTR_CNT_MAX		0x000F0000
#define QEI_CAP_BOTH_EDGES 	0x00000008

bool qei0_init(void);
uint32_t get_qei1_pos(void);


#endif