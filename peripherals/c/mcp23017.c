
#include "io_expander.h"
#include "eeprom.h"
#include "validate.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>


 //==============================
  // Configure I2C GPIO Pins
  //==============================  
	
bool mcp23017_init(void) {
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
	
	//config pullups on the peripherals button pins
  
  return true;
  
}

void config_pull_up(uint32_t  i2c_base)
{
	i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);
 
  // Send the pullup reg Address
  i2cSendByte( IO_EXPANDER_I2C_BASE, MCP23017_IODIRB_R, I2C_MCS_START | I2C_MCS_RUN);
 
  // Send the data
  i2cSendByte(IO_EXPANDER_I2C_BASE, 0x03, I2C_MCS_RUN | I2C_MCS_STOP);
}

void config_input(uint32_t  i2c_base)
{
	i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);
 
  // Send the pullup reg Address
  i2cSendByte( IO_EXPANDER_I2C_BASE, MCP23017_GPPUB_R, I2C_MCS_START | I2C_MCS_RUN);
 
  // Send the data
  i2cSendByte(IO_EXPANDER_I2C_BASE, 0x03, I2C_MCS_RUN | I2C_MCS_STOP);
}

uint8_t mcp23017_read_status(uint32_t i2c_base, uint8_t address, uint8_t *data) {
	i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(i2c_base)) {};

	// Set the I2C slave address to be the EEPROM and in Write Mode
  status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_WRITE);

  // Send the address
	i2cSendByte(i2c_base, address, I2C_MCS_START);
  
  // Set the I2C slave address to be the EEPROM and in Read Mode
	status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_READ);
  
  // Read the data returned by the EEPROM
	i2cGetByte(i2c_base, data, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
	
	if (!(*data & 0x1))
		put_string("up\n\r");
	if (!(*data & 0x2))
		put_string("down\n\r");
    
  return I2C_OK;
}





  