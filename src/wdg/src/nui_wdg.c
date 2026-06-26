//#include "nui_wdg.h"

//WidgetOop_Typedef widgetOop[]= // widget function oop 
//{
//	[WIDGET_TEXTBOX]=
//	{
//		.draw=TEXTBOX_DRAW,
//	  .setText=TEXTBOX_SET_TEXT,
//		.setColor=TEXTBOX_SET_COLOR,
//		.setBackColor=TEXTBOX_SET_BACKCOLOR,
//	},
////	[WIDGET_BUTTON]=
////	{
////		.draw=BUTTON_DRAW,
////	  .setText=BUTTON_SET_TEXT,
////		.setColor=BUTTON_SET_COLOR,
////		.setBackColor=BUTTON_SET_BACKCOLOR,
////	},
//};

//uint16_t Round(float value)
//{
//    return (uint16_t)(value+0.5f);
//}


////void WIDGET_DRAW(void *ctx,const Nui_Wdg_Typedef *widget,void (*lcd_draw_px)(void *ctx,int16_t , int16_t , uint32_t ))
//void WIDGET_DRAW(void *ctx,const Nui_Wdg_Typedef *widget)
//{
//	if(!widget) return;
//  if(!widget->visible) return;
//  if(!widget->Data) return;

//  if(widget->type >= WIDGET_TYPE_MAX) return;

//  const WidgetOop_Typedef *oop = &widgetOop[widget->type];
//  if(!oop->draw) return;

////  oop->draw(ctx, widget, lcd_draw_px);
//	oop->draw(ctx, widget);
//}

//void WIDGET_SET_TEXT(Nui_Wdg_Typedef *widget,const uint8_t *FMT,...)
//{
////	if(widget->type==WIDGET_NULL) return;
//	if(!widget) return;
//  if(!widget->Data) return;

//  if(widget->type >= WIDGET_TYPE_MAX) return;

//  const WidgetOop_Typedef *oop = &widgetOop[widget->type];
//  if(!oop->setText) return;
//	
//	va_list arg;
//  va_start(arg,FMT);
//	oop->setText(widget,FMT,arg);
//  va_end (arg);
//}

//void WIDGET_SET_POS(Nui_Wdg_Typedef *widget,int16_t x,int16_t y)
//{
//  widget->x=x;
//	widget->y=y;
//}

//void WIDGET_SET_WIDTH(Nui_Wdg_Typedef *widget,uint16_t w)
//{
//  widget->w=w;
//}

//void WIDGET_SET_HEIGHT(Nui_Wdg_Typedef *widget,uint16_t h)
//{
//  widget->h=h;
//}

//void WIDGET_SET_VISIBLE(Nui_Wdg_Typedef *widget,bool visible)
//{
//  widget->visible=visible;
//}

//void WIDGET_SET_COLOR(Nui_Wdg_Typedef *widget,uint32_t color)
//{
//	if(!widget->Data) return;
//	if(!widget) return;
//	if(widget->type>=WIDGET_TYPE_MAX) return;
//	
//	const WidgetOop_Typedef *oop = &widgetOop[widget->type];
//  if(!oop->setColor) return;
//	
//	oop->setColor(widget,color);
//}

//void WIDGET_SET_BACKCOLOR(Nui_Wdg_Typedef *widget,uint32_t backColor)
//{
//	if(!widget->Data) return;
//	if(!widget) return;
//	if(widget->type>=WIDGET_TYPE_MAX) return;
//	
//	const WidgetOop_Typedef *oop = &widgetOop[widget->type];
//  if(!oop->setBackColor) return;
//	
//	oop->setBackColor(widget,backColor);
//}

//void WIDGET_SET_CHECK(Nui_Wdg_Typedef *widget,bool check)
//{
//	if(widget->type!=WIDGET_CHECKBOX) return;
//	if(!widget->Data) return;
//	if(!widget) return;
//	
//	WidgetCheckBox_Typedef *wCBox=(WidgetCheckBox_Typedef *) widget->Data;
//	wCBox->check=check;
//}

////void WIDGET_SET_COLOR(Nui_Wdg_Typedef *widget,uint32_t Color)
////{
////  switch(widget->type)
////	{
////		case WIDGET_BUTTON:
////		{
////			WidgetButton_Typedef *button=(WidgetButton_Typedef*)widget->Data;
////			button->Color=Color;
////			break;
////		}
////		case WIDGET_TEXTBOX:
////		{
////			Nui_Wdg_TxtBox *textbox=(Nui_Wdg_TxtBox*)widget->Data;
////			textbox->Color=Color;
////			break;
////		}
////		case WIDGET_PROGRESS:
////		{
////			WidgetProgress_Typedef *progress=(WidgetProgress_Typedef *) widget->Data;
////			progress->Color=Color;
////			break;
////		}
////		case WIDGET_SLIDER:
////		{
////			WidgetSlider_Typedef *slider=(WidgetSlider_Typedef *) widget->Data;
////			slider->Color=Color;
////			break;
////		}
////		case WIDGET_CHECKBOX:
////		{
////			WidgetCheckBox_Typedef *checkbox=(WidgetCheckBox_Typedef *) widget->Data;
////			checkbox->Color=Color;
////			break;
////		}
//////		case WIDGET_PICTUREBOX:
//////		{
//////			WidgetPictureBox_Typedef *picturebox=(WidgetPictureBox_Typedef *) widget->Data;
//////			picturebox->Color=Color;
//////			break;
//////		}
////		default:
////		{
////			return;
////		}
////	}
////}

////void WIDGET_SET_BACKCOLOR(Nui_Wdg_Typedef *widget,uint32_t BackColor)
////{
////  switch(widget->type)
////	{
////		case WIDGET_BUTTON:
////		{
////			WidgetButton_Typedef *button=(WidgetButton_Typedef*)widget->Data;
////			button->BackColor=BackColor;
////			break;
////		}
////		case WIDGET_TEXTBOX:
////		{
////			Nui_Wdg_TxtBox *textbox=(Nui_Wdg_TxtBox*)widget->Data;
////			textbox->BackColor=BackColor;
////			break;
////		}
//////		case WIDGET_PROGRESS:
//////		{
//////			WidgetProgress_Typedef *progress=(WidgetProgress_Typedef *) widget->Data;
//////			progress->BackColor=BackColor;
//////			break;
//////		}
//////		case WIDGET_SLIDER:
//////		{
//////			WidgetSlider_Typedef *slider=(WidgetSlider_Typedef *) widget->Data;
//////			slider->BackColor=BackColor;
//////			break;
//////		}
//////		case WIDGET_CHECKBOX:
//////		{
//////			WidgetCheckBox_Typedef *checkbox=(WidgetCheckBox_Typedef *) widget->Data;
//////			checkbox->BackColor=BackColor;
//////			break;
//////		}
////		default:
////		{
////			return;
////		}
////	}
////}
