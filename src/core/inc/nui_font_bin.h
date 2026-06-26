#ifndef __NUI_FONT_BIN_H__
#define __NUI_FONT_BIN_H__

#include "nui_conf.h"

#if NUI_FONT_USE_STREAM

#include <stdint.h>
#include <stddef.h>

#include "nui_font.h"
#include "nui_stream.h"

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

typedef struct
{
	Nui_Stream_Typedef *stream;
	uint16_t version;
	uint32_t fileSize;
  uint16_t numChar;
	uint32_t mapOffset;
	uint32_t refOffset;
	uint32_t dataOffset;
//	uint8_t gap;
}Nui_Font_Bin_Typedef;


#ifdef __cplusplus // Compatible with C++
}
#endif

#endif

#endif
