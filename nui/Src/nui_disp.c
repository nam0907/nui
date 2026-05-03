#include "nui_disp.h"
#include "nui_port.h"

void NUI_DISP_CLEAR(void *ctx, uint32_t bg)
{
	if(nui_ready!=true || !nui_drv->clear) return;
	nui_drv->clear(ctx, bg);
}

void NUI_DISP_CLEAR_WINDOW(void *ctx, int16_t x, int16_t y, int16_t w, int16_t h, uint32_t bg)
{
	if(nui_ready!=true || !nui_drv->clear_window) return;
	nui_drv->clear_window(ctx,x,y,w,h,bg);
}

void NUI_DISP_UPDATE(void *ctx)
{
	if(nui_ready!=true || !nui_drv->update) return;
	nui_drv->update(ctx);
}

