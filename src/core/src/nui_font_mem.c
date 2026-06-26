#include "../inc/nui_font_mem.h"

bool NUI_FONT_MEM_GET_GLYPH(const Nui_Font_Typedef *font,uint32_t unicode ,Nui_Glyph_Typedef *glyph)
{
	if(!font->data) return false;
	Nui_Font_Mem_Typedef *fontMem=(Nui_Font_Mem_Typedef *) font->data;
	
	int left=0;
	int right=fontMem->numChar-1;
	
	while(left<=right)
	{
		int mid=(left+right)>>1;
	
		if(fontMem->Font_Ref[mid]==unicode)
		{
			uint32_t indexGlyph = fontMem->Font_Map[mid];

			glyph->bitmap = &fontMem->Font[indexGlyph];
			glyph->w = fontMem->Font[indexGlyph - 4];// Chieu rong cua chu
			glyph->h = fontMem->Font[indexGlyph - 3];// Chieu cao cua chu
			glyph->bytePerRow = fontMem->Font[indexGlyph - 2]; // so byte tren 1 hang
			glyph->offset = fontMem->Font[indexGlyph - 1]; // Do lech cua chu so voi baseline 

			return true;
			
		}
	
		if(fontMem->Font_Ref[mid]<unicode) left=mid+1;
		else right=mid-1;
	}
	
	return false;
}

//Nui_Font_Typedef NUI_FONT_MEM_INIT(const Nui_Font_Mem_Typedef *fontMem)
//{
//	Nui_Font_Typedef font=
//	{
//		.gap=fontMem->gap,
//		.get_glyph=NUI_FONT_MEM_GET_GLYPH,
//		.data=fontMem,
//	};
//	
//	return font;
//}

void NUI_FONT_MEM_INIT(Nui_Font_Typedef *font,const Nui_Font_Mem_Typedef *fontMem)
{
		font->gap=fontMem->gap;
		font->get_glyph=NUI_FONT_MEM_GET_GLYPH;
		font->data=fontMem;
}

