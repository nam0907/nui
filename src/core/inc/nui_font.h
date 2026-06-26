/**

---

* @file    nui_font.h
* @brief   Font interface for the NUI graphics library.

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

#ifndef __NUI_FONT_H__
#define __NUI_FONT_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "nui_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**

* @defgroup NUI_Font Font
* @brief Font rendering module.
*
* This module provides font abstraction, glyph access,
* UTF-8 text rendering and text drawing utilities.
*
* Fonts can be loaded from memory, SD card or any custom
* source by implementing the font interface.
*
* @{
  */

/**

* @brief Glyph descriptor.
*
* Describes a single character glyph including its dimensions,
* bitmap location and rendering information.
  */
  typedef struct
  {
  /**

  * @brief Glyph width in pixels.
    */
    uint8_t w;

  /**

  * @brief Glyph height in pixels.
    */
    uint8_t h;

  /**

  * @brief Vertical offset.
  *
  * Specifies the vertical position of the glyph
  * relative to the text baseline.
    */
    uint8_t offset;

  /**

  * @brief Number of bytes per bitmap row.
    */
    uint8_t bytePerRow;

  /**

  * @brief Pointer to glyph bitmap data.
  *
  * Bitmap data is stored as a monochrome image.
    */
    const uint8_t *bitmap;

} Nui_Glyph_Typedef;

/**

* @brief Generic font object.
*
* This structure defines a generic font interface used by NUI.
*
* Different font backends such as memory fonts or SD card fonts
* can implement this interface and provide glyph data through
* the callback functions.
  */
  typedef struct Nui_Font_Typedef
  {
  /**

  * @brief Retrieve glyph information.
  *
  * Searches for the specified Unicode character and fills
  * the glyph descriptor.
  *
  * @param[in] font Pointer to font object.
  * @param[in] unicode Unicode code point.
  * @param[out] glyph Output glyph descriptor.
  *
  * @retval true Glyph found.
  * @retval false Glyph not found.
    */
    bool (*get_glyph)(const struct Nui_Font_Typedef *font,uint32_t unicode,Nui_Glyph_Typedef *glyph);

  /**

  * @brief Character spacing.
  *
  * Additional horizontal spacing inserted between glyphs.
    */
    uint16_t gap;

  /**

  * @brief Backend-specific font data.
  *
  * The actual type depends on the font implementation.
    */
    const void *data;

} Nui_Font_Typedef;

/**

* @brief Draw a UTF-8 string.
*
* Draws a text string at the specified position using the
* selected font.
*
* The string is decoded as UTF-8 and rendered character
* by character using the font backend.
*
* @param[in] ctx Display context.
* @param[in] x Left coordinate.
* @param[in] y Top coordinate.
* @param[in] str UTF-8 encoded string.
* @param[in] font Font object.
* @param[in] color Text color.
* @param[in] backColor Background color.
*
* @note The active display driver must support monochrome bitmap
* rendering through the registered driver interface.
  */
  void NUI_FONT_DRAW_STRING(void *ctx, int16_t x, int16_t y, const uint8_t *str, const Nui_Font_Typedef *font,uint32_t color, uint32_t backColor);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
