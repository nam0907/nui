#include "nui_sd.h"
#include "../int/nui_sd_int.h"

#if NUI_USE_SD
FRESULT chekRead;

bool NUI_SD_READ_BIN(void * userData, uint32_t offset, void *buffer, uint32_t Size)
{
	UINT br;
	Nui_SD_Typedef *data =(Nui_SD_Typedef *)userData;
	
	if(f_lseek(&data->file, offset) != FR_OK)
        return false;
	chekRead=f_read(&data->file,buffer,Size,&br);
	if(chekRead!=FR_OK) return false;
//	if(f_read(&data->file,buffer,Size,&br) != FR_OK ) return false;
	
	return br==Size;
}

FRESULT check;

bool NUI_SD_INIT(Nui_SD_Typedef *sd, const uint8_t *pathFile)
{
	uint8_t path[NUI_PATH_MAX_SIZE]={0};
	strncpy((char*)path,(char*)pathFile,NUI_PATH_MAX_SIZE);
	
	check=f_mount(&sd->fs, "", 1);	
//	check=f_open(&sd->file,(TCHAR *)path,FA_READ);
	if(f_open(&sd->file,(TCHAR *)path,FA_READ) != FR_OK) return false;
		
	sd->stream.read=NUI_SD_READ_BIN;
	sd->stream.userData=sd;
	
	return true;
}
#endif
