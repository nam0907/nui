#include "../inc/nui_port.h"

Nui_Driver_Typedef *nui_drv=0;
bool nui_ready=false;

void NUI_REGISTER_Driver(Nui_Driver_Typedef * drv)
{
	nui_drv=drv;
	nui_ready=true;
}
