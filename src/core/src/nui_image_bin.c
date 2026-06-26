#include "../inc/nui_image_bin.h"
#include "../../int/nui_image_bin_int.h"

#if NUI_IMAGE_USE_STREAM
//uint32_t offsetData=0;
//uint32_t Size=0;
bool NUI_IMAGE_BIN_GET_LINE(const Nui_Image_Typedef *img, uint16_t lineSize ,uint16_t line, uint16_t numLine, uint8_t * buff)
{
	if(!img->data) return false;
	Nui_Image_Bin_Typedef *imgBin=(Nui_Image_Bin_Typedef *) img->data;
	uint32_t offsetData = NUI_IMAGE_BIN_DATA_OFFSET_POS+line*lineSize;
//	uint32_t Size = numLine*lineSize;
	
	if(!imgBin->stream->read(imgBin->stream->userData,offsetData,buff,numLine*lineSize)) return false;
	
	return true;
}

#endif
