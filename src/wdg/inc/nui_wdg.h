/**
 * @defgroup NUI_Widget Widget
 * @brief Widget framework.
 *
 * This module provides graphical user interface widgets
 * for the NUI graphics library.
 *
 * Available widgets:
 * - Button
 * - TextBox
 * - CheckBox
 *
 * @{
 */

#ifndef __NUI_WDG_H__
#define __NUI_WDG_H__

//#include "nui_wdg_conf.h"
#include "nui_conf.h"
#include "nui_wdg_ev.h"

#if NUI_WDG_USE_BUTTON
#include "nui_wdg_button.h"
#endif

#if NUI_WDG_USE_TXTBOX
#include "nui_wdg_txtbox.h"
#endif

#endif

/** @} */
