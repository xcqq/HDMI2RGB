#include "i2c.h"
#include "delay.h"

/*i2c driver*/
void I2CInit(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	IIC_SCL=1;
	IIC_SDA=1;

}

static void I2CStart(void)
{
	SDA_OUT();
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;
	delay_us(4);
	IIC_SCL=0;
}	  

static void I2CStop(void)
{
	SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;
	delay_us(4);							   	
}

static uint8_t I2CWaitAck(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			I2CStop();
			return 0;
		}
	}
	IIC_SCL=0;   
	return 1;  
} 

static void I2CAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
	    
static void I2CNack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
	  
static void I2CSend(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL=0;
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    

static uint8_t I2CRead(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        I2CNack();
    else
        I2CAck();
    return receive;
}

int8_t I2CWriteByte(uint8_t i2c_addr,uint16_t data_addr,uint8_t data)
{
	I2CStart();
	I2CSend(i2c_addr);
	if(!I2CWaitAck())
		return -1;
	I2CSend(data_addr);
	if(!I2CWaitAck())
		return -1;
	I2CSend(data);
	if(!I2CWaitAck())
		return -1;
	I2CStop();
	delay_ms(10);
	return 0;
}

int8_t I2CReadByte(uint8_t i2c_addr,uint16_t data_addr,uint8_t *data)
{
	I2CStart();
	I2CSend(i2c_addr);
	if(!I2CWaitAck())
		return -1;
	I2CSend(data_addr);
	if(!I2CWaitAck())
		return -1;
	I2CStart();
	I2CSend(i2c_addr | 0x01);
	if(!I2CWaitAck())
		return -1;
	*data = I2CRead(0);
	I2CStop();
	return 0;
}

int8_t I2CWriteBytes(uint8_t i2c_addr,uint16_t data_addr,uint8_t *data,uint16_t len)
{
	uint8_t i;
	I2CStart();
	I2CSend(i2c_addr);
	if(!I2CWaitAck())
		return -1;
	I2CSend(data_addr);
	if(!I2CWaitAck())
		return -1;
	for (i = 0; i < len;i++)
	{
		I2CSend(*(data+i));
		if(!I2CWaitAck())
			return -1;
	}
	I2CStop();
	delay_ms(10);
	return 0;
}

int8_t I2CReadBytes(uint8_t i2c_addr,uint16_t data_addr,uint8_t *data,uint16_t len)
{
	uint8_t i;
	I2CStart();
	I2CSend(i2c_addr);
	if(!I2CWaitAck())
		return -1;
	I2CSend(data_addr);
	if(!I2CWaitAck())
		return -1;
	I2CStart();
	I2CSend(i2c_addr | 0x01);
	if(!I2CWaitAck())
		return -1;
	for (i = 0; i < len;i++)
	{
		if(i==len-1)
		{
			*(data + i) = I2CRead(0);
		}
		else
		{
			*(data + i) = I2CRead(1);
		}
	}
	I2CStop();
	return 0;
}























