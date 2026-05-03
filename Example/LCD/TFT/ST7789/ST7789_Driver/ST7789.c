
#include "ST7789.h"

static uint16_t line_buf[ST7789_DISPLAY_WIDTH*2];

/*------------------------------------------------------------------------------------------------
	+ Function: ST7789_REGISTER_CS_PIN
	+ Description: Register chip select(CS) pin for ST7789.
	+ PARA IN: 
		. *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
		. *CS_Port: Pointer to GPIO_TypeDef.
		. CS_PIN:  Chip select(CS) pin.  
	+ PARA OUT: None
------------------------------------------------------------------------------------------------*/

void ST7789_REGISTER_CS_PIN(ST7789_Typedef *ST7789, GPIO_TypeDef *CS_Port, uint16_t CS_PIN)
{
	ST7789->CS_Port=CS_Port;
	ST7789->CS_PIN=CS_PIN;
}

/*------------------------------------------------------------------------------------------------
	+ Function: ST7789_REGISTER_DC_PIN
	+ Description: Register data/command(DC) pin for ST7789.
	+ PARA IN: 
		. *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
		. *DC_Port: Pointer to GPIO_TypeDef.
		. DC_PIN:  data/command(DC) pin.  
	+ PARA OUT: None
------------------------------------------------------------------------------------------------*/

void ST7789_REGISTER_DC_PIN(ST7789_Typedef *ST7789, GPIO_TypeDef *DC_Port, uint16_t DC_PIN)
{
	ST7789->DC_Port=DC_Port;
	ST7789->DC_PIN=DC_PIN;
}

void ST7789_SEND_SPI(ST7789_Typedef *ST7789,const uint8_t *data, uint16_t len)
{
	HAL_GPIO_WritePin(ST7789->CS_Port,ST7789->CS_PIN,GPIO_PIN_RESET); // CS low to select chip
//	HAL_SPI_Transmit_DMA(ST7789->SPI_Port,data,len);
	HAL_SPI_Transmit(ST7789->SPI_Port,data,len,100);
	HAL_GPIO_WritePin(ST7789->CS_Port,ST7789->CS_PIN,GPIO_PIN_SET); // CS high to ignore SCK
}

void ST7789_WRITE_COMMAND(ST7789_Typedef *ST7789, uint8_t cmd)
{
	HAL_GPIO_WritePin(ST7789->DC_Port,ST7789->DC_PIN,GPIO_PIN_RESET); // DC low to send Command
	ST7789_SEND_SPI(ST7789,&cmd,1);
	HAL_GPIO_WritePin(ST7789->DC_Port,ST7789->DC_PIN,GPIO_PIN_SET); // DC high to send data
}

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

/*------------------------------------------------------------------------------------------------
	+ Function: ST7789_ROTATION
	+ Description: Set display inversion mode for ST7789.
	+ PARA IN: 
		. *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
		. rotate:  Rotation display for ST7789. This parameter can be one of this value: 
				 ST7789_ROTATION_0_DEGREE
				 ST7789_ROTATION_90_DEGREE
         ST7789_ROTATION_180_DEGREE:
				 ST7789_ROTATION_270_DEGREE:
	+ PARA OUT: None
------------------------------------------------------------------------------------------------*/

void ST7789_ROTATION(ST7789_Typedef *ST7789, uint8_t rotate)
{
	uint8_t buff=0;
	switch(rotate)
	{
		case ST7789_ROTATION_0_DEGREE:
		{
			buff=0x00;
			ST7789->width=ST7789_DISPLAY_WIDTH;
			ST7789->height=ST7789_DISPLAY_HEIGHT;
			break;
		}			
		case ST7789_ROTATION_90_DEGREE:
		{
			buff=0x60;
			ST7789->width=ST7789_DISPLAY_HEIGHT;
			ST7789->height=ST7789_DISPLAY_WIDTH;
			break;
		}
		case ST7789_ROTATION_180_DEGREE:
		{
			buff=0xC0;
			ST7789->width=ST7789_DISPLAY_WIDTH;
			ST7789->height=ST7789_DISPLAY_HEIGHT;
			break;
		}
		case ST7789_ROTATION_270_DEGREE:
		{
			buff=0xA0;
			ST7789->width=ST7789_DISPLAY_HEIGHT;
			ST7789->height=ST7789_DISPLAY_WIDTH;
			break;
		}
	}
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_MEM_ACCSESS_CTRL); //  Memory Data Access Control (36h)
	ST7789_WRITE_DATA(ST7789,&buff,1);
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
	HAL_Delay(120); 
	
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_SLEEP_OUT); // Sleep out mode (11h)
	HAL_Delay(120);
	
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_NORMAL_MODE_ON); // Normal Display Mode On (13h)
	
	ST7789_ROTATION(ST7789, ST7789_ROTATION_90_DEGREE);
	
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_INVERSION_ON); // Normal Display Mode On (13h)
	
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_INTERFACE_PX_FORMAT); //  Interface Pixel Format (3Ah)
	buff[0]=ST7789_INTERFACE_COLOR; //Control interface color format
	ST7789_WRITE_DATA(ST7789,buff,1);
	
	ST7789_WRITE_COMMAND(ST7789, ST7789_CMD_SET_BRIGHTNESS); //  Memory Data Access Control (51h)
	buff[0]=0x0F;
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

void ST7789_INIT(ST7789_Typedef *ST7789, SPI_HandleTypeDef *SPI_Port)
{
	
	
	ST7789->SPI_Port=SPI_Port;
	
	ST7789->CS_Port=GPIOB;
	ST7789->CS_PIN=GPIO_PIN_12;
	ST7789->DC_Port=GPIOB;
	ST7789->DC_PIN=GPIO_PIN_14;
//	
//	HAL_SPI_Abort(ST7789->SPI_Port);
//	HAL_SPI_DeInit(ST7789->SPI_Port);
//	
//	ST7789->SPI_Port->Init.Mode = SPI_MODE_MASTER;
//  ST7789->SPI_Port->Init.Direction = SPI_DIRECTION_2LINES;
//  ST7789->SPI_Port->Init.DataSize = SPI_DATASIZE_8BIT;
//  ST7789->SPI_Port->Init.CLKPolarity = SPI_POLARITY_LOW;
//  ST7789->SPI_Port->Init.CLKPhase = SPI_PHASE_1EDGE;
//  ST7789->SPI_Port->Init.NSS = SPI_NSS_SOFT;
//  ST7789->SPI_Port->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
//  ST7789->SPI_Port->Init.FirstBit = SPI_FIRSTBIT_MSB;
//  ST7789->SPI_Port->Init.TIMode = SPI_TIMODE_DISABLE;
//  ST7789->SPI_Port->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//  ST7789->SPI_Port->Init.CRCPolynomial = 10;
//	
//	HAL_SPI_Init(ST7789->SPI_Port);
	
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

void ST7789_SET_WINDOW(ST7789_Typedef *ST7789,int16_t x, int16_t y, int16_t w, int16_t h)
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
	
	ST7789_SET_WINDOW(ST7789,x,y,1,1);
	
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

void ST7789_BLIT_COLOR(void *ctx,int16_t x, int16_t y, int16_t w, int16_t h,const uint8_t *data)
{
	
	if(!ctx || !data) return;
	
	ST7789_Typedef *ST7789=(ST7789_Typedef *)ctx;
	
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
	
	ST7789_SET_WINDOW(ST7789,x,y,w,h);
	ST7789_WRITE_DATA(ST7789,data,w*h*2);
}

void ST7789_BLIT_MONO(void* ctx,int16_t x, int16_t y,int16_t w, int16_t h,const uint8_t *bitmap,uint16_t bytes_per_line,uint32_t color, uint32_t bg)
{
  if (!ctx || !bitmap) return;
	
  ST7789_Typedef *ST7789 = (ST7789_Typedef *)ctx;
	
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
	

  ST7789_SET_WINDOW(ST7789, x, y, w, h);
	
	uint16_t color16 = RGB888_to_RGB565(color);
  uint16_t bg16    = RGB888_to_RGB565(bg);
	
	uint16_t color_swapped = (color16 >> 8) | (color16 << 8);
	uint16_t bg_swapped    = (bg16 >> 8) | (bg16 << 8);

	for (int fy = 0; fy < h; fy++)
	{
		const uint8_t *row = bitmap + fy * bytes_per_line;
		
		for (int fx = 0; fx < w; fx++)
		{
			uint8_t byte = row[fx >> 3];
			uint8_t bit  = (byte >> (7 - (fx & 7))) & 1;
		
//			line_buf[fx] = bit ? color16 : bg16;
			line_buf[fx] = bit ? color_swapped : bg_swapped;
		}
		
		ST7789_WRITE_DATA(ST7789, (uint8_t*)line_buf, w * 2);
	}
}

/*------------------------------------------------------------------------------------------------
	+ Function: ST7789_CLEAR
	+ Description: clear display for ST7789.
	+ PARA IN: 
		 *ST7789: Pointer to ST7789_Typedef structure config for ST7789 module.
	+ PARA OUT: None
------------------------------------------------------------------------------------------------*/

void ST7789_CLEAR(void *ctx, uint32_t bg)
{
	ST7789_Typedef *ST7789=(ST7789_Typedef *)ctx;
	
	uint16_t bg16=RGB888_to_RGB565(bg);
	
	uint16_t color =(bg16 >> 8) | (bg16 << 8);
	
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

void ST7789_CLEAR_WINDOW(void *ctx,int16_t x, int16_t y, int16_t w, int16_t h, uint32_t bg)
{
	if (!ctx) return;
	
	ST7789_Typedef *ST7789=(ST7789_Typedef *) ctx;
	
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
	
	uint16_t bg16=RGB888_to_RGB565(bg);
	uint16_t color =(bg16 >> 8) | (bg16 << 8);
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
