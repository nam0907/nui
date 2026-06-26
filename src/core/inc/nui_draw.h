#ifndef __NUI_DRAW_H__
#define __NUI_DRAW_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

typedef struct
{
  int16_t x;
  int16_t y;
  int16_t w;
  int16_t h;
} Nui_Rect_Typedef;

//typedef struct
//{
//  int16_t dst_x;
//  int16_t dst_y;

//  int16_t src_x;
//  int16_t src_y;

//  int16_t w;
//  int16_t h;
//} Nui_Draw_Rect_Typedef;

//void nui_draw_pixel(void *ctx, int16_t x, int16_t y, uint32_t color);
//bool nui_clip_rect(const Nui_Rect_Typedef *clip, Nui_Draw_Rect_Typedef *draw);

#ifdef __cplusplus // Compatible with C++
}
#endif


#endif
