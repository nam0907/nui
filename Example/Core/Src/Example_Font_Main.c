#include "Example_Font_Main.h"

Nui_Driver_Typedef st7789_drv;
ST7789_Typedef ST7789;

//Nui_Font_Typedef Font_Test={Times_New_Roman_Regular_72, Times_New_Roman_Regular_72_MAP, Times_New_Roman_Regular_72_REF, 0, 229,1};
//Nui_Font_Typedef Font_Test={Times_New_Roman_36, Times_New_Roman_36_MAP, Times_New_Roman_36_REF, 0, 229, 1};



Nui_Font_Mem_Typedef Font_Test_Mem={Times_New_Roman_36, Times_New_Roman_36_MAP, Times_New_Roman_36_REF, 229, 1};
Nui_Font_Typedef Font_Test;

//Nui_Font_SD_Typedef Font_Test_SD;


//Nui_Wdg_Typedef textbox1={0};
//Nui_Wdg_TxtBox_Typedef textbox1_Data={0};

void ST7789_WRITE_DC(uint8_t value)
{
	HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,value?GPIO_PIN_SET:GPIO_PIN_RESET);
	
}

void ST7789_WRITE_CS(uint8_t value)
{
	HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,value?GPIO_PIN_SET:GPIO_PIN_RESET);
}

void ST7789_WRITE_RESET(uint8_t value)
{
	HAL_GPIO_WritePin(RST_GPIO_Port,RST_Pin,value?GPIO_PIN_SET:GPIO_PIN_RESET);
}

void ST7789_SPI_TRANSMIT(const uint8_t *data, uint16_t len)
{
	HAL_SPI_Transmit(&hspi2,data,len,100);
}

//void ST7789_SPI_DMA(const uint8_t *data, uint16_t len)
//{
//	HAL_SPI_Transmit_DMA(&hspi2,data,len);
//}

void ST7789_DELAY(uint32_t time)
{
	HAL_Delay(time);
}

void EXAMPLE_FONT_MAIN(void)
{
	
	ST7789.SPITransmit=ST7789_SPI_TRANSMIT;
	ST7789.WriteDC=ST7789_WRITE_DC;
	ST7789.WriteCS=ST7789_WRITE_CS;
	ST7789.Delay=ST7789_DELAY;
	ST7789.WriteReset=ST7789_WRITE_RESET;
	
	st7789_drv.set_px=ST7789_SET_PX;
	st7789_drv.blit_color=ST7789_BLIT_COLOR;
	st7789_drv.clear_window=ST7789_CLEAR_WINDOW;
	st7789_drv.clear=ST7789_CLEAR;
	st7789_drv.blit_mono=ST7789_BLIT_MONO;
	
	NUI_REGISTER_Driver(&st7789_drv);
	ST7789_INIT(&ST7789);
	
	ST7789_CLEAR(&ST7789,NUI_COLOR_BLACK);
	
//	NUI_FONT_MEM_INIT(&Font_Test,&Font_Test_Mem);
//	NUI_FONT_SD_INIT(&Font_Test, &Font_Test_SD, (uint8_t *)"Font_test.bin");
	
//	textbox1=NUI_WDG_TEXTBOX_CREATE(&textbox1_Data,0,10,50,240,50,(uint8_t*)"Yêu An",20,&Font_Test,NUI_COLOR_WHITE,NUI_COLOR_CYAN);
	
	NUI_FONT_DRAW_STRING(&ST7789,50,100,(uint8_t*)"0123",&Font_Test,NUI_COLOR_CYAN,NUI_COLOR_BLACK);
//	NUI_WDG_DRAW(&ST7789,&textbox1);
	while(1)
	{
		
	}
}
