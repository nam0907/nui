#include "../inc/nui_align_txt.h"
#include "../../int/nui_font_def_int.h"

#if NUI_WDG_USE_TXT_GRAPH

Nui_Rect_Typedef NUI_ALIGN_RECT_SYMETRY_X(Nui_Rect_Typedef rect, uint16_t width) // Lay toa do doi xung theo truc x
{
	Nui_Rect_Typedef rectTmp;
	int16_t end_x=width-rect.x;
	uint16_t space=0;
	space=end_x-rect.w*2-rect.x+1;
	
	rectTmp.x=rect.x+space+rect.w;
	rectTmp.y=rect.y;
	rectTmp.w=rect.w;
	rectTmp.h=rect.h;
	
	return rectTmp;
}

Nui_Rect_Typedef NUI_ALIGN_RECT_SPLIT_X(Nui_Rect_Typedef rectParent, uint8_t numRect, uint8_t index, uint8_t gap) // Lay toa do doi xung theo truc x
{
	Nui_Rect_Typedef rectTmp;
	uint16_t total_gap=gap*(numRect-1);
	uint16_t usable = rectParent.w-total_gap; // Phan duoc su dung trong rect
	uint16_t RectChildW=usable/numRect;
	uint16_t rem=usable%numRect; // Phan du ra trong rect
	
	int16_t x=rectParent.x;
	
	rectTmp.x=x+(RectChildW+gap)*index;
	rectTmp.y=rectParent.y;
	rectTmp.w=RectChildW;
	rectTmp.h=rectParent.h;
	
	if(index==numRect-1)
	{
		rectTmp.w+=rem; // neu rect con la rect cuoi thi cho rect con chiem het phan du
	}
	
	return rectTmp;
}


void NUI_ALIGN_FORM_START(Nui_Txt_Graph_Typedef *gA, Nui_Txt_Graph_Typedef *gB,uint16_t screenW,int16_t start_x,int16_t y)
{
	const uint8_t *pA=gA->txt;
	const uint8_t *pB=gB->txt;
	uint16_t lenA=0;
	uint16_t lenB=0;
	uint16_t space=0;
	int16_t end_x=screenW-start_x-1;
	lenA=NUI_FONT_GET_WIDTH(pA,gA->font);
	lenB=NUI_FONT_GET_WIDTH(pB,gA->font);
	
	// Toa do x
	space=end_x-lenA-lenB-start_x;
	gA->x=start_x;
	gB->x=start_x+space+lenA;
	
	// Toa do y
	gA->y=y;
	gB->y=y;
}

void NUI_ALIGN_TXT_CENTER_X(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect)
{
	const uint8_t *pA=gA->txt;
	uint16_t lenA=0;
	
	lenA=NUI_FONT_GET_WIDTH(pA,gA->font); 
	
	gA->x=rect.x+(rect.w-lenA)/2;
//	gA->y=rect.y;
	
}

void NUI_ALIGN_TXT_CENTER(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect)
{
	const uint8_t *pA = gA->txt;

  uint16_t widthA  = NUI_FONT_GET_WIDTH(pA, gA->font);
  
  int16_t min_top, max_bottom;
  uint16_t heightA = NUI_FONT_GET_HEIGHT(pA, gA->font, &min_top, &max_bottom);

  gA->x = rect.x + (rect.w  - widthA)  / 2;
  gA->y = rect.y + (rect.h - heightA) / 2 - min_top; // baseline
}

void NUI_ALIGN_TXT_CENTER_Y(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect)
{
	const uint8_t *pA = gA->txt;

//  uint16_t widthA  = NUI_FONT_GET_WIDTH(pA, gA->font);
  
  int16_t min_top, max_bottom;
  uint16_t heightA = NUI_FONT_GET_HEIGHT(pA, gA->font, &min_top, &max_bottom);

//  gA->x = rect.x;
  gA->y = rect.y + (rect.h - heightA) / 2 - min_top; // baseline
}

void NUI_ALIGN_TXT_HORIZONTAL(Nui_Txt_Graph_Typedef *graphic[],uint8_t num, Nui_Rect_Typedef rect)
{
	const uint8_t *pGraphic[num];
	uint16_t total_width=0;
	uint16_t len[num];
	for(uint8_t i=0;i<num;i++)
	{
		pGraphic[i]=graphic[i]->txt;
		len[i]=0;
		len[i]=NUI_FONT_GET_WIDTH(pGraphic[i],graphic[i]->font);
		total_width+=len[i];
	}
	uint16_t startX=rect.x+(rect.w-total_width)/2;
	for(uint8_t i=0;i<num;i++)
	{
		graphic[i]->x=startX;
		startX+=len[i];
	}
}

void NUI_ALIGN_TXT_RIGHT(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect)
{
	const uint8_t *pA=gA->txt;
	uint16_t lenA=0;
	lenA=NUI_FONT_GET_WIDTH(pA,gA->font);
	gA->x=rect.x+rect.w-lenA;
//	gA->y=rect.y;
}

void NUI_ALIGN_TXT_LEFT(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect)
{
	gA->x=rect.x;
//	gA->y=rect.y;
}

void NUI_ALIGN_TXT_TOP(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect)
{
//	gA->x=rect.x;
	gA->y=rect.y;
}

void NUI_ALIGN_TXT_BOTTOM(Nui_Txt_Graph_Typedef *gA, Nui_Rect_Typedef rect)
{
	const uint8_t *pA = gA->txt;
  
  int16_t min_top, max_bottom;
  uint16_t heightA = NUI_FONT_GET_HEIGHT(pA, gA->font, &min_top, &max_bottom);

  gA->y = rect.y + (rect.h - heightA) - min_top; // baseline
}
#endif
