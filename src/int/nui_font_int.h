#ifndef __NUI_FONT_INT_H__
#define __NUI_FONT_INT_H__

#include "../core/inc/nui_draw.h"
#include "../core/inc/nui_font.h"


#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

#if NUI_WDG_USE_TXT_GRAPH
	typedef struct
	{
		uint32_t color;
		uint32_t backColor;
		int16_t x;
		int16_t y;
		const uint8_t *txt;
		const Nui_Font_Typedef *font;
	}Nui_Txt_Graph_Typedef; 
#endif

//#if NUI_WDG_USE_TXT_GRAPH
//	void NUI_FONT_DRAW_TXT_GRAPH(void *ctx,const Nui_Rect_Typedef *clip ,const Nui_Txt_Graph_Typedef *txtGraph);
//#endif

#ifdef __cplusplus // Compatible with C++
}
#endif

#endif
