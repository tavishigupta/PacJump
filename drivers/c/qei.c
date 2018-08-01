#include "qei.h"
#include "driver_defines.h"
#include "validate.h"
#include "gpio_port.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

bool qei0_init(void) {
	//enable the port e pd6 and pd7 for sending and receiving the data
	gpio_enable_port(GPIOD_BASE);
	gpio_config_digital_enable(GPIOD_BASE, PD6|PD7);
	gpio_config_enable_input(GPIOD_BASE, PD6|PD7);
	gpio_config_alternate_function(GPIOD_BASE, PD6|PD7);
	gpio_config_port_control(GPIOD_BASE, 
													(GPIO_PCTL_PD6_M | GPIO_PCTL_PD7_M),
													(GPIO_PCTL_PD6_PHA1 | GPIO_PCTL_PD7_PHB1));
	// Turn the clock on using the rcgc_mask
	//SYSCTL->RCGCQEI |= SYSCTL_RCGC1_QEI0; this macro was wrong
	SYSCTL->RCGCQEI |= 0x00000001;

	// Wait for the Peripheral ready reg to indicate its ready
	while( !(SYSCTL->PRQEI & SYSCTL_PRQEI_P0));
	 
	//disable it
	QEI0->CTL &= ~QEI_EN;

	//set max positions in 1 rotation
	QEI0->MAXPOS = 0x63;	
	
	//enable the filter to be maxxed out
	QEI0->CTL |= QEI_FLTR_EN;
	QEI0->CTL |= QEI_FLTR_CNT_MAX;
	//set capture mode to be on both edges
	QEI0->CTL |= QEI_CAP_BOTH_EDGES;
	
	//reenable the peripheral	
	QEI0->CTL |= QEI_EN;
	return true;
}

uint32_t get_qei1_pos(void) {
	return QEI0->POS;
}
