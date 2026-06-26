/**

---

* @file    nui_wdg_txtbox.h
* @brief   TextBox widget.

---

*/

#ifndef __WIDGET_TEXTBOX_H__
#define __WIDGET_TEXTBOX_H__

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "../../core/inc/nui_geometry.h"
#include "../../align/inc/nui_align.h"

#ifdef __cplusplus
extern "C" {
#endif

/**

* @ingroup NUI_Widget
* @{
  */

/**

* @brief TextBox widget data.
*
* Stores the visual properties and text
* information associated with a TextBox widget.
  */
  typedef struct
  {
  /**

  * @brief Text color.
    */
    uint32_t txtColor;

  /**

  * @brief Text descriptor.
    */
    Nui_Wdg_Txt_Typedef txt;

} Nui_Wdg_TxtBox_Typedef;

/**

* @brief Set TextBox text.
*
* Updates the text displayed by the widget.
*
* @param[in,out] widget Target widget.
* @param[in] FMT Format string.
* @param[in] arg Variable argument list.
  */
  void NUI_WDG_TEXTBOX_SET_TEXT(Nui_Wdg_Typedef *widget,const uint8_t *FMT,va_list arg);

/**

* @brief Set text color.
*
* Changes the color used to render text.
*
* @param[in,out] widget Target widget.
* @param[in] color New text color.
  */
  void NUI_WDG_TEXTBOX_SET_TXT_COLOR(Nui_Wdg_Typedef *widget,uint32_t color);

/**

* @brief Create a TextBox widget.
*
* Creates and initializes a TextBox widget.
*
* @param[in,out] textboxData Widget data.
* @param[in] id Widget identifier.
* @param[in] x Left coordinate.
* @param[in] y Top coordinate.
* @param[in] w Width.
* @param[in] h Height.
* @param[in] str Initial text.
* @param[in] txtMaxLen Maximum text length.
* @param[in] font Font used for rendering.
* @param[in] color Text color.
* @param[in] backColor Background color.
*
* @return Initialized widget object.
  */
  Nui_Wdg_Typedef NUI_WDG_TEXTBOX_CREATE(Nui_Wdg_TxtBox_Typedef *textboxData,uint16_t id,int16_t x,int16_t y,int16_t w,int16_t h,uint8_t *str,uint16_t txtMaxLen,const Nui_Font_Typedef *font,uint32_t color,uint32_t backColor);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
