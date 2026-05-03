
#ifndef __NUI_H__
#define __NUI_H__

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

#include "nui_conf.h"
#include "nui_port.h"
#include "nui_disp.h"
#include "nui_color.h"

#if NUI_USE_FONT
#include "nui_font.h"
#endif

#if NUI_USE_IMAGE
#include "nui_image.h"
#endif

#if NUI_USE_GEOMETRY
#include "nui_geometry.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
