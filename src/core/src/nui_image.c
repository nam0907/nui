#include "../inc/nui_image.h"
#include "../inc/nui_draw.h"
#include "../inc/nui_port.h"
#include "../../int/nui_draw_int.h"

void NUI_IMAGE_DRAW_RGB565(void *ctx, int16_t x, int16_t y, uint16_t width , uint16_t height, const uint8_t *data)
{
	if (nui_drv && nui_drv->blit_color)
  {
     nui_drv->blit_color(ctx,x,y,0,0,width,height,data,width*2);
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

void NUI_IMAGE_DRAW_RGB888(void *ctx, int16_t x, int16_t y ,uint16_t width , uint16_t height, const uint8_t *data)
{
	if (nui_drv && nui_drv->blit_color)
  {
     nui_drv->blit_color(ctx,x,y,0,0,width,height,data,width*3);
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
     nui_drv->blit_mono(ctx,x,y,0,0,width,height,data,(width+7)>>3,1,0);
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

//void NUI_IMAGE_DRAW(void *ctx, int16_t x, int16_t y ,const Nui_Image_Typedef *image)
//{
//	if(!image->get_bitmap && !image->get_line) return;
//	
//	if(image->get_line)
//	{
//		uint8_t lineBuf[1024]={0};
//		uint16_t lineSize = 0;
//	
//		switch(image->format)
//		{
//			case NUI_IMAGE_FORMAT_MONO1BIT:
//			{
//				lineSize=(image->w+7)>>3;
//				break;
//			}
//			case NUI_IMAGE_FORMAT_RGB565:
//			{
//				lineSize=image->w*2;
//				break;
//			}
//			case NUI_IMAGE_FORMAT_RGB888:
//			{
//				lineSize=image->w*3;
//				break;
//			}
//			default:
//			{
//				lineSize=(image->w+7)>>3;
//				break;
//			}
//		}
//		
//		if(lineSize > sizeof(lineBuf)) return;
//		
//		for(uint16_t line=0; line<image->h; line++)
//		{
//			if(!image->get_line(image,lineSize,line,lineBuf)) return;
//			switch(image->format)
//			{
//				case NUI_IMAGE_FORMAT_RGB565:
//				{
//					NUI_IMAGE_DRAW_RGB565(ctx,x,y+line, image->w,1,lineBuf);
//					break;
//				}
//				case NUI_IMAGE_FORMAT_RGB888:
//				{
//					NUI_IMAGE_DRAW_RGB888(ctx,x,y+line,image->w,1,lineBuf);
//					break;
//				}
//				case NUI_IMAGE_FORMAT_MONO1BIT:
//				{
//					NUI_IMAGE_DRAW_MONO1BIT(ctx,x,y+line, image->w,1,lineBuf);
//					break;
//				}
//			}
//		}
//		
//	}
//	else if(image->get_bitmap)
//	{
//		const uint8_t *bitmap=image->get_bitmap(image);
//		if(bitmap)
//		{
//			switch(image->format)
//			{
//				case NUI_IMAGE_FORMAT_RGB565:
//				{
//					NUI_IMAGE_DRAW_RGB565(ctx,x,y, image->w,image->h,bitmap);
//					break;
//				}
//				case NUI_IMAGE_FORMAT_RGB888:
//				{
//					NUI_IMAGE_DRAW_RGB888(ctx,x,y,image->w,image->h,bitmap);
//					break;
//				}
//				case NUI_IMAGE_FORMAT_MONO1BIT:
//				{
//					NUI_IMAGE_DRAW_MONO1BIT(ctx,x,y, image->w,image->h,bitmap);
//					break;
//				}
//			}
//		}
//	}
//}

#if NUI_USE_IMAGE_SD
static uint8_t lineBuf[4096]={0};
#endif

void NUI_IMAGE_DRAW(void *ctx, int16_t x, int16_t y ,const Nui_Image_Typedef *image)
{
	if(!image->get_bitmap && !image->get_line) return;
	#if NUI_USE_IMAGE_SD
	if(image->get_line)
	{
		uint16_t lineSize = 0;
	
		switch(image->format)
		{
			case NUI_IMAGE_FORMAT_MONO1BIT:
			{
				lineSize=(image->w+7)>>3;
				break;
			}
			case NUI_IMAGE_FORMAT_RGB565:
			{
				lineSize=image->w*2;
				break;
			}
			case NUI_IMAGE_FORMAT_RGB888:
			{
				lineSize=image->w*3;
				break;
			}
			default:
			{
				lineSize=(image->w+7)>>3;
				break;
			}
		}
		
		if(lineSize > sizeof(lineBuf)) return;
		uint16_t curLine=0;
		uint16_t numLine=sizeof(lineBuf)/lineSize;
		while(curLine<image->h)
		{
			if(curLine + numLine > image->h) numLine=image->h-curLine;
			if(!image->get_line(image,lineSize,curLine, numLine,lineBuf)) return;
			switch(image->format)
			{
				case NUI_IMAGE_FORMAT_RGB565:
				{
					NUI_IMAGE_DRAW_RGB565(ctx,x,y+curLine, image->w,numLine,lineBuf);
					break;
				}
				case NUI_IMAGE_FORMAT_RGB888:
				{
					NUI_IMAGE_DRAW_RGB888(ctx,x,y+curLine,image->w,numLine,lineBuf);
					break;
				}
				case NUI_IMAGE_FORMAT_MONO1BIT:
				{
					NUI_IMAGE_DRAW_MONO1BIT(ctx,x,y+curLine, image->w,numLine,lineBuf);
					break;
				}
			}
			curLine+=numLine;
		}
	}
	
	#endif
	
	if(image->get_bitmap)
	{
		const uint8_t *bitmap=image->get_bitmap(image);
		if(bitmap)
		{
			switch(image->format)
			{
				case NUI_IMAGE_FORMAT_RGB565:
				{
					NUI_IMAGE_DRAW_RGB565(ctx,x,y, image->w,image->h,bitmap);
					break;
				}
				case NUI_IMAGE_FORMAT_RGB888:
				{
					NUI_IMAGE_DRAW_RGB888(ctx,x,y,image->w,image->h,bitmap);
					break;
				}
				case NUI_IMAGE_FORMAT_MONO1BIT:
				{
					NUI_IMAGE_DRAW_MONO1BIT(ctx,x,y, image->w,image->h,bitmap);
					break;
				}
			}
		}
	}
}

uint16_t NUI_IMAGE_GET_WIDTH(const Nui_Image_Typedef *image)
{
	return image->w;
}

uint16_t NUI_IMAGE_GET_HEIGHT(const Nui_Image_Typedef *image)
{
	return image->h;
}

void NUI_IMAGE_DRAW_IMAGE(void *ctx, int16_t x, int16_t y ,const Nui_Image_Typedef *image)
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
