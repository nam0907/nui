/**

---

* @file    nui_wdg_button.h
* @brief   Button widget.

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

#ifndef __NUI_WDG_BUTTON_H__
#define __NUI_WDG_BUTTON_H__

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "../../align/inc/nui_align_txt.h"
#include "../../core/inc/nui_geometry.h"

#ifdef __cplusplus
extern "C" {
#endif

/**

* @ingroup NUI_Widget
* @{
  */

/**

* @brief Button widget data.
*
* Stores text rendering information and
* visual properties associated with a button.
  */
  typedef struct
  {
  /**

  * @brief Button text color.
    */
    uint32_t txtColor;

  /**

  * @brief Text descriptor.
    */
    Nui_Wdg_Txt_Typedef txt;

} Nui_Wdg_Button_Typedef;

/**

* @brief Set button text.
*
* Updates the text displayed on the button.
*
* @param[in,out] widget Target widget.
* @param[in] FMT Format string.
* @param[in] arg Variable argument list.
  */
  void NUI_WDG_BUTTON_SET_TEXT(Nui_Wdg_Typedef *widget,const uint8_t *FMT,va_list arg);

/**

* @brief Set button text color.
*
* Changes the color used to render
* the button caption.
*
* @param[in,out] widget Target widget.
* @param[in] color New text color.
  */
  void NUI_WDG_BUTTON_SET_TXT_COLOR(Nui_Wdg_Typedef *widget,uint32_t color);

/**

* @brief Set button text alignment.
*
* Configures horizontal and vertical
* alignment of the button caption.
*
* @param[in,out] widget Target widget.
* @param[in] xAlign Horizontal alignment.
* @param[in] yAlign Vertical alignment.
  */
  void NUI_WDG_BUTTON_SET_TXT_ALIGN(Nui_Wdg_Typedef *widget,Nui_Align_Typedef xAlign,Nui_Align_Typedef yAlign);

/**

* @brief Create a button widget.
*
* Creates and initializes a button widget.
*
* @param[in,out] textboxData Button data structure.
* @param[in] id Widget identifier.
* @param[in] x Left coordinate.
* @param[in] y Top coordinate.
* @param[in] w Widget width.
* @param[in] h Widget height.
* @param[in] str Initial button text.
* @param[in] txtMaxLen Maximum text length.
* @param[in] font Font used for rendering.
* @param[in] color Text color.
* @param[in] backColor Background color.
*
* @return Initialized widget object.
  */
  Nui_Wdg_Typedef NUI_WDG_BUTTON_CREATE(Nui_Wdg_Button_Typedef *textboxData,uint16_t id,int16_t x,int16_t y,int16_t w,int16_t h,uint8_t *str,uint16_t txtMaxLen,uint32_t color,uint32_t backColor);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
