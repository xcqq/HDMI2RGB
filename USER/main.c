#include "led.h"
#include "delay.h"
#include "sys.h"
#include "dlp.h"
#include "key.h"
#include "adv7611.h"
int main(void)
{
	uint8_t power_state = 0;
	uint8_t dlp_mode = 0;
	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	delay_init(72);	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LEDInit();
	DLPInit();
	KeyInit();
	IOInit();
	I2CInit();
	
	while(1)
	{
		switch(KeyScan())
		{
			case key_num_poweron:
				if(power_state==0)
				{
					LEDSet(led_num_state, 1);
					DLPStart();
					power_state = 1;
                    if(ADV7611Init()==-1)
                    {
                        LEDSet(led_num_error, 1);
                    }
                    ADV7611Start();
				}
				else
				{
					LEDSet(led_num_state, 0);
					DLPStop();
					power_state = 0;
				}
				break;
			case key_num_dlp_mode:
				dlp_mode++;
				if (dlp_mode == 3)
					dlp_mode = 0;
				switch (dlp_mode)
				{
				case 0:
					DLPModeSet(dlp_mode_powersave);
					break;
				case 1:
					DLPModeSet(dlp_mode_normal);
					break;
				case 2:
					DLPModeSet(dlp_mode_brighten);
					break;
				}

				break;
		}
		if(ADV7611Check()==-1)
			 LEDSet(led_num_error, 1);
		else
			LEDSet(led_num_error, 0);
	}
}

