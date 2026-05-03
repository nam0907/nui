#ifndef __ST7789_H__
#define __ST7789_H__

#include "main.h" 
#include "stdbool.h"
#include "string.h"
//#include "UI_Config.h"

//#define ST7789_CMD						0
//#define ST7789_DATA						1

#define ST7789_DISPLAY_WIDTH		240
#define ST7789_DISPLAY_HEIGHT		320

#define ST7789_INTERFACE_RGB565     // use for RGB565 
//#define ST7789_INTERFACE_RGB666	// use for RGB666

#if defined(ST7789_INTERFACE_RGB565)
	#define ST7789_R_MASK																5
	#define ST7789_G_MASK																6
	#define ST7789_B_MASK																5
	#define ST7789_INTERFACE_COLOR											0x55
#elif defined(ST7789_INTERFACE_RGB666)
	#define ST7789_R_MASK																6
	#define ST7789_G_MASK																6
	#define ST7789_B_MASK																6
	#define ST7789_INTERFACE_COLOR											0x66
#else
	#error "Please define ST7789 interface mode"
#endif

#define ST7789_MAX_BYTE_SEND				1024

#define ST7789_OFFSET_X							0
#define ST7789_OFFSET_Y							0

#define ST7789_CMD_NOP															0x00
#define ST7789_CMD_RST															0x01
#define ST7789_CMD_READ_DISPLAY_ID									0x04
#define ST7789_CMD_READ_DISPLAY_STT									0x09
#define ST7789_CMD_READ_DISPLAY_PW_MODE							0x0A
#define ST7789_CMD_READ_DISPLAY_PX_FORMAT						0x0C
#define ST7789_CMD_READ_DISPLAY_IMAGE_MODE					0x0D
#define ST7789_CMD_READ_DISPLAY_SIGNAL_MODE					0x0E
#define ST7789_CMD_SLEEP_IN													0x10
#define ST7789_CMD_SLEEP_OUT												0x11
#define ST7789_CMD_PARTIAL_MODE_ON									0x12
#define ST7789_CMD_NORMAL_MODE_ON										0x13
#define ST7789_CMD_INVERSION_OFF										0x20
#define ST7789_CMD_INVERSION_ON											0x21
#define ST7789_CMD_GAMMA_SET												0x26
#define ST7789_CMD_DISPLAY_OFF											0x28
#define ST7789_CMD_DISPLAY_ON												0x29
#define ST7789_CMD_COL_ADDR_SET											0x2A
#define ST7789_CMD_ROW_ADDR_SET											0x2B
#define ST7789_CMD_MEM_WR														0x2C
#define ST7789_CMD_VER_SCROLL_DEF										0x33
#define ST7789_CMD_MEM_ACCSESS_CTRL									0x36
#define ST7789_CMD_VER_SCROLL_START									0x37
#define ST7789_CMD_IDLE_OFF													0x38
#define ST7789_CMD_INTERFACE_PX_FORMAT							0x3A
#define ST7789_CMD_WR_MEM_CONTINUE									0x3C
#define ST7789_CMD_SET_BRIGHTNESS										0x51
#define ST7789_CMD_WR_CTRL_DISPLAY									0x53
#define ST7789_CMD_WR_CACE													0x55
#define ST7789_CMD_WR_CABC_MIN_BRIGHTNESS						0x5E

#define ST7789_ROTATION_0_DEGREE										0
#define ST7789_ROTATION_90_DEGREE										1
#define ST7789_ROTATION_180_DEGREE									2
#define ST7789_ROTATION_270_DEGREE									3


typedef struct
{
	uint16_t width,height;
	SPI_HandleTypeDef *SPI_Port;
	GPIO_TypeDef *CS_Port;
	uint16_t CS_PIN;
	GPIO_TypeDef *DC_Port;
	uint16_t DC_PIN;
}ST7789_Typedef;

void ST7789_ROTATION(ST7789_Typedef *ST7789, uint8_t rotate);
void ST7789_INIT(ST7789_Typedef *ST7789, SPI_HandleTypeDef *SPI_Port);
void ST7789_SET_WINDOW(ST7789_Typedef *ST7789,int16_t x, int16_t y, int16_t w, int16_t h);
void ST7789_CLEAR(void *ctx, uint32_t bg);
void ST7789_SET_PX(void *ctx,int16_t x, int16_t y, uint32_t color);
void ST7789_CLEAR_WINDOW(void *ctx,int16_t x, int16_t y, int16_t w, int16_t h, uint32_t bg);
void ST7789_BLIT_COLOR(void *ctx,int16_t x, int16_t y, int16_t w, int16_t h,const uint8_t *data);
void ST7789_BLIT_MONO(void* ctx,int16_t x, int16_t y,int16_t w, int16_t h,const uint8_t *bitmap,uint16_t bytes_per_line,uint32_t color, uint32_t bg);

#endif
