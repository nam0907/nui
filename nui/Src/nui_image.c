#include "nui_image.h"
#include "nui_draw.h"
#include "nui_port.h"

void NUI_IMAGE_DRAW_RGB565(void *ctx, int16_t x, int16_t y, uint16_t width , uint16_t height, const uint8_t *data)
{
	if (nui_drv && nui_drv->blit_color)
  {
     nui_drv->blit_color(ctx,x,y,width,height,data);
  }
	else
	{
		for(int16_t h=0; h<height; h++)
		{
//			int16_t idx=0;
			for(int16_t w=0; w<width; w++)
			{
				int16_t index= h*width+w;
				uint16_t colorTmp=(uint16_t)data[(index*2)]<<8;
				colorTmp |= data[(index*2)+1];
				
				uint8_t r=(colorTmp>>11) & RGB565_RMASK; 
				uint8_t g=(colorTmp>>5) & RGB565_GMASK;
				uint8_t b=(colorTmp) & RGB565_BMASK;
				
				// scale bit tu 5,6 bit len 8 bit bang cach lay bit cao lap lai bit thap
				r = (r << 3) | (r >> 2); 
				g = (g << 2) | (g >> 4);
				b = (b << 3) | (b >> 2);
				
				uint32_t color=(uint32_t)r<<16 | (uint32_t)g<<8 | b;
				nui_draw_pixel(ctx,x+w,y+h,color);
			}
		}
	}
}

//void NUI_IMAGE_DRAW_RGB565_CLIP(WidgetClip_Typedef clip, int16_t x, int16_t y, uint16_t width , uint16_t height, const uint8_t *data)
//{
//	if (nui_drv && nui_drv->blit_color)
//  {
//     nui_drv->blit_color(clip.ctx,x,y,width,height,data);
//  }
//	else
//	{
//		for(int16_t h=0; h<height; h++)
//		{
////			int16_t idx=0;
//			for(int16_t w=0; w<width; w++)
//			{
//				int16_t index= h*width+w;
//				uint16_t colorTmp=(uint16_t)data[(index*2)]<<8;
//				colorTmp |= data[(index*2)+1];
//				
//				uint8_t r=(colorTmp>>11) & RGB565_RMASK; 
//				uint8_t g=(colorTmp>>5) & RGB565_GMASK;
//				uint8_t b=(colorTmp) & RGB565_BMASK;
//				
//				// scale bit tu 5,6 bit len 8 bit bang cach lay bit cao lap lai bit thap
//				r = (r << 3) | (r >> 2); 
//				g = (g << 2) | (g >> 4);
//				b = (b << 3) | (b >> 2);
//				
//				uint32_t color=(uint32_t)r<<16 | (uint32_t)g<<8 | b;
//				nui_draw_pixel_clip(clip.ctx,x+w,y+h,color);
//			}
//		}
//	}
//}	

void NUI_IMAGE_DRAW_RGB888(void *ctx, int16_t x, int16_t y ,uint16_t width , uint16_t height, const uint8_t *data)
{
	if (nui_drv && nui_drv->blit_color)
  {
     nui_drv->blit_color(ctx,x,y,width,height,data);
  }
	else
	{
		for(int16_t h=0; h<height; h++)
		{
//			int16_t idx=0;
			for(int16_t w=0; w<width; w++)
			{
				int16_t index= h*width+w;
				
				uint8_t r=data[(index*3)]; 
				uint8_t g=data[(index*3)+1];
				uint8_t b=data[(index*3)+2];
				
				uint32_t color=(uint32_t)r<<16 | (uint32_t)g<<8 | b;
				nui_draw_pixel(ctx,x+w,y+h,color);
			}
		}
	}
	
}	

void NUI_IMAGE_DRAW_MONO1BIT(void *ctx, int16_t x, int16_t y, uint16_t width , uint16_t height, const uint8_t *data)
{
	if (nui_drv && nui_drv->blit_mono)
  {
     nui_drv->blit_mono(ctx,x,y,width,height,data,(width+7)/8,1,0);
  }
	else
	{
		for (uint16_t fy = 0; fy < height; fy++)
    {
      for (uint16_t fx = 0; fx < width; fx++)
      {
        uint32_t byte_index = fy * (width+7)/8 + (fx >> 3);
        uint8_t bit_mask = 0x80 >> (fx & 7);

        if (data[byte_index] & bit_mask)
        {
					nui_draw_pixel(ctx, x + fx, y + fy, 1);
        }
        else
        {
					nui_draw_pixel(ctx, x + fx, y + fy, 0);
        }
      }
    }
	}
	
}	

void NUI_IMAGE_DRAW(void *ctx, int16_t x, int16_t y ,Image_Typedef image)
{
	switch(image.Format)
	{
		case FORMAT_RGB565:
		{
			NUI_IMAGE_DRAW_RGB565(ctx,x,y, image.Width,image.Height, image.Data);
			break;
		}
		case FORMAT_RGB888:
		{
			NUI_IMAGE_DRAW_RGB888(ctx,x,y,image.Width,image.Height,image.Data);
			break;
		}
		case FORMAT_MONO1BIT:
		{
			NUI_IMAGE_DRAW_MONO1BIT(ctx,x,y, image.Width,image.Height, image.Data);
			break;
		}
	}
}

uint16_t NUI_IMAGE_GET_WIDTH(Image_Typedef image)
{
	return image.Width;
}

uint16_t NUI_IMAGE_GET_HEIGHT(Image_Typedef image)
{
	return image.Height;
}

void NUI_IMAGE_DRAW_IMAGE(void *ctx, int16_t x, int16_t y ,Image_Typedef image)
{
	NUI_IMAGE_DRAW(ctx,x,y,image);
}

//void NUI_IMAGE_DRAW_IMAGE_CLIP(WidgetClip_Typedef clip, int16_t x, int16_t y ,Image_Typedef image)
//{
////	WidgetClip_Typedef clip;
////	clip.ctx = ctx;
////	clip.isClip = false;
//	NUI_IMAGE_DRAW(clip.ctx,x,y,image);
//}

//void NUI_IMAGE_DRAW_ImgGraphic(void *ctx,ImageGraphic_Typedef imgG)
//{
//	NUI_IMAGE_DRAW_IMAGE_UI(ctx,imgG.PosX,imgG.PosY, imgG.Img);
//}
