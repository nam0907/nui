#include "../inc/nui_font.h"
#include "../inc/nui_port.h"
#include "../inc/nui_draw.h"
#include "../../int/nui_draw_int.h"
#include "../../int/nui_font_int.h"
#include "../../int/nui_font_def_int.h"

uint32_t NUI_FONT_UTF8_DECODE(const uint8_t *txt, uint8_t *offset)
{
	*offset = 1;
	if(txt[0]<ACSCII_END)
	{
		return txt[0];
	}
	else
	{
		uint32_t value=0;
		
		if((*txt & 0xE0)==0xC0) // UTF-8 loai 2 byte
		{
			*offset=2;
			value=(uint32_t)txt[0]<<8|txt[1];
		}
		else if((*txt & 0xF0)==0xE0) // UTF-8 loai 3 byte
		{
			*offset=3;
			value=(uint32_t)txt[0]<<16|(uint32_t)txt[1]<<8|txt[2];
		}
		else if((*txt & 0xF8)==0xF0) // UTF-8 loai 4 byte
		{
			*offset=4;
			value=(uint32_t)txt[0]<<24|(uint32_t)txt[1]<<16|(uint32_t)txt[2]<<8|txt[3];
		}
		
		return value;
	}  
}

uint16_t NUI_FONT_GET_WIDTH(const uint8_t *str, const Nui_Font_Typedef *font)
{
	uint8_t offset=0;
	uint16_t width=0;
	uint8_t cnt=0;
	Nui_Glyph_Typedef glyph;
	while(*str)
	{
		
		uint32_t unicode=NUI_FONT_UTF8_DECODE(str,&offset);
		if(!font->get_glyph(font, unicode, &glyph)) break;
		width+=glyph.w;
		if(cnt>0)
		{
			width+=font->gap;
		}
	}
	
	return width;
}

//uint16_t NUI_FONT_GET_HEIGHT(const uint8_t *str,const Nui_Font_Typedef *font,int16_t *min_top, int16_t *max_bottom)
//{
//	uint8_t offset=0;
//	
//	*min_top = 32767;
//  *max_bottom = -32768;
//	while(*str)
//	{
//		
//		uint32_t indexTmp=NUI_FONT_GET_ADDR(str, &offset, font);
//		uint32_t Char = font->Font_Map[indexTmp];
//		uint8_t Char_H = font->Font[Char - 3];// Chieu cao cua chu
//		int16_t offset_y = font->Font[Char - 1]; // Do lech cua chu so voi baseline 
//		
//		int16_t top    = offset_y;
//    int16_t bottom = offset_y + Char_H;

//    if (top < *min_top)        *min_top = top;
//    if (bottom > *max_bottom)  *max_bottom = bottom;
//		
//		
//		str+=offset;
//	}
//	
//	if (*min_top > *max_bottom) return 0;
//	
//	return (uint16_t)(*max_bottom - *min_top);
//}

uint16_t NUI_FONT_GET_HEIGHT(const uint8_t *str,const Nui_Font_Typedef *font,int16_t *min_top, int16_t *max_bottom)
{
	uint8_t offset=0;
	
	*min_top = 32767;
  *max_bottom = -32768;
	Nui_Glyph_Typedef glyph;
	while(*str)
	{
		
		uint32_t unicode=NUI_FONT_UTF8_DECODE(str,&offset);
		if(!font->get_glyph(font, unicode, &glyph)) break;
//		font->get_glyph(font, unicode, &glyph);
		
		int16_t top    = glyph.offset;
    int16_t bottom = glyph.offset + glyph.h;

    if (top < *min_top)        *min_top = top;
    if (bottom > *max_bottom)  *max_bottom = bottom;
		
		
		str+=offset;
	}
	
	if (*min_top > *max_bottom) return 0;
	
	return (uint16_t)(*max_bottom - *min_top);
}

//void NUI_FONT_DRAW_CHAR(void *ctx,int16_t x, int16_t y, int16_t src_x,int16_t src_y,int16_t draw_w, int16_t draw_h, uint16_t index,const Nui_Font_Typedef *font,uint32_t color, uint32_t backColor)
//{
//  uint32_t map = font->Font_Map[index];

//  uint16_t bytes_per_line = font->Font[map - 2]; // so byte tren 1 hang
//  int16_t offset_y = font->Font[map - 1]; // Do lech cua chu so voi baseline 
//  int16_t start_y = offset_y; // Diem bat dau cua chu so voi toa do cho truoc

//  const uint8_t *bitmap = &font->Font[map];

//  if (nui_drv && nui_drv->blit_mono)
//  {
//     nui_drv->blit_mono(ctx,x,y + start_y,src_x,src_y,draw_w,draw_h,bitmap,bytes_per_line,color, backColor);
//  }
//  else
//  {
//    for (uint16_t fy = 0; fy < draw_h; fy++)
//    {
//			int16_t sy = fy + src_y;
//      for (uint16_t fx = 0; fx < draw_w; fx++)
//      {
//				int16_t sx = fx + src_x;
//        uint32_t byte_index = sy * bytes_per_line + (sx >> 3);
//        uint8_t bit_mask = 0x80 >> (sx & 7);

//        if (bitmap[byte_index] & bit_mask)
//        {
//					nui_draw_pixel(ctx, x + fx, y + fy + start_y, color);
//        }
//        else
//        {
//					nui_draw_pixel(ctx, x +fx, y + fy + start_y, backColor);
//        }
//      }
//    }
//  }

//}

void NUI_FONT_DRAW_CHAR(void *ctx,int16_t x, int16_t y, int16_t src_x,int16_t src_y,int16_t draw_w, int16_t draw_h,const Nui_Glyph_Typedef *glyph,uint32_t color, uint32_t backColor)
{
	
  uint16_t bytes_per_line = glyph->bytePerRow; // so byte tren 1 hang
  int16_t start_y = glyph->offset; // Do lech cua chu so voi baseline 

  const uint8_t *bitmap = glyph->bitmap;

  if (nui_drv && nui_drv->blit_mono)
  {
     nui_drv->blit_mono(ctx,x,y + start_y,src_x,src_y,draw_w,draw_h,bitmap,bytes_per_line,color, backColor);
  }
  else
  {
    for (uint16_t fy = 0; fy < draw_h; fy++)
    {
			int16_t sy = fy + src_y;
      for (uint16_t fx = 0; fx < draw_w; fx++)
      {
				int16_t sx = fx + src_x;
        uint32_t byte_index = sy * bytes_per_line + (sx >> 3);
        uint8_t bit_mask = 0x80 >> (sx & 7);

        if (bitmap[byte_index] & bit_mask)
        {
					nui_draw_pixel(ctx, x + fx, y + fy + start_y, color);
        }
        else
        {
					nui_draw_pixel(ctx, x +fx, y + fy + start_y, backColor);
        }
      }
    }
  }

}

//void NUI_FONT_DRAW_STRING_RENDER(void *ctx,const Nui_Rect_Typedef *clip,int16_t x,int16_t y,const uint8_t *str,const Nui_Font_Typedef *font,uint32_t color,uint32_t backColor)
//{
//  uint8_t offset = 0;

//  while(*str)
//  {
//    uint16_t indexTmp = NUI_FONT_GET_ADDR(str, &offset, font);
//    uint32_t map = font->Font_Map[indexTmp];

//    uint8_t Char_W = font->Font[map - 4];
//    uint8_t Char_H = font->Font[map - 3];

//    // Skip glyph out left
//    if(clip)
//    {
//      if((x + Char_W+font->gap) <= clip->x) // Neu ki tu nam hoan toan ben ngoai toa do clip se bo qua ki tu nay
//      {
//        x = x+Char_W+font->gap; // tang x len de lay toa do hien thi cac ki tu sau hien thi cac ki tu sau
//        str += offset;
//        continue; // bo qua ki tu nay
//      }

//      // Skip glyph out right
//      if(x >= (clip->x + clip->w))
//      {
//				break;
//      }
//    }

//    Nui_Draw_Rect_Typedef draw =
//    {
//      .dst_x = x,
//      .dst_y = y,

//      .src_x = 0,
//      .src_y = 0,

//      .w = Char_W,
//      .h = Char_H
//    };

//    if(clip)
//    {
//      if(!nui_clip_rect(clip, &draw))
//      {
//        x = x+Char_W+font->gap;
//        str += offset;
//        continue;
//      }
//    }

//    NUI_FONT_DRAW_CHAR(ctx,draw.dst_x,draw.dst_y,draw.src_x,draw.src_y,draw.w,draw.h,indexTmp,font,color,backColor);
//    x = x+Char_W+font->gap;
//    str += offset;
//  }
//}

//Nui_Glyph_Typedef glyph;

void NUI_FONT_DRAW_STRING_RENDER(void *ctx,const Nui_Rect_Typedef *clip,int16_t x,int16_t y,const uint8_t *str,const Nui_Font_Typedef *font,uint32_t color,uint32_t backColor)
{
  uint8_t offset = 0;
	
  while(*str)
  {
		Nui_Glyph_Typedef glyph;
		uint32_t unicode=NUI_FONT_UTF8_DECODE(str,&offset);
		if(!font->get_glyph(font, unicode, &glyph)) break;
//		font->get_glyph(font, unicode, &glyph);
		

    // Skip glyph out left
    if(clip)
    {
      if((x + glyph.w+font->gap) <= clip->x) // Neu ki tu nam hoan toan ben ngoai toa do clip se bo qua ki tu nay
      {
        x = x+glyph.w+font->gap; // tang x len de lay toa do hien thi cac ki tu sau hien thi cac ki tu sau
        str += offset;
        continue; // bo qua ki tu nay
      }

      // Skip glyph out right
      if(x >= (clip->x + clip->w))
      {
				break;
      }
    }

    Nui_Draw_Rect_Typedef draw =
    {
      .dst_x = x,
      .dst_y = y,

      .src_x = 0,
      .src_y = 0,

      .w = glyph.w,
      .h = glyph.h
    };

    if(clip)
    {
      if(!nui_clip_rect(clip, &draw))
      {
        x = x+glyph.w+font->gap;
        str += offset;
        continue;
      }
    }

    NUI_FONT_DRAW_CHAR(ctx,draw.dst_x,draw.dst_y,draw.src_x,draw.src_y,draw.w,draw.h,&glyph,color,backColor);
    x = x+glyph.w+font->gap;
    str += offset;
  }
}

void NUI_FONT_DRAW_STRING(void *ctx, int16_t x, int16_t y, const uint8_t *str, const Nui_Font_Typedef *font,uint32_t color, uint32_t backColor)
{
	NUI_FONT_DRAW_STRING_RENDER(ctx,NULL,x,y,str,font,color,backColor);
}

#if NUI_WDG_USE_TXT_GRAPH
void NUI_FONT_DRAW_TXT_GRAPH(void *ctx,const Nui_Rect_Typedef *clip ,const Nui_Txt_Graph_Typedef *txtGraph)
{
	NUI_FONT_DRAW_STRING_RENDER(ctx,clip,txtGraph->x,txtGraph->y,txtGraph->txt,txtGraph->font,txtGraph->color,txtGraph->backColor);
}

#endif

