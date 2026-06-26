#ifndef __NUI_SD_H__
#define __NUI_SD_H__

#include "stdint.h"
#include "string.h"
#include "nui_conf.h"

#if NUI_USE_SD
#include "fatfs.h"
#include "../core/inc/nui_stream.h"
#include "../core/inc/nui_font.h"
#include "../core/inc/nui_font_bin.h"

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

//#define NUI_PATH_MAX_SIZE					50
//#define NUI_FONT_BIN_TYPE					0
//#define NUI_IMAGE_BIN_TYPE				1

typedef struct 
{
	FATFS fs;
	FIL file;
	Nui_Stream_Typedef stream;
}Nui_SD_Typedef;


//bool NUI_SD_INIT(Nui_SD_Typedef *sd, const uint8_t *pathFile);

#ifdef __cplusplus // Compatible with C++
}
#endif

#endif

#endif
