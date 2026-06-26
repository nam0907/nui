#ifndef __NUI_IMAGE_BIN_INT_H__
#define __NUI_IMAGE_BIN_INT_H__

#include "nui_conf.h"

#if NUI_IMAGE_USE_STREAM

#include "../core/inc/nui_image_bin.h"

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

#define NUI_IMAGE_BIN_DATA_OFFSET_POS							15


bool NUI_IMAGE_BIN_GET_LINE(const Nui_Image_Typedef *img, uint16_t lineSize ,uint16_t line, uint16_t numLine, uint8_t * buff);

#ifdef __cplusplus // Compatible with C++
}
#endif

#endif

#endif
