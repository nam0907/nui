#ifndef __NUI_PORT_H__
#define __NUI_PORT_H__

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif


#include "stdint.h"
#include "stdbool.h"

typedef struct
{
	void (*set_px)(void *,int16_t, int16_t, uint32_t);
	void (*clear)(void *, uint32_t);
	void (*clear_window)(void *,int16_t, int16_t, int16_t, int16_t,  uint32_t);
	void (*update)(void *);
	void (*blit_mono)(void*, int16_t, int16_t,int16_t, int16_t,const uint8_t*,uint16_t,uint32_t, uint32_t );
	void (*blit_color)(void*, int16_t, int16_t,int16_t, int16_t,const uint8_t*);
//	void (*blit_fill)(void*, int16_t, int16_t,int16_t, int16_t, uint32_t);
}nui_driver_Typedef;

extern nui_driver_Typedef *nui_drv;
extern bool nui_ready;

void NUI_REGISTER_Driver(nui_driver_Typedef * drv);

#ifdef __cplusplus // Compatible with C++
}
#endif


#endif
