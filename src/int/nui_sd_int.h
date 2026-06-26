#ifndef __NUI_SD_INT_H__
#define __NUI_SD_INT_H__

#include "nui_conf.h"

#if NUI_USE_SD
#include "../sd/nui_sd.h"

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

#define NUI_PATH_MAX_SIZE					50
#define NUI_FONT_BIN_TYPE					0
#define NUI_IMAGE_BIN_TYPE				1


bool NUI_SD_INIT(Nui_SD_Typedef *sd, const uint8_t *pathFile);

#ifdef __cplusplus // Compatible with C++
}
#endif

#endif

#endif
