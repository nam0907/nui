#ifndef __NUI_IMAGE_BIN_H__
#define __NUI_IMAGE_BIN_H__

#include "nui_conf.h"

#if NUI_IMAGE_USE_STREAM

#include <stdint.h>
#include <stddef.h>

#include "nui_image.h"
#include "nui_stream.h"


#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

//#define NUI_IMAGE_BIN_DATA_OFFSET_POS							15

typedef struct
{
	Nui_Stream_Typedef *stream;
	uint16_t version;
	uint32_t fileSize;
}Nui_Image_Bin_Typedef;

//bool NUI_IMAGE_BIN_GET_LINE(const Nui_Image_Typedef *img, uint16_t lineSize ,uint16_t line, uint16_t numLine, uint8_t * buff);

#ifdef __cplusplus // Compatible with C++
}
#endif

#endif

#endif
