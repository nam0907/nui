#include "nui_font.h"
#include "nui_port.h"

uint16_t NUI_FONT_GET_WIDTH(const uint8_t *str,Font_Typedef font)
{
	uint8_t offset=0;
	uint16_t width=0;
	while(*str)
	{
		
		uint32_t indexTmp=NUI_FONT_GET_ADDR(str,&offset, font);
		indexTmp=indexTmp-font.offset;
		uint32_t Char = font.Font_Map[indexTmp];
		uint8_t Char_W = font.Font[Char - 4];// Chieu rong cua chu
		width+=Char_W+UTF8_GAP;
		str+=offset;
	}
	
	return width;
}

uint16_t NUI_FONT_GET_HEIGHT(const uint8_t *str,Font_Typedef font,int16_t *min_top, int16_t *max_bottom)
{
	uint8_t offset=0;
	
	*min_top = 32767;
  *max_bottom = -32768;
	while(*str)
	{
		
		uint32_t indexTmp=NUI_FONT_GET_ADDR(str, &offset, font);
		indexTmp=indexTmp-font.offset;
		uint32_t Char = font.Font_Map[indexTmp];
		uint8_t Char_H = font.Font[Char - 3];// Chieu cao cua chu
		int16_t offset_y = font.Font[Char - 1]; // Do lech cua chu so voi baseline 
		
		int16_t top    = offset_y;
    int16_t bottom = offset_y + Char_H;

    if (top < *min_top)        *min_top = top;
    if (bottom > *max_bottom)  *max_bottom = bottom;
		
		
		str+=offset;
	}
	
	if (*min_top > *max_bottom) return 0;
	
	return (uint16_t)(*max_bottom - *min_top);
}

uint32_t NUI_FONT_GET_ADDR(const uint8_t *txt, uint8_t *offset,Font_Typedef font)
{
	*offset = 1;
	if(*txt<UTF8_START2)
	{
		for(int i=0;i<font.numChar;i++)
		{
			if(*txt==font.Font_Ref[i])
			{
				return i;
			}
		}
	}
	else
	{
		uint32_t value=0;
		uint8_t mask=0;
		mask=*txt&0xF0;
		
		if(mask==0xC0) // UTF-8 loai 2 byte
		{
			*offset=2;
			value=(uint32_t)txt[0]<<8|txt[1];
		}
		else if(mask==0xE0) // UTF-8 loai 3 byte
		{
			*offset=3;
			value=(uint32_t)txt[0]<<16|(uint32_t)txt[1]<<8|txt[2];
		}
		else if(mask==0xF0) // UTF-8 loai 4 byte
		{
			*offset=4;
			value=(uint32_t)txt[0]<<24|(uint32_t)txt[2]<<16|(uint32_t)txt[3]<<8|txt[4];
		}
		for(int i=0;i<font.numChar;i++)
		{
			if(value==font.Font_Ref[i])
			{
				return i;
//				if(i<=UTF8_END1)
//				{
//					return i+1;
//				}
//				else
//				{
//					return i+UTF8_START2-UTF8_END1-1;
//				}
			}
		}
	}  
	return 0;
}

uint8_t NUI_FONT_DRAW_CHAR(void *ctx,int16_t x, int16_t y,uint16_t index,Font_Typedef font,uint32_t color, uint32_t bg)
{
  uint16_t indextmp = index - font.offset;
  uint32_t str = font.Font_Map[indextmp];

  uint8_t Char_W = font.Font[str - 4];// Chieu rong cua chu
  uint8_t Char_H = font.Font[str - 3];// Chieu cao cua chu
  uint16_t bytes_per_line = font.Font[str - 2]; // so byte tren 1 hang
  int16_t offset_y = font.Font[str - 1]; // Do lech cua chu so voi baseline 
  int16_t start_y = offset_y; // Diem bat dau cua chu so voi toa do cho truoc

  const uint8_t *bitmap = &font.Font[str];

  if (nui_drv && nui_drv->blit_mono)
  {
     nui_drv->blit_mono(ctx,x,y + start_y,Char_W,Char_H,bitmap,bytes_per_line,color, bg);
  }
  else
  {
    for (uint16_t fy = 0; fy < Char_H; fy++)
    {
      for (uint16_t fx = 0; fx < Char_W; fx++)
      {
        uint32_t byte_index = fy * bytes_per_line + (fx >> 3);
        uint8_t bit_mask = 0x80 >> (fx & 7);

        if (bitmap[byte_index] & bit_mask)
        {
					nui_draw_pixel(ctx, x + fx, y + fy + start_y, color);
        }
        else
        {
					nui_draw_pixel(ctx, x + fx, y + fy + start_y, 0);
        }
      }
    }
  }

  return Char_W;
}


void NUI_FONT_DRAW_STRING(void *ctx, int16_t x, int16_t y, const uint8_t *str, Font_Typedef font,uint32_t color, uint32_t bg)
{
	uint8_t offset=0;

	while(*str)
	{
		uint16_t indexTmp=NUI_FONT_GET_ADDR(str,&offset,font);
		x+=NUI_FONT_DRAW_CHAR(ctx,x,y,indexTmp,font,color,bg);
		str+=offset;
	}
}

void NUI_FONT_DRAW_STRING_CLIP(WidgetClip_Typedef *clip, int16_t x, int16_t y, const uint8_t *str, Font_Typedef font,uint32_t color, uint32_t bg)
{
	uint8_t offset=0;
	while(*str)
	{
		uint16_t indexTmp=NUI_FONT_GET_ADDR(str,&offset, font);
		x+=NUI_FONT_DRAW_CHAR(clip->ctx,x,y,indexTmp,font,color, bg);
		str+=offset;
	}
}

//void NUI_FONT_DRAW_STRGraphic(WidgetClip_Typedef *clip,StringGraphic_Typedef strG, Font_Typedef font)
//{
//	NUI_FONT_DRAW_STRING_CLIP(clip->ctx,strG.PosX,strG.PosY, strG.Text,font,strG.Color);
//}
