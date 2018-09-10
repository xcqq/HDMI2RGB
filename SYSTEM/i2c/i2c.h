#ifndef __I2C_H
#define __I2C_H
#include "sys.h"


#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}


#define IIC_SCL    PBout(10)
#define IIC_SDA    PBout(11)
#define READ_SDA   PBin(11)

void I2CInit(void);
int8_t I2CWriteByte(uint8_t i2c_addr, uint16_t data_addr, uint8_t data);
int8_t I2CReadByte(uint8_t i2c_addr, uint16_t data_addr, uint8_t *data);
int8_t I2CWriteBytes(uint8_t i2c_addr, uint16_t data_addr, uint8_t *data, uint16_t len);
int8_t I2CReadBytes(uint8_t i2c_addr, uint16_t data_addr, uint8_t *data, uint16_t len);

#endif
















