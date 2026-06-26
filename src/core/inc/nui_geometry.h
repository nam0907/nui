/**

---

* @file    nui_geometry.h
* @brief   Geometry drawing functions for the NUI graphics library.

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

#ifndef __NUI_GEOMETRY_H__
#define __NUI_GEOMETRY_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**

* @defgroup NUI_Geometry Geometry
* @brief Geometry drawing module.
*
* This module provides basic drawing primitives such as
* lines, rectangles and circles.
*
* @{
  */

/**

* @brief Clear a rectangular region.
*
* Clears the specified display area.
*
* @param[in] ctx Display context.
* @param[in] x Left coordinate.
* @param[in] y Top coordinate.
* @param[in] w Area width.
* @param[in] h Area height.
  */
  void GRAPHIC_CLEAR_WINDOW(void *ctx,int16_t x,int16_t y,int16_t w,int16_t h);

/**

* @brief Draw a line.
*
* Draws a line starting at the specified position.
*
* @param[in] ctx Display context.
* @param[in] x Start X coordinate.
* @param[in] y Start Y coordinate.
* @param[in] length Line length.
* @param[in] color Line color.
  */
  void NUI_GEOMETRY_DRAW_LINE(void *ctx,
  int16_t x,
  int16_t y,
  uint16_t length,
  uint32_t color);

/**

* @brief Draw a filled rectangle.
*
* Draws a solid rectangle filled with the specified color.
*
* @param[in] ctx Display context.
* @param[in] x Left coordinate.
* @param[in] y Top coordinate.
* @param[in] width Rectangle width.
* @param[in] height Rectangle height.
* @param[in] color Fill color.
  */
  void NUI_GEOMETRY_DRAW_FILL_RECTANGLE(void *ctx,int16_t x,int16_t y,uint16_t width,uint16_t height,uint32_t color);

/**

* @brief Draw a rectangle outline.
*
* Draws only the border of a rectangle.
*
* @param[in] ctx Display context.
* @param[in] x Left coordinate.
* @param[in] y Top coordinate.
* @param[in] width Rectangle width.
* @param[in] height Rectangle height.
* @param[in] color Border color.
  */
  void NUI_GEOMETRY_DRAW_RECTANGLE(void *ctx,int16_t x,int16_t y, uint16_t width, uint16_t height,uint32_t color);

/**

* @brief Draw a circle.
*
* Draws the outline of a circle.
*
* @param[in] ctx Display context.
* @param[in] x Center X coordinate.
* @param[in] y Center Y coordinate.
* @param[in] r Circle radius.
* @param[in] color Circle color.
  */
  void NUI_GEOMETRY_DRAW_CIRCLE(void *ctx,int16_t x,int16_t y,uint16_t r,uint32_t color);

/**

* @brief Draw a filled circle.
*
* Draws a solid circle filled with the specified color.
*
* @param[in] ctx Display context.
* @param[in] x Center X coordinate.
* @param[in] y Center Y coordinate.
* @param[in] r Circle radius.
* @param[in] color Fill color.
  */
  void NUI_GEOMETRY_DRAW_FILL_CIRCLE(void *ctx,int16_t x, int16_t y,uint16_t r,uint32_t color);

//void GRAPHIC_CLEAR_WINDOW(void *ctx,int16_t x,int16_t y,int16_t w,int16_t h);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
