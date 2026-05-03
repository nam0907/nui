#include "Example_Image_Main.h"

nui_driver_Typedef ssd1306_drv;
SSD1306_Typedef SSD1306;

Image_Typedef Image={Image_62x62, FORMAT_MONO1BIT, 62, 62};

void EXAMPLE_IMAGE_MAIN(void)
{
	
	ssd1306_drv.set_px=SSD1306_SET_PX;
	ssd1306_drv.clear_window=SSD1306_CLEAR_WINDOW;
	ssd1306_drv.clear=SSD1306_CLEAR;
	ssd1306_drv.blit_mono=SSD1306_BLIT_MONO;
	ssd1306_drv.update=SSD1306_UPDATE;
	
	NUI_REGISTER_Driver(&ssd1306_drv);
	
	SSD1306_INIT(&SSD1306,&hi2c2,0);
	
	NUI_DISP_CLEAR(&SSD1306,NUI_COLOR_BLACK);
	
	NUI_IMAGE_DRAW_IMAGE(&SSD1306,32,9,Image);
	
	NUI_DISP_UPDATE(&SSD1306);
	
	while(1)
	{
		
	}
}
