/**

---

* @file    nui_port.h
* @brief   Display driver interface for the NUI graphics library.

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

#ifndef __NUI_PORT_H__
#define __NUI_PORT_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**

* @defgroup NUI_Driver Driver
* @brief Display driver interface.
*
* This module defines the hardware abstraction layer used by NUI.
* A display driver must implement the functions defined in
* @ref Nui_Driver_Typedef and register the driver using
* @ref NUI_REGISTER_Driver.
*
* @{
  */

/**

* @brief Display driver interface.
*
* This structure contains all low-level drawing functions required
* by the NUI graphics library. Each display driver must provide
* implementations for these callbacks.
  */
  typedef struct
  {
  /**

  * @brief Set a pixel.
  *
  * Draw a single pixel at the specified coordinates.
  *
  * @param[in] ctx Driver context.
  * @param[in] x X coordinate.
  * @param[in] y Y coordinate.
  * @param[in] color Pixel color.
    */
    void (*set_px)(void *ctx, int16_t x, int16_t y, uint32_t color);

  /**

  * @brief Clear the display.
  *
  * Fill the entire display with a solid color.
  *
  * @param[in] ctx Driver context.
  * @param[in] backColor Background color.
    */
    void (*clear)(void *ctx, uint32_t backColor);

  /**

  * @brief Clear a rectangular area.
  *
  * Fill a specified display region with a solid color.
  *
  * @param[in] ctx Driver context.
  * @param[in] x Left coordinate.
  * @param[in] y Top coordinate.
  * @param[in] w Area width.
  * @param[in] h Area height.
  * @param[in] backColor Background color.
    */
    void (*clear_window)(void *ctx,int16_t x,int16_t y,uint16_t w,uint16_t h,uint32_t backColor);

  /**

  * @brief Update display content.
  *
  * Flush any pending drawing operations to the display.
  *
  * @param[in] ctx Driver context.
    */
    void (*update)(void *ctx);

  /**

  * @brief Draw a monochrome bitmap.
  *
  * Draw a 1-bit bitmap to the display.
  *
  * @param[in] ctx Driver context.
  * @param[in] dst_x Destination X coordinate.
  * @param[in] dst_y Destination Y coordinate.
  * @param[in] src_x Source X offset.
  * @param[in] src_y Source Y offset.
  * @param[in] w Width of drawing area.
  * @param[in] h Height of drawing area.
  * @param[in] bitmap Pointer to bitmap data.
  * @param[in] bytes_per_line Number of bytes per bitmap line.
  * @param[in] color Foreground color.
  * @param[in] backColor Background color.
    */
    void (*blit_mono)(void *ctx,int16_t dst_x,int16_t dst_y,int16_t src_x,int16_t src_y,uint16_t w,uint16_t h,const uint8_t *bitmap,uint16_t bytes_per_line,uint32_t color,uint32_t backColor);

  /**

  * @brief Draw a color bitmap.
  *
  * Draw a color image to the display.
  *
  * @param[in] ctx Driver context.
  * @param[in] dst_x Destination X coordinate.
  * @param[in] dst_y Destination Y coordinate.
  * @param[in] src_x Source X offset.
  * @param[in] src_y Source Y offset.
  * @param[in] w Width of drawing area.
  * @param[in] h Height of drawing area.
  * @param[in] data Pointer to image data.
  * @param[in] bytes_per_line Number of bytes per image line.
    */
    void (*blit_color)(void *ctx,int16_t dst_x,int16_t dst_y,int16_t src_x,int16_t src_y,uint16_t w,uint16_t h,const uint8_t *data,uint16_t bytes_per_line);

} Nui_Driver_Typedef;

/**

* @brief Pointer to the active display driver.
  */
  extern Nui_Driver_Typedef *nui_drv;

/**

* @brief Driver initialization status.
  */
  extern bool nui_ready;

/**

* @brief Register a display driver.
*
* Registers a display driver instance so it can be used by
* the NUI graphics library.
*
* @param[in] drv Pointer to driver object.
  */
  void NUI_REGISTER_Driver(Nui_Driver_Typedef *drv);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
