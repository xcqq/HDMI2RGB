#ifndef __DLP_H
#define __DLP_H	 
#include "stm32f10x.h"

typedef enum
{
    dlp_mode_normal,
    dlp_mode_brighten,
    dlp_mode_powersave,
    //need to use video process to enhance color
    dlp_mode_colorful,
}e_dlp_mode_t;

int DLPInit();
void DLPStart();
void DLPStop();
int DLPModeSet(e_dlp_mode_t mode);

#endif
