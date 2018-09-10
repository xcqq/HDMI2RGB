#ifndef __IO_H
#define __IO_H	 

typedef enum 
{  
	io_num_hdmi_rst,
	io_num_hdmi_int,
	io_num_dlp_en,
	io_num_end,
} e_io_num_t;

typedef struct  
{
	e_io_num_t io_num;
	GPIO_TypeDef *io_port;
	uint16_t io_pin;
	GPIOMode_TypeDef io_mode;
}e_io_pin_mode_t;	

void IOInit(void);
void IOSet(e_io_num_t io_num,uint8_t state);
uint8_t IOGet(e_io_num_t io_num);
#endif
