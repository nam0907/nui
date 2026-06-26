#include "../inc/nui_geometry.h"
#include "../inc/nui_port.h"
#include "../inc/nui_draw.h"
#include "../../int/nui_draw_int.h"

void NUI_GEOMETRY_DRAW_LINE(void *ctx,int16_t x,int16_t y, uint16_t length,uint32_t color)
{
	for(uint16_t x1=x; x1<x+length;x1++)
	{
		nui_draw_pixel(ctx,x,y,color);
	}
}

void NUI_GEOMETRY_DRAW_FILL_RECTANGLE(void *ctx,int16_t x,int16_t y, uint16_t width, uint16_t height,uint32_t color)
{
	if (nui_drv && nui_drv->clear_window)
  {
     nui_drv->clear_window(ctx,x,y,width,height,color);
  }
	else
	{
		for(uint16_t y1=y; y1<y+height;y1++)
		{
			for(uint16_t x1=x; x1<x+width;x1++)
			{
				nui_draw_pixel(ctx,x1,y1,color);
			}
		}
	}
}

void NUI_GEOMETRY_DRAW_RECTANGLE(void *ctx,int16_t x,int16_t y, uint16_t width, uint16_t height,uint32_t color)
{
	for(uint16_t y1=y; y1<y+height;y1++)
	{
		if(y1==y || y1==(y+height-1))
		{
			for(uint16_t x1=x; x1<x+width;x1++)
			{
				nui_draw_pixel(ctx,x1,y1,color);
			}
		}
		else
		{
			nui_draw_pixel(ctx,x,y1,color);
			nui_draw_pixel(ctx,x+width-1,y1,color);
		}
	}
}

void NUI_GEOMETRY_DRAW_CIRCLE(void *ctx,int16_t x, int16_t y,uint16_t r,uint32_t color)
{
	// Use Midpoint / Bresenham Circle Algorithm to draw circle
  int16_t x1 = 0;
  int16_t y1 = r;
  int16_t d = 3 - (2 * r);

  while (x1 <= y1)
  {
    nui_draw_pixel(ctx, x + x1, y + y1, color);
    nui_draw_pixel(ctx, x - x1, y + y1, color);
    nui_draw_pixel(ctx, x + x1, y - y1, color);
    nui_draw_pixel(ctx, x - x1, y - y1, color);

    nui_draw_pixel(ctx, x + y1, y + x1, color);
		nui_draw_pixel(ctx, x - y1, y + x1, color);
		nui_draw_pixel(ctx, x + y1, y - x1, color);
		nui_draw_pixel(ctx, x - y1, y - x1, color);

    if (d < 0)
		{
        d += (4 * x1) + 6;
		}
    else
    {
        d += 4 * (x1 - y1) + 10;
        y1--;
    }
    x1++;
  }
}

void NUI_GEOMETRY_DRAW_FILL_CIRCLE(void *ctx,int16_t x, int16_t y,uint16_t r,uint32_t color)
{
	// Use Midpoint / Bresenham Circle Algorithm to draw circle
  int16_t x1 = 0;
  int16_t y1 = r;
  int16_t d  = 3 - 2 * r;

  while (x1 <= y1)
  {
    // Vẽ các đoạn ngang (scanline)
    for (int16_t xi = x - x1; xi <= x + x1; xi++)
    {
        nui_draw_pixel(ctx, xi, y + y1, color);
        nui_draw_pixel(ctx, xi, y - y1, color);
    }

    for (int16_t xi = x - y1; xi <= x + y1; xi++)
    {
        nui_draw_pixel(ctx, xi, y + x1, color);
        nui_draw_pixel(ctx, xi, y - x1, color);
    }

    if (d < 0)
    {
        d += 4 * x1 + 6;
    }
    else
    {
        d += 4 * (x1 - y1) + 10;
        y1--;
    }
    x1++;
  }
}

//void NUI_GEOMETRY_DRAW_LINE_CLIP(WidgetClip_Typedef *clip,int16_t x,int16_t y, uint16_t length,uint32_t color)
//{
//	for(uint16_t x1=x; x1<x+length;x1++)
//	{
//		nui_draw_pixel_clip(clip,x,y,color);
//	}
//}

//void NUI_GEOMETRY_DRAW_FILL_RECTANGLE_CLIP(WidgetClip_Typedef *clip,int16_t x,int16_t y, uint16_t width, uint16_t height,uint32_t color)
//{
//	for(uint16_t y1=y; y1<y+height;y1++)
//	{
//		for(uint16_t x1=x; x1<x+width;x1++)
//		{
//			nui_draw_pixel_clip(clip,x1,y1,color);
//		}
//	}
//}

//void NUI_GEOMETRY_DRAW_RECTANGLE_CLIP(WidgetClip_Typedef *clip,int16_t x,int16_t y, uint16_t width, uint16_t height,uint32_t color)
//{
//	for(uint16_t y1=y; y1<y+height;y1++)
//	{
//		if(y1==y || y1==(y+height-1))
//		{
//			for(uint16_t x1=x; x1<x+width;x1++)
//			{
//				nui_draw_pixel_clip(clip,x1,y1,color);
//			}
//		}
//		else
//		{
//			nui_draw_pixel_clip(clip,x,y1,color);
//			nui_draw_pixel_clip(clip,x+width-1,y1,color);
//		}
//	}
//}

//void NUI_GEOMETRY_DRAW_CIRCLE_CLIP(WidgetClip_Typedef *clip,int16_t x, int16_t y,uint16_t r,uint32_t color)
//{
//	
//	// Use Midpoint / Bresenham Circle Algorithm to draw circle
//  int16_t x1 = 0;
//  int16_t y1 = r;
//  int16_t d = 3 - (2 * r);

//  while (x1 <= y1)
//  {
//    nui_draw_pixel_clip(clip, x + x1, y + y1, color);
//    nui_draw_pixel_clip(clip, x - x1, y + y1, color);
//    nui_draw_pixel_clip(clip, x + x1, y - y1, color);
//    nui_draw_pixel_clip(clip, x - x1, y - y1, color);

//    nui_draw_pixel_clip(clip, x + y1, y + x1, color);
//		nui_draw_pixel_clip(clip, x - y1, y + x1, color);
//		nui_draw_pixel_clip(clip, x + y1, y - x1, color);
//		nui_draw_pixel_clip(clip, x - y1, y - x1, color);

//    if (d < 0)
//		{
//        d += (4 * x1) + 6;
//		}
//    else
//    {
//        d += 4 * (x1 - y1) + 10;
//        y1--;
//    }
//    x1++;
//  }
//}

//void NUI_GEOMETRY_DRAW_FILL_CIRCLE_CLIP(WidgetClip_Typedef *clip,int16_t x, int16_t y,uint16_t r,uint32_t color)
//{
//	// Use Midpoint / Bresenham Circle Algorithm to draw circle
//  int16_t x1 = 0;
//  int16_t y1 = r;
//  int16_t d  = 3 - 2 * r;

//  while (x1 <= y1)
//  {
//    // Vẽ các đoạn ngang (scanline)
//    for (int16_t xi = x - x1; xi <= x + x1; xi++)
//    {
//        nui_draw_pixel_clip(clip, xi, y + y1, color);
//        nui_draw_pixel_clip(clip, xi, y - y1, color);
//    }

//    for (int16_t xi = x - y1; xi <= x + y1; xi++)
//    {
//        nui_draw_pixel_clip(clip, xi, y + x1, color);
//        nui_draw_pixel_clip(clip, xi, y - x1, color);
//    }

//    if (d < 0)
//    {
//        d += 4 * x1 + 6;
//    }
//    else
//    {
//        d += 4 * (x1 - y1) + 10;
//        y1--;
//    }
//    x1++;
//  }
//}
