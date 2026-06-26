/**

---

* @file    nui_disp.h
* @brief   Display control functions for the NUI graphics library.

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

#ifndef __NUI_DISP_H__
#define __NUI_DISP_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**

* @defgroup NUI_Display Display
* @brief Display management functions.
*
* This module provides basic display operations such as
* clearing the screen, clearing regions and updating
* display content.
*
* @{
  */

/**

* @brief Clear the entire display.
*
* Fills the complete display area using the specified
* background color.
*
* @param[in] ctx Display context.
* @param[in] backColor Background color.
  */
  void NUI_DISP_CLEAR(void *ctx, uint32_t backColor);

/**

* @brief Clear a rectangular area.
*
* Fills the specified display region using the
* supplied background color.
*
* @param[in] ctx Display context.
* @param[in] x Left coordinate.
* @param[in] y Top coordinate.
* @param[in] w Area width.
* @param[in] h Area height.
* @param[in] backColor Background color.
  */
  void NUI_DISP_CLEAR_WINDOW(void *ctx,int16_t x,int16_t y,int16_t w,int16_t h,uint32_t backColor);

/**

* @brief Update the display.
*
* Flushes pending drawing operations to the display.
*
* @param[in] ctx Display context.
  */
  void NUI_DISP_UPDATE(void *ctx);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
