#include "../inc/nui_wdg_checkbox.h"
#include "../../int/nui_font_def_int.h"

#if NUI_WDG_USE_TXT_GRAPH
void NUI_WDG_CHECKBOX_DRAW(void *ctx,const Nui_Wdg_Typedef *widget)
{
	Nui_Wdg_TxtBox_Typedef *textbox=(Nui_Wdg_TxtBox_Typedef *) widget->data;
	
	// Khai bao cat string neu kich thuoc string lon hon textbox 
	Nui_Rect_Typedef clip=
	{
		.x = widget->x,
		.y = widget->y,
		.w = widget->w,
		.h = widget->h,
	};
	
	Nui_Txt_Graph_Typedef txtGraph;
	txtGraph.txt=textbox->txt.txt;
	txtGraph.color=textbox->txtColor;
	txtGraph.backColor=widget->backColor;
	txtGraph.font=textbox->txt.font;
	
	switch(textbox->txt.xAlign)
	{
		case NUI_ALIGN_LEFT:
		{
			NUI_ALIGN_TXT_LEFT(&txtGraph,clip);
			break;
		}
		case NUI_ALIGN_RIGHT:
		{
			NUI_ALIGN_TXT_RIGHT(&txtGraph,clip);
			break;
		}
		case NUI_ALIGN_CENTER:
		{
			NUI_ALIGN_TXT_CENTER_X(&txtGraph,clip);
			break;
		}
		case NUI_ALIGN_BOTTOM:
		{
			break;
		}
		case NUI_ALIGN_TOP:
		{
			break;
		}
		default:
		{
			NUI_ALIGN_TXT_CENTER_X(&txtGraph,clip);
			break;
		}
	}
	
	switch(textbox->txt.yAlign)
	{
		case NUI_ALIGN_TOP:
		{
			NUI_ALIGN_TXT_TOP(&txtGraph,clip);
			break;
		}
		case NUI_ALIGN_BOTTOM:
		{
			NUI_ALIGN_TXT_BOTTOM(&txtGraph,clip);
			break;
		}
		case NUI_ALIGN_CENTER:
		{
			NUI_ALIGN_TXT_CENTER_Y(&txtGraph,clip);
			break;
		}
		case NUI_ALIGN_RIGHT:
		{
			break;
		}
		case NUI_ALIGN_LEFT:
		{
			break;
		}
		default:
		{
			NUI_ALIGN_TXT_CENTER_Y(&txtGraph,clip);
			break;
		}
	}
	
	if(widget->visible)
	{
		NUI_GEOMETRY_DRAW_FILL_RECTANGLE(ctx,widget->x,widget->y,widget->w,widget->h,widget->backColor);
		NUI_FONT_DRAW_TXT_GRAPH(ctx,&clip,&txtGraph);
	}
}

void NUI_WDG_CHECKBOX_SET_TXT_COLOR(Nui_Wdg_Typedef *widget,uint32_t color)
{
	Nui_Wdg_TxtBox_Typedef *textbox=(Nui_Wdg_TxtBox_Typedef*)widget->data;
	textbox->txtColor=color;
}

void NUI_WDG_CHECKBOX_SET_TXT_ALIGN(Nui_Wdg_Typedef *widget,Nui_Align_Typedef xAlign, Nui_Align_Typedef yAlign)
{
	Nui_Wdg_TxtBox_Typedef *textbox=(Nui_Wdg_TxtBox_Typedef*)widget->data;
	textbox->txt.xAlign=xAlign;
	textbox->txt.yAlign=yAlign;
} 

//Nui_Wdg_Typedef NUI_WDG_CHECKBOX_CREATE(Nui_Wdg_TxtBox_Typedef *textboxData,uint16_t id, int16_t x, int16_t y, int16_t w, int16_t h,uint8_t *str,uint16_t txtMaxLen,const Nui_Font_Typedef *font,uint32_t color, uint32_t backColor)
//{
//	/* 
//	=========================== Init textbox data============================
//	*/
//	textboxData->txt.font=font;
//	textboxData->txtColor=color;
//	textboxData->txt.txt=str;
//	textboxData->txt.txt_maxl=txtMaxLen; 
//	textboxData->txt.xAlign=NUI_ALIGN_CENTER; 
//	textboxData->txt.yAlign=NUI_ALIGN_CENTER;
//	
//	/* 
//	=========================================================================
//	*/
//	
//	Nui_Wdg_Typedef textbox=
//	{
//		.x = x,
//		.y = y,
//		.w = w,
//		.h = h,
//		.id=id,
//		.visible=true,
//		.backColor=backColor,
//		.type=NUI_WDG_TEXTBOX,
//		.draw=NUI_WDG_CHECKBOX_DRAW,
//		.data=textboxData,
//	};
//	
//	return textbox;
//}

#endif

