#ifndef __NUI_FONT_BIN_INT_H__
#define __NUI_FONT_BIN_INT_H__

#include "nui_conf.h"

#if NUI_FONT_USE_STREAM
#include "../core/inc/nui_font_bin.h"

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

#define NUI_GLYPH_BUFF_MAX_SIZE									256

#define NUI_FONT_BIN_REF_OFFSET_POS							13
#define NUI_FONT_BIN_MAP_OFFSET_POS							17
#define NUI_FONT_BIN_DATA_OFFSET_POS						21

#define NUI_FONT_BIN_REF_OFFSET_SIZE						4
#define NUI_FONT_BIN_MAP_OFFSET_SIZE						4
#define NUI_FONT_BIN_DATA_OFFSET_SIZE						4

//typedef struct
//{
//	Nui_Stream_Typedef *stream;
//	uint16_t version;
//	uint32_t fileSize;
//  uint16_t numChar;
//	uint32_t mapOffset;
//	uint32_t refOffset;
//	uint32_t dataOffset;
////	uint8_t gap;
//}Nui_Font_Bin_Typedef;


bool NUI_FONT_BIN_GET_GLYPH(const Nui_Font_Typedef *font,uint32_t unicode ,Nui_Glyph_Typedef *glyph);

#ifdef __cplusplus // Compatible with C++
}
#endif

#endif

#endif
