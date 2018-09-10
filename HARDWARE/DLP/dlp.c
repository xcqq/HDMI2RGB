#include "stm32f10x.h"
#include "dlp.h"
#include "uart.h"
#include "io.h"

//dlp driver here

#define MODE_POWER_SAVE 0x15
#define MODE_NORMAL 0x13
#define MODE_BRIGHTEN 0x11
int DLPInit()
{
    UARTInit(USART1, 19200);
    return 0;
}
void DLPStart()
{
    IOSet(io_num_dlp_en, 1);
}
void DLPStop()
{
    IOSet(io_num_dlp_en, 0);
}
int DLPModeSet(e_dlp_mode_t mode)
{
    uint8_t cmd = 0;
    switch(mode)
    {
        case dlp_mode_normal:
            cmd = 0x13;
            UARTSend(USART1, &cmd, 1);
            break;
        case dlp_mode_brighten:
            cmd = 0x11;
            UARTSend(USART1, &cmd, 1);
            break;
        case dlp_mode_powersave:
            cmd = 0x15;
            UARTSend(USART1, &cmd, 1);
            break;
    }
    return 0;
}