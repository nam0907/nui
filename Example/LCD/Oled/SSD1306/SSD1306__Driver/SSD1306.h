
#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "main.h" 
#include "stdbool.h"
#include "string.h"

#define SSD1306_CMD				0
#define SSD1306_DATA			1

#define SSD1306_TIMEOUT										1000

#define SSD1306_CMD_SET_CONTRAST					0x81
#define SSD1306_CMD_ENTIRE_DISPLAY				0xA5
#define SSD1306_CMD_RAM_DISPLAY						0xA4
#define SSD1306_CMD_SET_MUX								0xA8
#define SSD1306_CMD_NORMAL_DISPLAY				0xA6
#define SSD1306_CMD_INVERSE_DISPLAY				0xA7
#define SSD1306_CMD_DISPLAY_OFF						0xAE
#define SSD1306_CMD_DISPLAY_ON						0xAF
#define SSD1306_CMD_DISPLAY_OFFSET				0xD3
#define SSD1306_CMD_SET_OSC								0xD5

#define SSD1306_SEGMENT_FORWARD						0
#define SSD1306_SEGMENT_REVERSE						1

#define SSD1306_LEN_RX 50
#define SSD1306_LEN_TX 50
#define SSD1306_MAX_BYTE_SEND						128

// Resolution of LCD
#define SSD1306_DISPLAY_WIDTH 									128
#define SSD1306_DISPLAY_HEIGHT 									64
#define SSD1306_PAGE										SSD1306_DISPLAY_HEIGHT/8
#define SSD1306_SIZE_BUFF								SSD1306_DISPLAY_WIDTH*SSD1306_PAGE


#define SSD1306_ROTATION_0_DEGREE										0
#define SSD1306_ROTATION_90_DEGREE									1
#define SSD1306_ROTATION_180_DEGREE									2
#define SSD1306_ROTATION_270_DEGREE									3

typedef struct
{
	I2C_HandleTypeDef *PORT;
	uint16_t deviceAddr;
	uint8_t dataRx[SSD1306_LEN_RX];
	uint8_t dataTx[SSD1306_LEN_TX];
	uint8_t BuffDisplay[SSD1306_SIZE_BUFF];
	uint8_t rotate;
	int16_t width;
	int16_t height;
}SSD1306_Typedef;


void SSD1306_WRITE_COMMAND(SSD1306_Typedef *SSD1306,uint8_t CMD);
void SSD1306_WRITE_BYTE(SSD1306_Typedef *SSD1306,uint8_t value);
HAL_StatusTypeDef SSD1306_INIT(SSD1306_Typedef *SSD1306,I2C_HandleTypeDef *hi2c,uint8_t SA0);
void SSD1306_SET_PX(void *ctx,int16_t x, int16_t y,uint32_t color);
void SSD1306_UPDATE(void *ctx);
void SSD1306_CLEAR(void *ctx, uint32_t bg);
void SSD1306_BLIT_MONO(void *ctx,int16_t x, int16_t y, int16_t w, int16_t h,const uint8_t *bitmap,uint16_t bytes_per_line,uint32_t color, uint32_t bg);
void SSD1306_ROTATION(SSD1306_Typedef *SSD1306,uint8_t rotate);
void SSD1306_CLEAR_WINDOW(void *ctx, int16_t x, int16_t y, int16_t w, int16_t h, uint32_t bg);

#endif
