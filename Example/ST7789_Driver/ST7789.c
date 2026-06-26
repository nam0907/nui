
#include "ST7789.h"

#if ST7789_USING_SPI_DMA
static uint16_t DmaBuf[2][ST7789_MAX_BYTE_SEND];
#else
static uint16_t line_buf[ST7789_DISPLAY_WIDTH_MAX];
#endif

///*------------------------------------------------------------------------------------------------
//	+ Function: ST7789_REGISTER_CS_PIN
//	+ Description: Register chip select(CS) pin for ST7789.
//	+ PARA IN: 
//		. *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
//		. *CS_Port: Pointer to GPIO_TypeDef.
//		. CS_PIN:  Chip select(CS) pin.  
//	+ PARA OUT: None
//------------------------------------------------------------------------------------------------*/

//void ST7789_REGISTER_CS_PIN(ST7789_Typedef *ST7789, GPIO_TypeDef *CS_Port, uint16_t CS_PIN)
//{
//	ST7789->CS_Port=CS_Port;
//	ST7789->CS_PIN=CS_PIN;
//}

///*------------------------------------------------------------------------------------------------
//	+ Function: ST7789_REGISTER_DC_PIN
//	+ Description: Register data/command(DC) pin for ST7789.
//	+ PARA IN: 
//		. *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
//		. *DC_Port: Pointer to GPIO_TypeDef.
//		. DC_PIN:  data/command(DC) pin.  
//	+ PARA OUT: None
//------------------------------------------------------------------------------------------------*/

void ST7789_RESET(ST7789_Typedef *ST7789)
{
	ST7789->WriteReset(0);// RST low to RST LCD
	ST7789->Delay(150); 
	ST7789->WriteReset(1); // RST High to normal 
}

void ST7789_SEND_SPI(ST7789_Typedef *ST7789,const uint8_t *data, uint16_t len)
{
	ST7789->WriteCS(0); // CS low to select chip
	ST7789->SPITransmit(data, len);
	ST7789->WriteCS(1); // CS high to ignore SCK
}

void ST7789_SEND_SPI_DMA(ST7789_Typedef *ST7789,const uint8_t *data, uint16_t len)
{
	ST7789->WriteCS(0); // CS low to select chip
	ST7789->SPITransmitDma(data, len);
}

void ST7789_WRITE_COMMAND(ST7789_Typedef *ST7789, uint8_t cmd)
{
	ST7789->WriteDC(0); // DC low to send Command
	ST7789_SEND_SPI(ST7789,&cmd,1);
	ST7789->WriteDC(1); // DC high to send data
}

#if ST7789_USING_SPI_DMA
void ST7789_WRITE_DATA_DMA(ST7789_Typedef *ST7789, const uint8_t *data, uint16_t Size)
{
	ST7789->dma.DmaRemain=Size;
	ST7789->dma.DmaPtr=data;
	uint16_t chunk=(ST7789->dma.DmaRemain>ST7789_MAX_BYTE_SEND)?ST7789_MAX_BYTE_SEND:ST7789->dma.DmaRemain;
		
	ST7789->dma.DmaRemain -= chunk;
  ST7789->dma.DmaPtr = data + chunk;
	
	ST7789_SEND_SPI_DMA(ST7789,data,chunk);
}

void ST7789_SPI_TRANSMIT_DMA_CALLBACK(ST7789_Typedef *ST7789)
{
	if(ST7789->dma.DmaRemain>0)
	{
		uint16_t chunk=(ST7789->dma.DmaRemain>ST7789_MAX_BYTE_SEND)?ST7789_MAX_BYTE_SEND:ST7789->dma.DmaRemain;
		ST7789_SEND_SPI_DMA(ST7789,ST7789->dma.DmaPtr,chunk);
		ST7789->dma.DmaRemain-=chunk;
		ST7789->dma.DmaPtr+=chunk;
	}
	else
	{
		ST7789->WriteCS(1); // CS high to ignore SCK
		return;
	}
}

uint16_t ST7789_FILL_COLOR_BUFF_DMA(ST7789_Typedef *ST7789, uint8_t *buf)
{
	uint16_t line_size=ST7789->blit.width*2;
	uint16_t max_line=ST7789_MAX_BYTE_SEND/line_size;
	if(max_line > ST7789->blit.RemainLine)
	{
		 max_line = ST7789->blit.RemainLine;
	} 
	uint8_t *dst = buf;
	
	for(uint16_t y=0;y<max_line;y++)
  {
    const uint8_t *src =ST7789->blit.SrcData +((ST7789->blit.SrcY + ST7789->blit.CurrentLine +y) *ST7789->blit.BytesPerLine)+ST7789->blit.SrcX * 2;

    memcpy(dst,src,line_size);

    dst += line_size;
  }

  ST7789->blit.CurrentLine += max_line;
  ST7789->blit.RemainLine  -= max_line;

  return max_line * line_size;
}

uint16_t ST7789_FILL_MONO_BUFF_DMA(ST7789_Typedef *ST7789, uint8_t *buf, uint16_t color_swapped, uint16_t backColor_swapped)
{
	uint16_t line_size=ST7789->blit.width*2;
	uint16_t max_line=ST7789_MAX_BYTE_SEND/line_size;
	if(max_line > ST7789->blit.RemainLine)
	{
		 max_line = ST7789->blit.RemainLine;
	} 
	uint16_t *dst16 = (uint16_t *)buf;
	
	for (int fy = 0; fy < max_line; fy++)
	{
		const uint8_t *row = ST7789->blit.SrcData + (fy + ST7789->blit.SrcY + ST7789->blit.CurrentLine) * ST7789->blit.BytesPerLine;
		uint16_t *line = dst16 + fy * ST7789->blit.width;
		for (int fx = 0; fx < ST7789->blit.width; fx++)
		{
			
			uint16_t sx = fx + ST7789->blit.SrcX;
			uint8_t byte = row[sx >> 3];
			uint8_t bit  = (byte >> (7 - (sx & 7))) & 1;
		
//			line_buf[fx] = bit ? color16 : backColor16;
			line[fx] = bit ? color_swapped : backColor_swapped;
		}
	}

  ST7789->blit.CurrentLine += max_line;
  ST7789->blit.RemainLine  -= max_line;

  return max_line * line_size;
}

uint16_t ST7789_FILL_CLEAR_BUFF_DMA(ST7789_Typedef *ST7789, uint8_t *buf, uint16_t color_swapped)
{
	uint16_t line_size=ST7789->blit.width*2;
	uint16_t max_line=ST7789_MAX_BYTE_SEND/line_size;
	if(max_line > ST7789->blit.RemainLine)
	{
		 max_line = ST7789->blit.RemainLine;
	} 
	uint16_t *dst16 = (uint16_t *)buf;
	
	
	
	for (int fy = 0; fy < max_line; fy++)
	{
		const uint8_t *row = ST7789->blit.SrcData + (fy + ST7789->blit.SrcY + ST7789->blit.CurrentLine) * ST7789->blit.BytesPerLine;
		uint16_t *line = dst16 + fy * ST7789->blit.width;
		for (int fx = 0; fx < ST7789->blit.width; fx++)
		{
			
			uint16_t sx = fx + ST7789->blit.SrcX;
			uint8_t byte = row[sx >> 3];
			uint8_t bit  = (byte >> (7 - (sx & 7))) & 1;
		
//			line_buf[fx] = bit ? color16 : backColor16;
			line[fx] = color_swapped;
		}
	}

  ST7789->blit.CurrentLine += max_line;
  ST7789->blit.RemainLine  -= max_line;

  return max_line * line_size;
}

#endif

void ST7789_WRITE_DATA(ST7789_Typedef *ST7789, const uint8_t *data, uint16_t Size)
{
	uint16_t chunk=0;
	while(Size)
	{
		chunk=(Size>ST7789_MAX_BYTE_SEND)?ST7789_MAX_BYTE_SEND:Size;
		
		ST7789_SEND_SPI(ST7789,data,chunk);
		
		Size-=chunk;
		data+=chunk;
	}
}

void ST7789_SET_INVERSION(ST7789_Typedef *ST7789, bool invs)
{
	if(invs)
	{
		ST7789->cfg.invs=ST7789_CMD_INVERSION_ON; // Display Inversion ON (21h)
	}
	else 
	{
		ST7789->cfg.invs=ST7789_CMD_INVERSION_OFF; // Display Inversion OFF (20h)
	}
	ST7789_WRITE_COMMAND(ST7789, ST7789->cfg.invs);
}

/*------------------------------------------------------------------------------------------------
	+ Function: ST7789_SET_MADCTL
	+ Description: Set MADCTL for ST7789.
	+ PARA IN: 
		. *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
	+ PARA OUT: None
------------------------------------------------------------------------------------------------*/

void ST7789_SET_MADCTL(ST7789_Typedef *ST7789, uint8_t madctl)
{
	uint8_t mv = (madctl >> 5)&0x01;
	if(mv)
	{
		ST7789->width=ST7789_DISPLAY_HEIGHT;
		ST7789->height=ST7789_DISPLAY_WIDTH;
	}
	else
	{
		ST7789->width=ST7789_DISPLAY_WIDTH;
		ST7789->height=ST7789_DISPLAY_HEIGHT;
	}
	ST7789->cfg.madctl=madctl;
	
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_MEM_ACCSESS_CTRL); //  Memory Data Access Control (36h)
	ST7789_WRITE_DATA(ST7789,&ST7789->cfg.madctl,1);
}

/*------------------------------------------------------------------------------------------------
	+ Function: ST7789_DISPLAY_INVERSION
	+ Description: Set display inversion mode for ST7789.
	+ PARA IN: 
		. *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
		. Inversion:  Display inversion mode for ST7789. This parameter can be one of this value: 
				 true: Display inversion mode on
				 false: Display inversion mode off
	+ PARA OUT: None
------------------------------------------------------------------------------------------------*/

void ST7789_DISPLAY_INVERSION(ST7789_Typedef *ST7789, bool inversion)
{
	if(inversion) ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_INVERSION_ON);
	else if(!inversion) ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_INVERSION_OFF);
}

void ST7789_DEFAULT_CONFIG(ST7789_Typedef *ST7789)
{
	uint8_t buff[5];
	
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_RST); // Soft Reset (01h)
	ST7789->Delay(120);
	
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_SLEEP_OUT); // Sleep out mode (11h)
	ST7789->Delay(120);
	
	ST7789_SET_MADCTL(ST7789,0x00);
	
	ST7789_SET_INVERSION(ST7789,true); // Normal Display Mode On (13h)
	
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_INTERFACE_PX_FORMAT); //  Interface Pixel Format (3Ah)
	buff[0]=ST7789_INTERFACE_COLOR; //Control interface color format
	ST7789_WRITE_DATA(ST7789,buff,1);
	
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_DISPLAY_ON); // Display on (29h)
}


/*------------------------------------------------------------------------------------------------
	+ Function: ST7789_INIT
	+ Description: Init default parameter for ST7789.
	+ PARA IN: 
		. *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
		. *SPI_Port: Pointer to SPI_HandleTypeDef structure config for SPI STM32 
	+ PARA OUT: None
------------------------------------------------------------------------------------------------*/

void ST7789_INIT(ST7789_Typedef *ST7789)
{

	ST7789_RESET(ST7789);
	
	ST7789_DEFAULT_CONFIG(ST7789);
	
}

/*------------------------------------------------------------------------------------------------
	+ Function: ST7789_SET_WINDOW
	+ Description: Set window display for ST7789.
	+ PARA IN: 
		. *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
		. x: x position window display in ST7789
		. y: y position window display in ST7789
		. w: width window display in ST7789
		. h: height window display in ST7789
	+ PARA OUT: None
------------------------------------------------------------------------------------------------*/

void ST7789_SET_WINDOW(ST7789_Typedef *ST7789,int16_t x, int16_t y, uint16_t w, uint16_t h)
{
	if(x >= ST7789->width || y >= ST7789->height) return;
	
	if(x + w >= ST7789->width)  w = ST7789->width - x;
  if(y + h >= ST7789->height) h = ST7789->height - y;

	
  uint8_t data[4];

  x += ST7789_OFFSET_X;
  y += ST7789_OFFSET_Y;

  ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_COL_ADDR_SET); // Set address column 
	
	// Start column address 
  data[0] = x >> 8;
  data[1] = x;
	
	// End column address 
  data[2] = (x+w-1) >> 8;
  data[3] = (x+w-1);
  ST7789_WRITE_DATA(ST7789, data, 4);

  ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_ROW_ADDR_SET); // Set address row 
	
	// Start row address 
  data[0] = y >> 8;
  data[1] = y;
	
	// End row address 
  data[2] = (y+h-1) >> 8;
  data[3] = (y+h-1);
  ST7789_WRITE_DATA(ST7789, data, 4);

  ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_MEM_WR); // Write memory ram 
}

/*------------------------------------------------------------------------------------------------
	+ Function: ST7789_SET_PX
	+ Description: Set pixel display on ST7789.
	+ PARA IN: 
		. *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
		. x: x position pixel display in ST7789
		. y: y position pixel display in ST7789
		. color : color pixel display in ST7789
	+ PARA OUT: None
------------------------------------------------------------------------------------------------*/

void ST7789_SET_PX(void *ctx,int16_t x, int16_t y, uint32_t color)
{
	
	ST7789_Typedef *ST7789=(ST7789_Typedef *)ctx;
	
	if(x >= ST7789->width || y >= ST7789->height) return;

	uint8_t r=(color>>16)>>(8-ST7789_R_MASK);
	uint8_t g=(color>>8)>>(8-ST7789_G_MASK);
	uint8_t b=(color>>0)>>(8-ST7789_B_MASK);
	
	uint8_t data[4];
	
	uint16_t w=1;
	uint16_t h=1;
	
	ST7789_SET_WINDOW(ST7789,x,y,w,h);
	
	#if defined(ST7789_INTERFACE_RGB565)
    uint16_t out_color = (r << 11) | (g << 5) | b;
		data[0] = out_color >> 8;
		data[1] = out_color;
	#elif defined(ST7789_INTERFACE_RGB666)
    uint32_t out_color = (r << 12) | (g << 6) | b;
		data[0] = out_color >> 16;
		data[1] = out_color >> 8;
		data[2] = out_color;
	#endif

  ST7789_WRITE_DATA(ST7789, data, 2);
}

static inline uint16_t RGB888_to_RGB565(uint32_t c)
{
  uint8_t r = (c >> 16) & 0xFF;
  uint8_t g = (c >> 8)  & 0xFF;
  uint8_t b =  c        & 0xFF;

  return ((uint16_t)(r & 0xF8) << 8) |((uint16_t)(g & 0xFC) << 3) |((uint16_t)b >> 3);
}

void ST7789_BLIT_COLOR(void *ctx,int16_t dst_x, int16_t dst_y, int16_t src_x, int16_t src_y , uint16_t w, uint16_t h,const uint8_t *data, uint16_t bytes_per_line)
{
	
	if(!ctx || !data) return;
	
	if(w<=0 || h<=0) return;
	
	ST7789_Typedef *ST7789=(ST7789_Typedef *)ctx;
	
	if(dst_x >= ST7789->width || dst_y >= ST7789->height)  return;
	
	if(dst_x + w > ST7789->width)  w = ST7789->width - dst_x;
  if(dst_y + h > ST7789->height) h = ST7789->height - dst_y;
	
	ST7789_SET_WINDOW(ST7789,dst_x,dst_y,w,h);
	
	#if ST7789_USING_SPI_DMA
	ST7789_WRITE_DATA_DMA(ST7789,data,w*h);
	
	#else
	for(int fy = 0; fy < h; fy++)
  {
      const uint8_t *row =data +((fy + src_y) *bytes_per_line) +(src_x * 2);

      ST7789_WRITE_DATA(ST7789,row, w*2);
  }
	#endif
}

void ST7789_BLIT_MONO(void* ctx,int16_t dst_x, int16_t dst_y, int16_t src_x, int16_t src_y ,uint16_t w, uint16_t h,const uint8_t *bitmap,uint16_t bytes_per_line,uint32_t color, uint32_t backColor)
{
  if (!ctx || !bitmap) return;
	
	if(w<=0 || h<=0) return;
	
  ST7789_Typedef *ST7789 = (ST7789_Typedef *)ctx;
	
	if(dst_x >= ST7789->width || dst_y >= ST7789->height)  return;
	
	if(dst_x + w > ST7789->width)  w = ST7789->width - dst_x;
  if(dst_y + h > ST7789->height) h = ST7789->height - dst_y;
	
  ST7789_SET_WINDOW(ST7789, dst_x, dst_y, w, h);
	
	uint16_t color16 = RGB888_to_RGB565(color);
  uint16_t backColor16    = RGB888_to_RGB565(backColor);
	
	uint16_t color_swapped = (color16 >> 8) | (color16 << 8);
	uint16_t backColor_swapped    = (backColor16 >> 8) | (backColor16 << 8);
	
	

	#if ST7789_USING_SPI_DMA
	
	#else
	for (int fy = 0; fy < h; fy++)
	{
		const uint8_t *row = bitmap + (fy+src_y) * bytes_per_line;
		
		for (int fx = 0; fx < w; fx++)
		{
			int sx = fx + src_x;
			uint8_t byte = row[sx >> 3];
			uint8_t bit  = (byte >> (7 - (sx & 7))) & 1;
		
//			line_buf[fx] = bit ? color16 : backColor16;
			line_buf[fx] = bit ? color_swapped : backColor_swapped;
		}
		
		ST7789_WRITE_DATA(ST7789, (uint8_t*)line_buf, w * 2);
	}
	#endif
}

/*------------------------------------------------------------------------------------------------
	+ Function: ST7789_CLEAR
	+ Description: clear display for ST7789.
	+ PARA IN: 
		 *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
	+ PARA OUT: None
------------------------------------------------------------------------------------------------*/

void ST7789_CLEAR(void *ctx, uint32_t backColor)
{
	ST7789_Typedef *ST7789=(ST7789_Typedef *)ctx;
	
	uint16_t backColor16=RGB888_to_RGB565(backColor);
	
	uint16_t color =(backColor16 >> 8) | (backColor16 << 8);
	
	for (int i = 0; i < ST7789->width; i++)
	{
		 line_buf[i] = color;
	}
	
       
	ST7789_SET_WINDOW(ST7789,0,0,ST7789->width,ST7789->height);
	
	for(int16_t y=0;y<ST7789->height;y++)
	{
		ST7789_WRITE_DATA(ST7789,(uint8_t*)line_buf,ST7789->width*2);
	}
}

void ST7789_CLEAR_WINDOW(void *ctx,int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t backColor)
{
	if (!ctx) return;
	
	ST7789_Typedef *ST7789=(ST7789_Typedef *) ctx;
	
	if(x >= ST7789->width || y >= ST7789->height)  return;
	
	if(x + w > ST7789->width)  w = ST7789->width - x;
  if(y + h > ST7789->height) h = ST7789->height - y;
	
	if(x>=ST7789->width || y>=ST7789->height || (x+w)<=0 || (y+h)<=0) return;
	
	// Clip left
	if(x<0)
	{
		w+=x;
		x=0;
	}
	
	// Clip top
	if(y<0)
	{
		h+=y;
		y=0;
	}
	
	// Clip right
	if((x+w)>ST7789->width)
	{
		w=ST7789->width-x;
	}
	
	// Clip bottom
	if((y+h)>ST7789->height)
	{
		h=ST7789->height-y;
	}
	
	uint16_t backColor16=RGB888_to_RGB565(backColor);
	uint16_t color =(backColor16 >> 8) | (backColor16 << 8);
//	static uint16_t line_buf[ST7789_DISPLAY_WIDTH*2];
	
	for (int i = 0; i < w; i++)
	{
		 line_buf[i] = color;
	}
	
	
	ST7789_SET_WINDOW(ST7789,x,y,w,h);
	for(int y=0;y<h;y++)
	{
		ST7789_WRITE_DATA(ST7789,(uint8_t*)line_buf,w*2);
	}
}

void ST7789_UPDATE(void *ctx)
{
	// empty function
}
