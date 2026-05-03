#include "nui_port.h"

nui_driver_Typedef *nui_drv=0;
bool nui_ready=false;

void NUI_REGISTER_Driver(nui_driver_Typedef * drv)
{
	nui_drv=drv;
	nui_ready=true;
}
