#ifndef __NUI_FONT_H__
#define __NUI_FONT_H__

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

#include "stdint.h"
#include "nui_draw.h"

#define UTF8_END1				31
#define UTF8_START2			128

#define UTF8_GAP				1


typedef struct
{
   const uint8_t *Font;
   const uint16_t *Font_Map;
   const uint32_t *Font_Ref;
   uint8_t offset;
   uint16_t numChar;
} Font_Typedef;

typedef struct
{
	uint32_t Color;
	uint16_t PosX;
	uint16_t PosY;
	const uint8_t *Text;
}StringGraphic_Typedef;

uint32_t NUI_FONT_GET_ADDR(const uint8_t *txt, uint8_t *offset,Font_Typedef font);
uint16_t NUI_FONT_GET_HEIGHT(const uint8_t *str,Font_Typedef font,int16_t *min_top, int16_t *max_bottom);
uint16_t NUI_FONT_GET_WIDTH(const uint8_t *str,Font_Typedef font);
void NUI_FONT_DRAW_STRING(void *ctx, int16_t x, int16_t y, const uint8_t *str, Font_Typedef font,uint32_t color, uint32_t bg);
void NUI_FONT_DRAW_STRING_CLIP(WidgetClip_Typedef *clip, int16_t x, int16_t y, const uint8_t *str, Font_Typedef font,uint32_t color, uint32_t bg);

#ifdef __cplusplus // Compatible with C++
}
#endif

#endif
