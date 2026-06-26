#ifndef __NUI_WDG_DEF_H__
#define __NUI_WDG_DEF_H__

#include "stdint.h"
#include "stdbool.h"
#include "../../align/inc/nui_align_def.h"
#include "../../core/inc/nui_font.h"

typedef struct
{
	const Nui_Font_Typedef *font;
  uint8_t *txt;
  uint16_t txt_maxl;
	Nui_Align_Typedef xAlign;
	Nui_Align_Typedef yAlign;
}Nui_Wdg_Txt_Typedef;

typedef enum
{
	NUI_WDG_NULL,
	NUI_WDG_BUTTON,
	NUI_WDG_LABEL,
	NUI_WDG_TEXTBOX,
	NUI_WDG_PROGRESS,
	NUI_WDG_PICTUREBOX,
	NUI_WDG_CHECKBOX,
	NUI_WDG_SLIDER,
}Nui_Wdg_Type_Typedef;

typedef enum
{
	NUI_EV_PRESS,
	NUI_EV_RELEASE,
	NUI_EV_SLIDE,
}Nui_Ev_Type_Typedef;

typedef struct
{
	Nui_Ev_Type_Typedef type;
}Nui_Ev_Typedef;

typedef struct Nui_Wdg_Typedef
{
	uint16_t id;
	Nui_Wdg_Type_Typedef type;
	int16_t x,y,w,h;
	bool visible;
	uint32_t backColor;
	void *data;
	void(*draw)(void *ctx, const struct Nui_Wdg_Typedef *wdg);
	void(*event)(void *ctx, const struct Nui_Wdg_Typedef *wdg);
}Nui_Wdg_Typedef;

void WIDGET_DRAW_CLIP(void *ctx,int16_t x,int16_t y,uint32_t color);

#endif
