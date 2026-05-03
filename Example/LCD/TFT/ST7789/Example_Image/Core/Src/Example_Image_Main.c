#include "Example_Image_Main.h"

nui_driver_Typedef st7789_drv;
ST7789_Typedef ST7789;

Image_Typedef Image={Image_160x160, FORMAT_RGB565, 160, 160};

void EXAMPLE_IMAGE_MAIN(void)
{
	
	st7789_drv.set_px=ST7789_SET_PX;
	st7789_drv.blit_color=ST7789_BLIT_COLOR;
	st7789_drv.clear_window=ST7789_CLEAR_WINDOW;
	st7789_drv.clear=ST7789_CLEAR;
	st7789_drv.blit_mono=ST7789_BLIT_MONO;
	
	NUI_REGISTER_Driver(&st7789_drv);
	ST7789_INIT(&ST7789, &hspi2);
	
	ST7789_CLEAR(&ST7789,NUI_COLOR_BLACK);
	
	NUI_IMAGE_DRAW_IMAGE(&ST7789,80,40,Image);
	
	while(1)
	{
		
	}
}
