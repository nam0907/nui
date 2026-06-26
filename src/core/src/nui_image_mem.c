#include "../inc/nui_image_mem.h"

const uint8_t *NUI_IMAGE_MEM_GET_BITMAP(const Nui_Image_Typedef *image)
{
	if(!image->data) return NULL;
	
	Nui_Image_Mem_Typedef *imageMem=(Nui_Image_Mem_Typedef *) image->data;
	
	return imageMem->bitmap;
}

void NUI_IMAGE_MEM_INIT(Nui_Image_Typedef *image, Nui_Image_Mem_Typedef *imagetMem)
{
	image->w=imagetMem->w;
	image->h=imagetMem->h;
	image->data=imagetMem;
	image->format=imagetMem->format;
	image->get_bitmap=NUI_IMAGE_MEM_GET_BITMAP;
	image->get_line=NULL;
}

