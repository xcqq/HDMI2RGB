#include "stm32f10x.h"
#include "adv7611.h"
#include "i2c.h"
#include "io.h"
#include "delay.h"
//adv7611 driver here
#define ADV7611_ADDR 0x98
#define ADV7611_HDMI 0x68
int8_t ADV7611Init()
{
    uint16_t reg;
    IOSet(io_num_hdmi_rst, 0);
    delay_ms(100);
    IOSet(io_num_hdmi_rst, 1);

    if (I2CReadBytes(ADV7611_ADDR, 0xEA, (uint8_t *)&reg, 2) < 0)
        goto err;
    if (reg != 0x5120)
        goto err;
    I2CWriteByte(ADV7611_ADDR, 0xFF, 0x80);
    delay_ms(100);
    return 0;
err:
    return -1;
}

int8_t ADV7611Start()
{
    int8_t ret;

	I2CWriteByte(ADV7611_ADDR, 0xFF, 0x80); // I2C reset
    delay_ms(100);
	I2CWriteByte(ADV7611_ADDR, 0xF4, 0x80); // CEC
	I2CWriteByte(ADV7611_ADDR, 0xF5, 0x7C); // INFOFRAME
	I2CWriteByte(ADV7611_ADDR, 0xF8, 0x4C); // DPLL
	I2CWriteByte(ADV7611_ADDR, 0xF9, 0x64); // KSV
	I2CWriteByte(ADV7611_ADDR, 0xFA, 0x6C); // EDID
	I2CWriteByte(ADV7611_ADDR, 0xFB, ADV7611_HDMI); // HDMI
	I2CWriteByte(ADV7611_ADDR, 0xFD, 0x44); // CP

    I2CWriteByte(ADV7611_ADDR, 0x00, 0x31); // Prim_Mode =110b HDMI-GR  
	I2CWriteByte(ADV7611_ADDR, 0x01, 0x15); // Prim_Mode =110b HDMI-GR
	I2CWriteByte(ADV7611_ADDR, 0x02, 0xF2); // Auto CSC, YCrCb out, Set op_656 bit

	I2CWriteByte(ADV7611_ADDR, 0x03, 0x40); // 8-bit 4:2:2 DDR mode 2 (ITU-656 mode)????
	//I2CWriteByte(ADV7611_ADDR, 0x05, 0x28); // AV Codes Off
	I2CWriteByte(ADV7611_ADDR, 0x05, 0x2E); // AV Codes Off
	I2CWriteByte(ADV7611_ADDR, 0x06, 0xA6); // Invert VS,HS pins
	I2CWriteByte(ADV7611_ADDR, 0x0B, 0x44); // Power up part
	I2CWriteByte(ADV7611_ADDR, 0x0C, 0x42); // Power up part
	I2CWriteByte(ADV7611_ADDR, 0x14, 0x7F); // Max Drive Strength
	I2CWriteByte(ADV7611_ADDR, 0x15, 0x80); // Disable Tristate of Pins
	I2CWriteByte(ADV7611_ADDR, 0x19, 0x83); // LLC DLL phase
	I2CWriteByte(ADV7611_ADDR, 0x33, 0x40); // LLC DLL enable

	I2CWriteByte(ADV7611_ADDR, 0x20, 0xF8); // Manually assert hot plug on port A
	//I2CWriteByte(0x80, 0x2A, 0x3F); // power down

	I2CWriteByte(0x44, 0xBA, 0x01); // Set HDMI FreeRun
	//I2CWriteByte(0x64, 0x40, 0x81); // Disable HDCP 1.1 features

	I2CWriteByte(0x68, 0x9B, 0x03); // ADI recommended setting
	I2CWriteByte(0x68, 0xC1, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xC2, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xC3, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xC4, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xC5, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xC6, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xC7, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xC8, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xC9, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xCA, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xCB, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0xCC, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0x00, 0x00); // Set HDMI Input Port A
	I2CWriteByte(0x68, 0x83, 0xFE); // Enable clock terminator for port A
	I2CWriteByte(0x68, 0x6F, 0x0C); // ADI recommended setting
	I2CWriteByte(0x68, 0x85, 0x1F); // ADI recommended setting
	I2CWriteByte(0x68, 0x87, 0x70); // ADI recommended setting
	I2CWriteByte(0x68, 0x8D, 0x04); // LFG
	I2CWriteByte(0x68, 0x8E, 0x1E); // HFG
	//I2CWriteByte(0x68, 0x1A, 0x8A); // unmute audio
	I2CWriteByte(0x68, 0x57, 0xDA); // ADI recommended setting
	I2CWriteByte(0x68, 0x58, 0x01); // ADI recommended setting
	I2CWriteByte(0x68, 0x03, 0x98); // DIS_I2C_ZERO_COMPR
	I2CWriteByte(0x68, 0x75, 0x10); // DDC drive strength



	return 0;
err:
    return -1;
}

int8_t ADV7611Check()
{
	uint8_t reg, temp;
	uint16_t width = 0;
	I2CReadByte(ADV7611_ADDR, 0x6A, (uint8_t *)&reg);
	if(!(reg&0x10))
		return -1;
	I2CReadByte(ADV7611_ADDR, 0x6F, (uint8_t *)&reg);
	if(!(reg&0x01))
		return -1;
	I2CReadByte(ADV7611_HDMI, 0x08, (uint8_t *)&temp);
	width |= temp;
	I2CReadByte(ADV7611_HDMI, 0x07, (uint8_t *)&temp);
	width |= (temp & 0x1F) << 8;
	return 0;
}