

#include "SSD1306.h"


/*------------------------------------------------------------------------------------------------
	+ Function: AT24Cxx_READ_ADDR8b
	+ Description: Gets the AT24Cxx I2C address (8-bit). Automatically shifts left by 1 for STM32 HAL.
	+ PARA IN: AT24Cxx_TypeDef *AT24Cxx,p0,p1,p2
	+ PARA OUT: 8bit I2C device address of AT24Cxx
------------------------------------------------------------------------------------------------*/

uint8_t SSD1306_READ_ADDR8b(SSD1306_Typedef *SSD1306,uint8_t SA0)
{
	SSD1306->deviceAddr=(0x3C|SA0)<<1;
	return (uint8_t)SSD1306->deviceAddr;
}

/*------------------------------------------------------------------------------------------------
	+ Function: SSD1306_INIT
	+ Description: Initialization parameters for the SSD1306
	+ PARA IN: I2C_HandleTypeDef *hi2c, void *ctx, SA0-bit address of SSD1306(You can check the back of the module: if the resistor sets 0x78 (SA0 = 0), if the resistor sets 0x7A (SA0 = 1))
	+ PARA OUT: Init status;
------------------------------------------------------------------------------------------------*/

void SSD1306_WRITE_COMMAND(SSD1306_Typedef *SSD1306,uint8_t CMD)
{
	uint8_t buff[2];
	buff[0]=0x00; // C0=0;D/C=0(Command) 
	buff[1]=CMD;
	HAL_I2C_Master_Transmit(SSD1306->PORT,SSD1306->deviceAddr,buff,2,SSD1306_TIMEOUT);
}

void SSD1306_WRITE_DATA(SSD1306_Typedef *SSD1306,uint8_t *data,uint16_t size)
{
	uint8_t buff[SSD1306_MAX_BYTE_SEND+1];
	buff[0]=0x40; // C0=0;D/C=1(Data)
	while(size)
	{
		uint16_t chunk=(size>SSD1306_MAX_BYTE_SEND)?SSD1306_MAX_BYTE_SEND:size;
		
		memcpy(&buff[1],data,chunk);
		HAL_I2C_Master_Transmit(SSD1306->PORT,SSD1306->deviceAddr,buff,chunk+1,SSD1306_TIMEOUT);
		
		data+=chunk;
		size-=chunk;
	}
}

void SSD1306_ROTATION(SSD1306_Typedef *SSD1306,uint8_t rotate)
{
	switch(rotate)
	{
		case SSD1306_ROTATION_0_DEGREE:
		{
			SSD1306->rotate=SSD1306_ROTATION_0_DEGREE;
			SSD1306->width=SSD1306_DISPLAY_WIDTH;
			SSD1306->height=SSD1306_DISPLAY_HEIGHT;
			break;
		}			
		case SSD1306_ROTATION_90_DEGREE:
		{
			SSD1306->rotate=SSD1306_ROTATION_90_DEGREE;
			SSD1306->width=SSD1306_DISPLAY_HEIGHT;
			SSD1306->height=SSD1306_DISPLAY_WIDTH;
			break;
		}
		case SSD1306_ROTATION_180_DEGREE:
		{
			SSD1306->rotate=SSD1306_ROTATION_180_DEGREE;
			SSD1306->width=SSD1306_DISPLAY_WIDTH;
			SSD1306->height=SSD1306_DISPLAY_HEIGHT;
			break;
		}
		case SSD1306_ROTATION_270_DEGREE:
		{
			SSD1306->rotate=SSD1306_ROTATION_270_DEGREE;
			SSD1306->width=SSD1306_DISPLAY_HEIGHT;
			SSD1306->height=SSD1306_DISPLAY_WIDTH;
			break;
		}
	}
}

static inline void SSD1306_DRAW_ROTATION(SSD1306_Typedef *SSD1306, int16_t x, int16_t y, int16_t *x0, int16_t *y0)
{
	switch(SSD1306->rotate)
	{
		case SSD1306_ROTATION_0_DEGREE:
		{
			*x0=x;
			*y0=y;
			break;
		}			
		case SSD1306_ROTATION_90_DEGREE:
		{
//			*x0 = SSD1306_DISPLAY_HEIGHT - 1 - y; // 64 - 1 - y
//      *y0 = x;
			*x0 = y;
			*y0 = SSD1306_DISPLAY_HEIGHT - 1 - x;
			break;
		}
		case SSD1306_ROTATION_180_DEGREE:
		{
			*x0=SSD1306_DISPLAY_WIDTH-1-x;
			*y0=SSD1306_DISPLAY_HEIGHT-1-y;
			break;
		}
		case SSD1306_ROTATION_270_DEGREE:
		{
//			 *x0 = y;
//       *y0 = SSD1306_DISPLAY_WIDTH - 1 - x;
			*x0 = SSD1306_DISPLAY_WIDTH - 1 - y;
			*y0 = x;
			break;
		}
	}
}

void SSD1306_DEFAULT_CONFIG(SSD1306_Typedef *SSD1306)
{
	SSD1306_WRITE_COMMAND(SSD1306, 0xAE); // DISPLAY OFF

  SSD1306_WRITE_COMMAND(SSD1306, 0xD5); // Set display clock
  SSD1306_WRITE_COMMAND(SSD1306, 0x80);

  SSD1306_WRITE_COMMAND(SSD1306, 0xA8); // MUX
  SSD1306_WRITE_COMMAND(SSD1306, 0x3F); // 64

  SSD1306_WRITE_COMMAND(SSD1306, 0xD3); // Display offset
  SSD1306_WRITE_COMMAND(SSD1306, 0x00);

  SSD1306_WRITE_COMMAND(SSD1306, 0x40); // Start line

  SSD1306_WRITE_COMMAND(SSD1306, 0x8D); // Charge pump
  SSD1306_WRITE_COMMAND(SSD1306, 0x14);

  SSD1306_WRITE_COMMAND(SSD1306, 0xA1); // Segment remap
  SSD1306_WRITE_COMMAND(SSD1306, 0xC8); // COM scan DEC

  SSD1306_WRITE_COMMAND(SSD1306, 0xDA); // COM pins
  SSD1306_WRITE_COMMAND(SSD1306, 0x12);

  SSD1306_WRITE_COMMAND(SSD1306, 0x81); // Contrast
  SSD1306_WRITE_COMMAND(SSD1306, 0x7F);

  SSD1306_WRITE_COMMAND(SSD1306, 0xD9); // Pre-charge
  SSD1306_WRITE_COMMAND(SSD1306, 0xF1);
	
	SSD1306_WRITE_COMMAND(SSD1306, 0x20); // Set addressing mode
	SSD1306_WRITE_COMMAND(SSD1306, 0x00); // Horizontal
	
	SSD1306_WRITE_COMMAND(SSD1306, 0x21); // Column range
	SSD1306_WRITE_COMMAND(SSD1306, 0x00);
	SSD1306_WRITE_COMMAND(SSD1306, 0x7F);
	
	SSD1306_WRITE_COMMAND(SSD1306, 0x22); // Page range
	SSD1306_WRITE_COMMAND(SSD1306, 0x00);
	SSD1306_WRITE_COMMAND(SSD1306, SSD1306_PAGE-1);

  SSD1306_WRITE_COMMAND(SSD1306, 0xDB); // VCOMH
  SSD1306_WRITE_COMMAND(SSD1306, 0x40);

  SSD1306_WRITE_COMMAND(SSD1306, 0xA4); // RAM display
  SSD1306_WRITE_COMMAND(SSD1306, 0xA6); // Normal display

  SSD1306_WRITE_COMMAND(SSD1306, 0xAF); // DISPLAY ON
	
	SSD1306_ROTATION(SSD1306,SSD1306_ROTATION_0_DEGREE); // 
}

HAL_StatusTypeDef SSD1306_INIT(SSD1306_Typedef *SSD1306,I2C_HandleTypeDef *hi2c,uint8_t SA0)
{
	HAL_StatusTypeDef stt;
	SSD1306->PORT=hi2c;
	SSD1306_READ_ADDR8b(SSD1306,SA0);
	
//	SSD1306->PORT->Init.ClockSpeed = 100000;
//  SSD1306->PORT->Init.DutyCycle = I2C_DUTYCYCLE_2;
//  SSD1306->PORT->Init.OwnAddress1 = 0;
//  SSD1306->PORT->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
//  SSD1306->PORT->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
//  SSD1306->PORT->Init.OwnAddress2 = 0;
//  SSD1306->PORT->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
//  SSD1306->PORT->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	
	stt=HAL_I2C_IsDeviceReady(SSD1306->PORT,SSD1306->deviceAddr,10,5000); // Polling ACK
	if(stt==HAL_OK)
	{
		SSD1306_DEFAULT_CONFIG(SSD1306);
	}
	return stt;
}

void SSD1306_SET_PX(void *ctx,int16_t x, int16_t y,uint32_t color)
{
	SSD1306_Typedef *SSD1306=(SSD1306_Typedef *) ctx;
	
	if(x>=SSD1306->width || y>=SSD1306->height || x<0 || y<0) return;
	
	int16_t x0=0,y0=0;
	
	SSD1306_DRAW_ROTATION(SSD1306,x,y,&x0,&y0);
	
	uint8_t page=y0/8;
	uint8_t bit=y0%8;
	uint16_t offset=page*SSD1306->width+x0;
	if(color)
	{
		SSD1306->BuffDisplay[offset]|=(0x01<<bit);
	}
	else
	{
		SSD1306->BuffDisplay[offset]&=~(0x01<<bit);
	}
}

void SSD1306_BLIT_MONO(void *ctx,int16_t x, int16_t y, int16_t w, int16_t h,const uint8_t *bitmap,uint16_t bytes_per_line,uint32_t color, uint32_t bg)
{
  if (!ctx || !bitmap) return;

  SSD1306_Typedef *SSD1306=(SSD1306_Typedef*)ctx;
	
	if(x>=SSD1306->width || y>=SSD1306->height || (x+w)<=0 || (y+h)<=0) return;
	
	int src_offset_x = 0;
	int src_offset_y = 0;
	
	// Clip left
	if (x < 0) 
	{
		src_offset_x = -x;
    w += x;
    x = 0;
	}
	
	// Clip top
	if (y < 0) 
	{
		src_offset_y = -y;
		h += y;
		y = 0;
	}
	
	// Clip right
	if (x + w > SSD1306->width) 
	{
		w = SSD1306->width - x;
	}
	
	// Clip bottom
	if (y + h > SSD1306->height) 
	{
		h = SSD1306->height - y;
	}
	
	if (w <= 0 || h <= 0) return;
	
	for (int fy = 0; fy < h; fy++)
	{
    const uint8_t *row = bitmap + (fy+src_offset_y) * bytes_per_line;

    for (int fx = 0; fx < w; fx++)
    {
			
			int16_t src_fx=fx+src_offset_x;
			
      uint8_t byte = row[src_fx >> 3];
      uint8_t bit_g = (byte >> (7 - (src_fx & 7))) & 1;

      int x0 = x + fx;
      int y0 = y + fy;

      int16_t xx, yy;

      SSD1306_DRAW_ROTATION(SSD1306, x0, y0, &xx, &yy);

      if (xx < 0 || xx >= SSD1306_DISPLAY_WIDTH || yy < 0 || yy >= SSD1306_DISPLAY_HEIGHT)
			{
				continue;
			}

      uint8_t page = yy / 8;
      uint8_t bit  = yy % 8;

      uint16_t offset = page * SSD1306_DISPLAY_WIDTH + xx;

      if (bit_g)
      {
        if (color)
				{
					SSD1306->BuffDisplay[offset] |= (1 << bit);
				}
            
        else
				{
					SSD1306->BuffDisplay[offset] &= ~(1 << bit);
				}    
      }
      else
      {
        if (bg)
				{
					SSD1306->BuffDisplay[offset] |= (1 << bit);
				}
            
        else
				{
					SSD1306->BuffDisplay[offset] &= ~(1 << bit);
				}     
      }
    }
	}
}

void SSD1306_UPDATE(void *ctx)
{
	if(!ctx) return;
	SSD1306_Typedef *SSD1306=(SSD1306_Typedef*)ctx;
	
	SSD1306_WRITE_DATA(SSD1306,SSD1306->BuffDisplay,SSD1306_SIZE_BUFF);
}

void SSD1306_CLEAR(void *ctx, uint32_t bg)
{
	if(!ctx) return;
	SSD1306_Typedef *SSD1306=(SSD1306_Typedef*)ctx;
	uint8_t color = bg?0xFF:0;
	
	memset(SSD1306->BuffDisplay,color,SSD1306_SIZE_BUFF);
}

void SSD1306_CLEAR_WINDOW(void *ctx, int16_t x, int16_t y, int16_t w, int16_t h, uint32_t bg)
{
	if(!ctx) return;
	
	SSD1306_Typedef *SSD1306=(SSD1306_Typedef*)ctx;
	
	if(x>=SSD1306->width || y>=SSD1306->height || (x+w)<=0 || (y+h)<=0) return;
	
	// Clip left
	if (x < 0) 
	{
    w += x;
    x = 0;
	}
	
	// Clip top
	if (y < 0) 
	{
		h += y;
		y = 0;
	}
	
	// Clip right
	if (x + w > SSD1306->width) 
	{
		w = SSD1306->width - x;
	}
	
	// Clip bottom
	if (y + h > SSD1306->height) 
	{
		h = SSD1306->height - y;
	}
	
	for (int fy = y; fy < y+h; fy++)
	{

		for (int fx = x; fx < x+w; fx++)
		{
			int16_t x0=0,y0=0;
			
			SSD1306_DRAW_ROTATION(SSD1306,fx,fy,&x0,&y0);
			
			if (x0 < 0 || x0 >= SSD1306_DISPLAY_WIDTH || y0 < 0 || y0 >= SSD1306_DISPLAY_HEIGHT)
			{
				continue;
			}
			
			uint8_t page=y0/8;
			uint8_t bit=y0%8;
			uint16_t offset=page*SSD1306_DISPLAY_WIDTH+x0;
			
      if(bg) 
			{
				SSD1306->BuffDisplay[offset] |= (1 << bit);
			}
      else 
			{
				SSD1306->BuffDisplay[offset] &= ~(1 << bit);
			}
		}
	}
}
