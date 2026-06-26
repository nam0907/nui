#include "../inc/nui_wdg_ev.h"

#if NUI_USE_WIDGET

#error O

void NUI_WDG_DRAW(void *ctx,const Nui_Wdg_Typedef *widget)
{
	if(!widget) return;
  if(!widget->visible) return;
  if(!widget->data) return;

  if(!widget->type) return;
	if(!widget->draw) return;
	
	widget->draw(ctx,widget);
}

void NUI_WDG_SET_POS(Nui_Wdg_Typedef *widget,int16_t x, int16_t y)
{
	if(!widget) return;
	widget->x=x;
	widget->y=y;
}

void NUI_WDG_SET_WIDTH(Nui_Wdg_Typedef *widget,int16_t w)
{
	if(!widget) return;
	widget->w=w;
}

void NUI_WDG_SET_HEIGHT(Nui_Wdg_Typedef *widget,int16_t h)
{
	if(!widget) return;
	widget->h=h;
}

void NUI_WDG_SET_VISIBLE(Nui_Wdg_Typedef *widget,bool visible)
{
	if(!widget) return;
	widget->visible=visible;
}

#endif

