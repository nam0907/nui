#include "Example_Font_Main.h"

nui_driver_Typedef st7789_drv;
ST7789_Typedef ST7789;

Font_Typedef Font_Test={Times_New_Roman_Regular_72, Times_New_Roman_Regular_72_MAP, Times_New_Roman_Regular_72_REF, 0, 229};

void EXAMPLE_FONT_MAIN(void)
{
	
	st7789_drv.set_px=ST7789_SET_PX;
	st7789_drv.blit_color=ST7789_BLIT_COLOR;
	st7789_drv.clear_window=ST7789_CLEAR_WINDOW;
	st7789_drv.clear=ST7789_CLEAR;
	st7789_drv.blit_mono=ST7789_BLIT_MONO;
	
	NUI_REGISTER_Driver(&st7789_drv);
	ST7789_INIT(&ST7789, &hspi2);
	
	ST7789_CLEAR(&ST7789,NUI_COLOR_BLACK);
	
	NUI_FONT_DRAW_STRING(&ST7789,50,50,(uint8_t*)"Xin Chào",Font_Test,NUI_COLOR_MAGENTA,NUI_COLOR_BLACK);
	NUI_FONT_DRAW_STRING(&ST7789,50,100,(uint8_t*)"Hello",Font_Test,NUI_COLOR_CYAN,NUI_COLOR_BLACK);
	
	while(1)
	{
		
	}
}
