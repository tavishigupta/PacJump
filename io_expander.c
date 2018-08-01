#include "io_expander.h"
#include "validate.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

bool io_expander_init(void) {
	if(gpio_enable_port(IO_EXPANDER_GPIO_BASE) == false)
  {
    return false;
  }
  
  // Configure SCL 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PCTL_M, IO_EXPANDER_I2C_SCL_PIN_PCTL)== false)
  {
    return false;
  }
  
  // Configure SDA 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_open_drain(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PCTL_M, IO_EXPANDER_I2C_SDA_PIN_PCTL)== false)
  {
    return false;
  }
    
  //  Initialize the I2C peripheral
  if( initializeI2CMaster(IO_EXPANDER_I2C_BASE)!= I2C_OK)
  {
    return false;
  }
	
  return true;
}

void io_expander_en_interrupts() {
	gpio_enable_port(IO_EXPANDER_IRQ_GPIO_BASE);
	gpio_config_digital_enable(IO_EXPANDER_IRQ_GPIO_BASE, PF0);
	gpio_config_enable_input(IO_EXPANDER_IRQ_GPIO_BASE, PF0);
	gpio_config_falling_edge_irq(IO_EXPANDER_IRQ_GPIO_BASE, PF0);
	NVIC_SetPriority(GPIOF_IRQn, 0);
	NVIC_EnableIRQ(GPIOF_IRQn);
	GPIOF->ICR |= PF0;
	io_expander_read_reg(MCP23017_GPIOB_R);
}

void config_up_down_buttons() {
	io_expander_write_reg(MCP23017_IODIRB_R, 0xFF);
	io_expander_write_reg(MCP23017_GPINTENB_R, 0x0F);
	io_expander_write_reg(MCP23017_DEFVALB_R, 0xFF);
	io_expander_write_reg(MCP23017_INTCONB_R, 0x00);
	io_expander_write_reg(MCP23017_GPPUB_R, 0xFF);
}

void io_expander_write_reg(uint8_t reg, uint8_t data) {
	//set slave
	i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);
 
	// Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(IO_EXPANDER_I2C_BASE)) {put_string("w");};
 
	// Send the reg Address
  i2cSendByte( IO_EXPANDER_I2C_BASE, reg, I2C_MCS_START | I2C_MCS_RUN);
 
  // send the data
  i2cSendByte( IO_EXPANDER_I2C_BASE, data, I2C_MCS_RUN | I2C_MCS_STOP);
}

uint8_t io_expander_read_reg(uint8_t addr) {
	i2c_status_t status;
  uint8_t data;

  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(IO_EXPANDER_I2C_BASE)) {put_string("w");};

	// Set the I2C slave address to be the EEPROM and in Write Mode
  i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);

  // Send the address
	i2cSendByte(IO_EXPANDER_I2C_BASE, addr, I2C_MCS_START | I2C_MCS_RUN);
  
  // Set the I2C slave address to be the EEPROM and in Read Mode
	i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_READ);

  // Read the data returned by the EEPROM
	i2cGetByte(IO_EXPANDER_I2C_BASE, &data, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
    
  return data;
}