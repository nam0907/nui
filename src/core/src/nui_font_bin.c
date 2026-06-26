#include "../inc/nui_font_bin.h"
#include "../../int/nui_font_bin_int.h"
#include "../inc/nui_binary_reader.h"

#if NUI_FONT_USE_STREAM
uint8_t static glyphBuf[NUI_GLYPH_BUFF_MAX_SIZE]={0};


//uint32_t indexGlyphCur = 0;
//uint32_t sizeGlyph=0;

bool NUI_FONT_BIN_GET_GLYPH(const Nui_Font_Typedef *font,uint32_t unicode ,Nui_Glyph_Typedef *glyph)
{
	if(!font->data) return false;
	Nui_Font_Bin_Typedef *fontBin=(Nui_Font_Bin_Typedef *) font->data;
	
	int left=0;
	int right=fontBin->numChar-1;
	
	while(left<=right)
	{
		int mid=(left+right)>>1;
		
		// Kiem tra ki tu user dung co trong font khong
		uint32_t offsetRef = fontBin->refOffset+mid*NUI_FONT_BIN_REF_OFFSET_SIZE;
		uint32_t unicodeTmp=0;
		
		if(offsetRef >= fontBin->fileSize || offsetRef+NUI_FONT_BIN_REF_OFFSET_SIZE > fontBin->fileSize) return false; 		 // Kiem tra xem offset map co vuot qua size file .bin khong
		if(!fontBin->stream->read(fontBin->stream->userData,offsetRef,glyphBuf,NUI_FONT_BIN_REF_OFFSET_SIZE)) return false;
		unicodeTmp=NUI_BINARY_READER_UINT32(glyphBuf);
	
		if(unicodeTmp==unicode)
		{
			uint32_t offsetMap = fontBin->mapOffset+mid*NUI_FONT_BIN_REF_OFFSET_SIZE;
			uint32_t indexGlyphCur = 0;
			uint32_t sizeGlyph=0;
			
			if(offsetMap >= fontBin->fileSize || offsetMap+NUI_FONT_BIN_MAP_OFFSET_SIZE > fontBin->fileSize) return false; // Kiem tra xem offset map co vuot qua size file .bin khong		
			
			if(mid==fontBin->numChar-1)
			{
				if(!fontBin->stream->read(fontBin->stream->userData,offsetMap,glyphBuf,NUI_FONT_BIN_MAP_OFFSET_SIZE)) return false;// Lay offset cua data font trong file .bin
				indexGlyphCur=NUI_BINARY_READER_UINT32(glyphBuf);
				
				if(indexGlyphCur >= fontBin->fileSize) return false;
				sizeGlyph=fontBin->fileSize-fontBin->dataOffset-indexGlyphCur+4;
			}
			else
			{
				uint32_t indexGlyphNext = 0;
				
				if(offsetMap+NUI_FONT_BIN_MAP_OFFSET_SIZE*2 > fontBin->fileSize) return false;
				
				if(!fontBin->stream->read(fontBin->stream->userData,offsetMap,glyphBuf,NUI_FONT_BIN_MAP_OFFSET_SIZE*2)) return false;// Lay offset cua data font trong file .bin
				
				indexGlyphCur=NUI_BINARY_READER_UINT32(&glyphBuf[0]);				
				indexGlyphNext=NUI_BINARY_READER_UINT32(&glyphBuf[4]);
				
				if(indexGlyphCur>indexGlyphNext) return false;
				
				sizeGlyph=indexGlyphNext-indexGlyphCur;
			}
			
			if(indexGlyphCur > fontBin->fileSize - sizeGlyph) return false;
			if(sizeGlyph > sizeof(glyphBuf)) return false;
			if(indexGlyphCur >= fontBin->fileSize || indexGlyphCur+sizeGlyph>fontBin->fileSize) return false;
			
			if(!fontBin->stream->read(fontBin->stream->userData,indexGlyphCur+fontBin->dataOffset-4,glyphBuf,sizeGlyph)) return false;// Lay data font trong file .bin

			glyph->bitmap = &glyphBuf[4];
			glyph->w = glyphBuf[0];// Chieu rong cua chu
			glyph->h = glyphBuf[1];// Chieu cao cua chu
			glyph->bytePerRow = glyphBuf[2]; // so byte tren 1 hang
			glyph->offset = glyphBuf[3]; // Do lech cua chu so voi baseline 

			return true;
			
		}
	
		if(unicodeTmp<unicode) left=mid+1;
		else right=mid-1;
	}
	
	return false;
}
#endif
