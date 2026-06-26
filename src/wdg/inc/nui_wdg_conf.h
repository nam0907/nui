#ifndef __NUI_WDG_CONF_H__
#define __NUI_WDG_CONF_H__

#if NUI_WDG_USE_BUTTON
	#if !NUI_USE_FONT
		#undef 	NUI_USE_FONT
		#define NUI_USE_FONT									1
	#endif
	
	#if !NUI_USE_GEOMETRY
		#undef 	NUI_USE_GEOMETRY
		#define NUI_USE_GEOMETRY							1
	#endif
	
	#ifndef NUI_WDG_USE_TXT_GRAPH
		#define NUI_WDG_USE_TXT_GRAPH 				1
	#endif
	
#endif

#if NUI_WDG_USE_TXTBOX
	#if !NUI_USE_FONT
		#undef 	NUI_USE_FONT
		#define NUI_USE_FONT									1
	#endif
	
	#if !NUI_USE_GEOMETRY
		#undef 	NUI_USE_GEOMETRY
		#define NUI_USE_GEOMETRY							1
	#endif
	
	#ifndef NUI_WDG_USE_TXT_GRAPH
		#define NUI_WDG_USE_TXT_GRAPH 				1
	#endif
	
#endif

#include "nui_wdg_default_conf.h" 

#endif
