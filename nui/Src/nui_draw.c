#include "nui_draw.h"
#include "nui_port.h"

void nui_draw_pixel(void *ctx, int16_t x, int16_t y, uint32_t color)
{
	if(nui_ready!=true || !nui_drv->set_px) return;
  nui_drv->set_px(ctx, x, y, color);
}

void nui_draw_pixel_clip(WidgetClip_Typedef *clip, int16_t x, int16_t y, uint32_t color)
{
	if(nui_ready!=true || !nui_drv->set_px) return;
  if (clip->isClip==true)
  {
    if (x < clip->x0 || x > clip->x1) return;
    if (y < clip->y0 || y > clip->y1) return;
	}
	
  nui_drv->set_px(clip->ctx, x, y, color);
}
