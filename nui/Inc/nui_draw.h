#ifndef __NUI_DRAW_H__
#define __NUI_DRAW_H__

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif


#include "stdint.h"
#include "stdbool.h"

typedef struct 
{
	void *ctx;
	int16_t x0, y0, x1, y1;
	bool isClip;
}WidgetClip_Typedef;

void nui_draw_pixel(void *ctx, int16_t x, int16_t y, uint32_t color);
void nui_draw_pixel_clip(WidgetClip_Typedef *clip, int16_t x, int16_t y, uint32_t color);

#ifdef __cplusplus // Compatible with C++
}
#endif


#endif
