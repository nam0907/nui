#include "../inc/nui_font_sd.h"
#include "../../int/nui_sd_int.h"
#include "../../int/nui_font_bin_int.h"
#include "../inc/nui_binary_reader.h"

#define NUI_FONT_PATH_MAX_SIZE					50
#define NUI_FONT_HEADER_SIZE						26

#if NUI_FONT_USE_SD

void NUI_FONT_GET_INF(Nui_Font_Bin_Typedef *font, const uint8_t *buffHeader, uint16_t *gap)
{
	uint8_t index=4;
	
	font->version=NUI_BINARY_READER_UINT16(&buffHeader[index]);
	index+=2;
	font->fileSize=NUI_BINARY_READER_UINT32(&buffHeader[index]);
	index+=4;
	font->numChar=NUI_BINARY_READER_UINT16(&buffHeader[index]);
	index+=2;
	*gap=NUI_BINARY_READER_UINT16(&buffHeader[index]);
	index+=2;
	font->refOffset=NUI_BINARY_READER_UINT32(&buffHeader[index]);
	index+=4;
	font->mapOffset=NUI_BINARY_READER_UINT32(&buffHeader[index]);
	index+=4;
	font->dataOffset=NUI_BINARY_READER_UINT32(&buffHeader[index]);
	index+=4;
}

bool NUI_FONT_SD_INIT(Nui_Font_Typedef *font, Nui_Font_SD_Typedef *fontSd, const uint8_t *pathFile)
{
	UINT br;
	
	uint8_t buffHeader[NUI_FONT_HEADER_SIZE]={0};
	
	if(!NUI_SD_INIT(&fontSd->sd,pathFile)) return false;
	
	if(f_lseek(&fontSd->sd.file, 0) != FR_OK)
        return false;
	
	if(f_read(&fontSd->sd.file,buffHeader,NUI_FONT_HEADER_SIZE,&br) != FR_OK ) return false;
	
	if(buffHeader[0]!='N' || buffHeader[1]!='U' || buffHeader[2]!='I') return false;
	
	if(buffHeader[3]!=NUI_FONT_BIN_TYPE) return false;
	
	NUI_FONT_GET_INF(&fontSd->font,buffHeader,&font->gap);
	
	fontSd->font.stream=&fontSd->sd.stream;
	
//	font->gap=fontSd->font.gap;
	font->get_glyph=NUI_FONT_BIN_GET_GLYPH;
	font->data=&fontSd->font;
	
	return true;
}

#endif
