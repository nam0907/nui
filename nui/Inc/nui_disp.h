#ifndef __NUI_DISP_H__
#define __NUI_DISP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

void NUI_DISP_CLEAR(void *ctx, uint32_t bg);
void NUI_DISP_CLEAR_WINDOW(void *ctx, int16_t x, int16_t y, int16_t w, int16_t h, uint32_t bg);
void NUI_DISP_UPDATE(void *ctx);

#ifdef __cplusplus
}
#endif

#endif
