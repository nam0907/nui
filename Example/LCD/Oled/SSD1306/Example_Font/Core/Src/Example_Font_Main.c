#include "Example_Font_Main.h"

nui_driver_Typedef ssd1306_drv;
SSD1306_Typedef SSD1306;

Font_Typedef Font_Test={Times_New_Roman_Regular_72, Times_New_Roman_Regular_72_MAP, Times_New_Roman_Regular_72_REF, 0, 229};

void EXAMPLE_FONT_MAIN(void)
{
	
	ssd1306_drv.set_px=SSD1306_SET_PX;
	ssd1306_drv.clear_window=SSD1306_CLEAR_WINDOW;
	ssd1306_drv.clear=SSD1306_CLEAR;
	ssd1306_drv.blit_mono=SSD1306_BLIT_MONO;
	ssd1306_drv.update=SSD1306_UPDATE;
	
	NUI_REGISTER_Driver(&ssd1306_drv);
	
	SSD1306_INIT(&SSD1306,&hi2c2,0);
	SSD1306_ROTATION(&SSD1306,SSD1306_ROTATION_0_DEGREE);
	
	NUI_DISP_CLEAR(&SSD1306,NUI_COLOR_BLACK);
	
	NUI_FONT_DRAW_STRING(&SSD1306,0,10,(uint8_t*)"Xin Chào",Font_Test,NUI_COLOR_MAGENTA,NUI_COLOR_BLACK);
	
	NUI_DISP_UPDATE(&SSD1306);
	
	while(1)
	{
		
	}
}
