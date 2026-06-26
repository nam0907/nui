#include "../inc/nui_draw.h"
#include "../../int/nui_draw_int.h"
#include "../inc/nui_port.h"

void nui_draw_pixel(void *ctx, int16_t x, int16_t y, uint32_t color)
{
	if(nui_ready!=true || !nui_drv->set_px) return;
  nui_drv->set_px(ctx, x, y, color);
}



bool nui_clip_rect(const Nui_Rect_Typedef *clip, Nui_Draw_Rect_Typedef *draw)
{
	
	int16_t clip_right  = clip->x + clip->w - 1;
  int16_t clip_bottom = clip->y + clip->h - 1;
	
	// Clip left
	if(draw->dst_x < clip->x)
  {
    int16_t cut =clip->x - draw->dst_x;

    draw->src_x += cut;
    draw->w -= cut;
    draw->dst_x = clip->x;
  }

  // Clip top
  if(draw->dst_y < clip->y)
  {
    int16_t cut = clip->y - draw->dst_y;

    draw->src_y += cut;
    draw->h -= cut;
    draw->dst_y = clip->y;
  }

//  // Clip right
//  if((draw->dst_x + draw->w) > (clip->x + clip->w))
//  {
//    draw->w = (clip->x + clip->w)- draw->dst_x;
//  }

//  // Clip bottom
//  if((draw->dst_y + draw->h) > (clip->y + clip->h))
//	{
//    draw->h =(clip->y + clip->h) - draw->dst_y;
//  }
	
	// Clip right
  if((draw->dst_x + draw->w-1) > clip_right)
  {
    draw->w = (clip->x + clip->w)- draw->dst_x+1;
  }

  // Clip bottom
  if((draw->dst_y + draw->h-1) > clip_bottom)
	{
    draw->h =(clip->y + clip->h) - draw->dst_y+1;
  }

  // Invalid
  if(draw->w <= 0 || draw->h <= 0)
  {
    return false;
  }

  return true;
}

