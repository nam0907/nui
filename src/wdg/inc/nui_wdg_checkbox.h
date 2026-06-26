#ifndef __WIDGET_CHECKBOX_H__
#define __WIDGET_CHECKBOX_H__

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "../../core/inc/nui_geometry.h"
#include "../../align/inc/nui_align.h"

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

typedef struct
{
	uint32_t txtColor;
	Nui_Wdg_Txt_Typedef txt;
}Nui_Wdg_TxtBox_Typedef;

//void NUI_WDG_TEXTBOX_DRAW(void *ctx,const Nui_Wdg_Typedef *widget);
//void NUI_WDG_CHECKBOX_SET_TEXT(Nui_Wdg_Typedef *widget,const uint8_t *FMT, va_list arg);
void NUI_WDG_CHECKBOX_SET_COLOR(Nui_Wdg_Typedef *widget,uint32_t color);
Nui_Wdg_Typedef NUI_WDG_CHECKBOX_CREATE(Nui_Wdg_TxtBox_Typedef *checkboxData,uint16_t id, int16_t x, int16_t y, int16_t w, int16_t h,uint32_t color, uint32_t backColor);
//Nui_Wdg_Typedef NUI_WDG_CHECKBOX_CREATE(Nui_Wdg_TxtBox_Typedef *checkboxData,uint16_t id, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t *str,uint16_t txtMaxLen,const Nui_Font_Typedef *font,uint32_t color, uint32_t backColor);

#ifdef __cplusplus
}
#endif

#endif
