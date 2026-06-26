/**

---

* @file    nui_wdg_ev.h
* @brief   Widget management functions.

---

* @attention
*
* Copyright (c) 2026 Nam Pham.
* All rights reserved.
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*

---

*/

#ifndef __NUI_WDG_EV_H__
#define __NUI_WDG_EV_H__

#if NUI_USE_WIDGET

#include "nui_wdg_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/**

* @ingroup NUI_Widget
* @{
  */

/**

* @brief Draw a widget.
*
* Renders the specified widget using the active
* display driver.
*
* The widget appearance depends on its type,
* current state and associated data.
*
* @param[in] ctx Display context.
* @param[in] widget Widget object.
  */
  void NUI_WDG_DRAW(void *ctx,const Nui_Wdg_Typedef *widget);

/**

* @brief Set widget position.
*
* Updates the widget position on the display.
*
* @param[in,out] widget Target widget.
* @param[in] x New X coordinate.
* @param[in] y New Y coordinate.
  */
  void NUI_WDG_SET_POS(Nui_Wdg_Typedef *widget,int16_t x,int16_t y);

/**

* @brief Set widget width.
*
* Updates the widget width.
*
* @param[in,out] widget Target widget.
* @param[in] w New widget width.
  */
  void NUI_WDG_SET_WIDTH(Nui_Wdg_Typedef *widget,int16_t w);

/**

* @brief Set widget height.
*
* Updates the widget height.
*
* @param[in,out] widget Target widget.
* @param[in] h New widget height.
  */
  void NUI_WDG_SET_HEIGHT(Nui_Wdg_Typedef *widget,int16_t h);

/**

* @brief Set widget visibility.
*
* Controls whether the widget is visible.
*
* Hidden widgets are not rendered by
* @ref NUI_WDG_DRAW.
*
* @param[in,out] widget Target widget.
* @param[in] visible Visibility state.
*
* @retval true Widget is visible.
* @retval false Widget is hidden.
  */
  void NUI_WDG_SET_VISIBLE(Nui_Wdg_Typedef *widget,bool visible);

/** @} */

#ifdef __cplusplus
}
#endif

#endif

#endif
