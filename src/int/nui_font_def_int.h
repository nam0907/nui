#ifndef __NUI_FONT_DEF_INT_H__
#define __NUI_FONT_DEF_INT_H__

#include "../core/inc/nui_draw.h"
//#include "../wdg/inc/nui_wdg_conf.h"
#include "../core/inc/nui_font.h"
#include "nui_font_int.h"

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

#define ACSCII_END			128

uint32_t NUI_FONT_UTF8_DECODE(const uint8_t *txt, uint8_t *offset);
uint16_t NUI_FONT_GET_HEIGHT(const uint8_t *str,const Nui_Font_Typedef *font,int16_t *min_top, int16_t *max_bottom);
uint16_t NUI_FONT_GET_WIDTH(const uint8_t *str,const Nui_Font_Typedef *font);


#if NUI_WDG_USE_TXT_GRAPH
	void NUI_FONT_DRAW_TXT_GRAPH(void *ctx,const Nui_Rect_Typedef *clip ,const Nui_Txt_Graph_Typedef *txtGraph);
#endif


#ifdef __cplusplus // Compatible with C++
}
#endif

#endif
