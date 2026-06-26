#include "../inc/nui_image_sd.h"
#include "../../int/nui_sd_int.h"
#include "../../int/nui_image_bin_int.h"
#include "../inc/nui_binary_reader.h"

#if NUI_IMAGE_USE_SD
void NUI_IMAGE_GET_INF(Nui_Image_Bin_Typedef *img, const uint8_t *buffHeader, uint16_t *width, uint16_t *height, ImageFormat_Typedef *format)
{
	uint8_t index=0;
	
	img->version=NUI_BINARY_READER_UINT16(&buffHeader[index]);
	index+=2;
	img->fileSize=NUI_BINARY_READER_UINT32(&buffHeader[index]);
	index+=4;
	switch(buffHeader[index])
	{
		case 0:
		{
			*format=NUI_IMAGE_FORMAT_RGB565;
			break;
		}
		case 1:
		{
			*format=NUI_IMAGE_FORMAT_RGB888;
			break;
		}
		case 2:
		{
			*format=NUI_IMAGE_FORMAT_MONO1BIT;
			break;
		}
	}
	
	index+=1;
	*width=NUI_BINARY_READER_UINT16(&buffHeader[index]);
	index+=2;
	*height=NUI_BINARY_READER_UINT16(&buffHeader[index]);
	index+=2;
}

bool NUI_IMAGE_SD_INIT(Nui_Image_Typedef *img, Nui_Image_SD_Typedef *imgSD, const uint8_t *pathFile)
{
	UINT br;
	
	uint8_t buffHeader[NUI_IMAGE_HEADER_SIZE]={0};
	
	if(!NUI_SD_INIT(&imgSD->sd,pathFile)) return false;
	
	if(f_lseek(&imgSD->sd.file, 0) != FR_OK)
        return false;
	
	if(f_read(&imgSD->sd.file,buffHeader,NUI_IMAGE_HEADER_SIZE,&br) != FR_OK ) return false;
	
	if(buffHeader[0]!='N' || buffHeader[1]!='U' || buffHeader[2]!='I') return false;
	
	if(buffHeader[3]!=NUI_IMAGE_BIN_TYPE) return false;
	
	NUI_IMAGE_GET_INF(&imgSD->img,&buffHeader[4],&img->w,&img->h, &img->format);
	
	imgSD->img.stream=&imgSD->sd.stream;
	
	img->get_line=NUI_IMAGE_BIN_GET_LINE;
	img->get_bitmap=NULL;
	img->data=&imgSD->img;	
	
	return true;
}

#endif
