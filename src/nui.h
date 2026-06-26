
/**
  ******************************************************************************
  * @file    nui.h
  * @brief   Main header file for the NUI graphics library.
  *
  * This file provides access to all public NUI modules.
  *
  * Depending on the configuration options defined in
  * @ref nui_conf.h, the corresponding modules are
  * automatically included.
  *
  * Included modules may contain:
  * - Display driver interface
  * - Display control functions
  * - Color definitions
  * - Font rendering
  * - Image rendering
  * - Geometry drawing
  * - Widget framework
  *
  * @note This file is intended to be the only header
  * users need to include in most applications.
  ******************************************************************************
  */

#ifndef __NUI_H__
#define __NUI_H__

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

#include "nui_conf.h"
#include "core/inc/nui_port.h"
#include "core/inc/nui_disp.h"
#include "core/inc/nui_color.h"

#if NUI_USE_FONT
	#include "core/inc/nui_font.h"
	#if NUI_FONT_USE_MEMORY
		#include "core/inc/nui_font_mem.h"
	#endif
	#if NUI_FONT_USE_SD
		#include "core/inc/nui_font_sd.h"
	#endif
#endif

#if NUI_USE_IMAGE
	#include "core/inc/nui_image.h"
	#if NUI_IMAGE_USE_MEMORY
		#include "core/inc/nui_image_mem.h"
	#endif
	#if NUI_IMAGE_USE_SD
		#include "core/inc/nui_image_sd.h"
	#endif
#endif

#if NUI_USE_GEOMETRY
	#include "core/inc/nui_geometry.h"
#endif

#if NUI_USE_WIDGET
	#include "wdg/inc/nui_wdg.h"
#endif


#ifdef __cplusplus
}
#endif

#endif

