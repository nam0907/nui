#ifndef __NUI_ALIGN_TXT_H__
#define __NUI_ALIGN_TXT_H__

#include <stdint.h>

//#include "../../core/inc/nui_font.h"
#include "../../align/inc/nui_align_def.h"
#include "../../wdg/inc/nui_wdg_def.h"
#include "../../core/inc/nui_draw.h"
#include "../../int/nui_font_int.h"

#if NUI_WDG_USE_TXT_GRAPH

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

Nui_Rect_Typedef NUI_ALIGN_RECT_SYMETRY_X(Nui_Rect_Typedef rect, uint16_t width);
Nui_Rect_Typedef NUI_ALIGN_RECT_SPLIT_X(Nui_Rect_Typedef rectParent, uint8_t numRect, uint8_t index, uint8_t gap);
void NUI_ALIGN_TXT_FORM_START(Nui_Txt_Graph_Typedef *gA, Nui_Txt_Graph_Typedef *gB,uint16_t screenW,int16_t start_x,int16_t y);
void NUI_ALIGN_TXT_CENTER_X(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect);
void NUI_ALIGN_TXT_CENTER_Y(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect);
void NUI_ALIGN_TXT_CENTER(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect);
void NUI_ALIGN_TXT_HORIZONTAL(Nui_Txt_Graph_Typedef *graphic[],uint8_t num, Nui_Rect_Typedef rect);
void NUI_ALIGN_TXT_RIGHT(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect);
void NUI_ALIGN_TXT_LEFT(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect);
void NUI_ALIGN_TXT_BOTTOM(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect);
void NUI_ALIGN_TXT_TOP(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect);

#ifdef __cplusplus // Compatible with C++
}
#endif

#endif

#endif
