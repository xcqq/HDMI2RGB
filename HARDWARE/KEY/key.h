#ifndef __KEY_H
#define __KEY_H	 

typedef enum 
{  
	key_num_poweron,
	key_num_dlp_mode,
	key_num_end,
} e_key_num_t;

typedef struct  
{
	e_key_num_t key_num;
	GPIO_TypeDef *key_port;
	uint16_t key_pin;
	uint8_t key_state;
}e_key_pin_mode_t;	

	 
void KEY_Init(void);
e_key_num_t KeyScan(void);
#endif
