#ifndef __NUI_IMAGE_H__
#define __NUI_IMAGE_H__

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

#include "stdint.h"

#define RGB565_RMASK		(uint8_t)0x1F
#define RGB565_GMASK		(uint8_t)0x3F
#define RGB565_BMASK		(uint8_t)0x1F

typedef enum
{
	FORMAT_RGB565=0,
	FORMAT_RGB888=1,
	FORMAT_MONO1BIT=2,
}ImageFormat_Typedef;


typedef struct
{
  const uint8_t *Data;
  ImageFormat_Typedef Format;
	uint16_t Width;
  uint16_t Height;
}Image_Typedef;

typedef struct
{
	uint16_t PosX;
	uint16_t PosY;
	Image_Typedef Img;
}ImageGraphic_Typedef;

uint16_t NUI_IMAGE_GET_WIDTH(Image_Typedef image);
uint16_t NUI_IMAGE_GET_HEIGHT(Image_Typedef image);
void NUI_IMAGE_DRAW_IMAGE(void *ctx, int16_t x, int16_t y ,Image_Typedef image);
void NUI_IMAGE_DRAW_ImgGraphic(void *ctx,ImageGraphic_Typedef imgG);

#ifdef __cplusplus // Compatible with C++
}
#endif


#endif
