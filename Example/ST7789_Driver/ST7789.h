#ifndef __ST7789_H__
#define __ST7789_H__

#include "stdbool.h"
#include "string.h"
#include "stdint.h"

#define ST7789_USING_SPI_DMA		0

#define ST7789_DISPLAY_WIDTH		240
#define ST7789_DISPLAY_HEIGHT		320

#define ST7789_DISPLAY_WIDTH_MAX		(ST7789_DISPLAY_WIDTH>ST7789_DISPLAY_HEIGHT ? ST7789_DISPLAY_WIDTH:ST7789_DISPLAY_HEIGHT)

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

#if ST7789_USING_SPI_DMA
#define ST7789_MAX_BYTE_SEND				4096
#else 
//#define ST7789_MAX_BYTE_SEND				1024
#define ST7789_MAX_BYTE_SEND				ST7789_DISPLAY_WIDTH_MAX*2
#endif

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

#define ST7789_ROTATION_0_DEGREE										0x00
#define ST7789_ROTATION_90_DEGREE										0xA0
#define ST7789_ROTATION_180_DEGREE									0xC0
#define ST7789_ROTATION_270_DEGREE									0x60

/* 
====================================== User define MADCTL bit =========================================
*/
#define ST7789_MADCTL_MY				1
#define ST7789_MADCTL_MX				1
#define ST7789_MADCTL_MV				1
#define ST7789_MADCTL_BGR				1
/* 
=======================================================================================================
*/
/* 
====================================== User define Inversion mode  =========================================
*/
#define ST7789_INVERSION_MODE		0
/* 
=======================================================================================================
*/
typedef struct
{
	uint8_t madctl;
	uint8_t invs;
}ST7789_CFG_Typedef;

//typedef enum
//{
//	ST7789_DMA_STATE_IDLE,
//	ST7789_DMA_STATE_SEND,
//	ST7789_DMA_STATE_WAIT,
//	ST7789_DMA_STATE_SUCCESS,
//	ST7789_DMA_STATE_ERROR,
//}ST7789_DMA_State_Typedef;

//typedef struct
//{
//	ST7789_DMA_State_Typedef state;
//	
//}ST7789_DMA_Queue_Typedef;

typedef struct 
{
	
//	volatile bool DmaBusy;
	uint32_t DmaRemain;
	uint16_t DmaChunk;
	const uint8_t *DmaPtr;
  uint8_t TransBuff;
}ST7789_DMA_Typedef;

typedef struct
{
	uint16_t width;
	uint16_t height;
	const uint8_t *SrcData;
	uint16_t SrcX;
  uint16_t SrcY;

  uint16_t BytesPerLine;

  uint16_t CurrentLine;
  uint16_t RemainLine;
}ST7789_Blit_Typedef;

typedef struct
{
	ST7789_Blit_Typedef blit;
	ST7789_DMA_Typedef dma;
	ST7789_CFG_Typedef cfg;
	uint16_t width;
	uint16_t height;
	void(*WriteDC)(uint8_t value);
	void(*WriteCS)(uint8_t value);
	void(*WriteReset)(uint8_t value);
	void(*SPITransmit)(const uint8_t *data, uint16_t len);
	void(*SPITransmitDma)(const uint8_t *data, uint16_t len);
	void(*Delay)(uint32_t len);
	
}ST7789_Typedef;

void ST7789_SET_INVERSION(ST7789_Typedef *ST7789, bool invs);
void ST7789_SET_MADCTL(ST7789_Typedef *ST7789, uint8_t madctl);
void ST7789_INIT(ST7789_Typedef *ST7789);
//void ST7789_SET_WINDOW(ST7789_Typedef *ST7789,int16_t x, int16_t y, uint16_t *w, uint16_t *h);
void ST7789_SET_WINDOW(ST7789_Typedef *ST7789,int16_t x, int16_t y, uint16_t w, uint16_t h);
//void ST7789_SET_WINDOW(ST7789_Typedef *ST7789,int16_t x, int16_t y, int16_t w, int16_t h);
void ST7789_CLEAR(void *ctx, uint32_t backColor);
void ST7789_SET_PX(void *ctx,int16_t x, int16_t y, uint32_t color);
void ST7789_CLEAR_WINDOW(void *ctx,int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t backColor);
void ST7789_BLIT_COLOR(void *ctx,int16_t dst_x, int16_t dst_y, int16_t src_x, int16_t src_y , uint16_t w, uint16_t h,const uint8_t *data, uint16_t bytes_per_line);
void ST7789_BLIT_MONO(void* ctx,int16_t dst_x, int16_t dst_y, int16_t src_x, int16_t src_y ,uint16_t w, uint16_t h,const uint8_t *bitmap,uint16_t bytes_per_line,uint32_t color, uint32_t backColor);

#endif
