#ifndef __NUI_GEOMETRY_H__
#define __NUI_GEOMETRY_H__

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif


#include "stdint.h"
#include "nui_draw.h"

void GRAPHIC_CLEAR_WINDOW(void *ctx,int16_t x, int16_t y, int16_t w, int16_t h);
void NUI_GEOMETRY_DRAW_LINE(void *ctx,int16_t x,int16_t y, uint16_t length,uint32_t color);
void NUI_GEOMETRY_DRAW_FILL_RECTANGLE(void *ctx,int16_t x,int16_t y, uint16_t width, uint16_t height,uint32_t color);
void NUI_GEOMETRY_DRAW_RECTANGLE(void *ctx,int16_t x,int16_t y, uint16_t width, uint16_t height,uint32_t color);
void NUI_GEOMETRY_DRAW_CIRCLE(void *ctx,int16_t x, int16_t y,uint16_t r,uint32_t color);
void NUI_GEOMETRY_DRAW_FILL_CIRCLE(void *ctx,int16_t x, int16_t y,uint16_t r,uint32_t color);
void GRAPHIC_CLEAR_WINDOW(void *ctx,int16_t x, int16_t y, int16_t w, int16_t h);

void NUI_GEOMETRY_DRAW_LINE_CLIP(WidgetClip_Typedef *clip,int16_t x,int16_t y, uint16_t length,uint32_t color);
void NUI_GEOMETRY_DRAW_FILL_RECTANGLE_CLIP(WidgetClip_Typedef *clip,int16_t x,int16_t y, uint16_t width, uint16_t height,uint32_t color);
void NUI_GEOMETRY_DRAW_RECTANGLE_CLIP(WidgetClip_Typedef *clip,int16_t x,int16_t y, uint16_t width, uint16_t height,uint32_t color);
void NUI_GEOMETRY_DRAW_CIRCLE_CLIP(WidgetClip_Typedef *clip,int16_t x, int16_t y,uint16_t r,uint32_t color);
void NUI_GEOMETRY_DRAW_FILL_CIRCLE_CLIP(WidgetClip_Typedef *clip,int16_t x, int16_t y,uint16_t r,uint32_t color);

#ifdef __cplusplus // Compatible with C++
}
#endif


#endif
