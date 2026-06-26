/**

---

* @file    nui_image.h
* @brief   Image interface for the NUI graphics library.

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

#ifndef __NUI_IMAGE_H__
#define __NUI_IMAGE_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**

* @defgroup NUI_Image Image
* @brief Image rendering module.
*
* This module provides image abstraction and rendering
* functions for the NUI graphics library.
*
* Images can be stored in memory, loaded from external
* storage, or provided by custom image backends through
* the image interface.
*
* @{
  */

/**
  * @cond
  */

  #define RGB565_RMASK        (uint8_t)0x1F
  #define RGB565_GMASK        (uint8_t)0x3F
  #define RGB565_BMASK        (uint8_t)0x1F
  
/**
  * @endcond
  */

/**
* @brief Supported image formats.
*
* Defines the pixel format used by an image object.
  */
  typedef enum
  {
  /**

  * @brief RGB565 image format.
  *
  * Each pixel is stored using 16 bits.
    */
    NUI_IMAGE_FORMAT_RGB565 = 0,

  /**

  * @brief RGB888 image format.
  *
  * Each pixel is stored using 24 bits.
    */
    NUI_IMAGE_FORMAT_RGB888 = 1,

  /**

  * @brief Monochrome image format.
  *
  * Each pixel is represented by a single bit.
    */
    NUI_IMAGE_FORMAT_MONO1BIT = 2,

} ImageFormat_Typedef;

/**

* @brief Generic image object.
*
* This structure defines the image interface used by NUI.
*
* Different image sources such as memory images,
* SD card images, or custom image providers can
* implement this interface.
  */
  typedef struct Nui_Image_Typedef
  {
  /**

  * @brief Read image data by line.
  *
  * Retrieves one or more image lines and stores them
  * in the supplied buffer.
  *
  * @param[in] img Pointer to image object.
  * @param[in] lineSize Number of bytes per line.
  * @param[in] line Starting line index.
  * @param[in] numLine Number of lines to retrieve.
  * @param[out] buff Destination buffer.
  *
  * @retval true Operation successful.
  * @retval false Operation failed.
    */
    bool (*get_line)(const struct Nui_Image_Typedef *img,
    uint16_t lineSize,
    uint16_t line,
    uint16_t numLine,
    uint8_t *buff);

  /**

  * @brief Get direct bitmap access.
  *
  * Returns a pointer to the internal bitmap data.
  *
  * @param[in] img Pointer to image object.
  *
  * @return Pointer to bitmap data.
    */
    const uint8_t *(*get_bitmap)(const struct Nui_Image_Typedef *img);

  /**

  * @brief Backend-specific image data.
    */
    void *data;

  /**

  * @brief Image format.
    */
    ImageFormat_Typedef format;

  /**

  * @brief Image width in pixels.
    */
    uint16_t w;

  /**

  * @brief Image height in pixels.
    */
    uint16_t h;

} Nui_Image_Typedef;

/**

* @brief Image graphic descriptor.
*
* Associates an image object with a display position.
  */
  typedef struct
  {
  /**

  * @brief X coordinate.
    */
    int16_t x;

  /**

  * @brief Y coordinate.
    */
    int16_t y;

  /**

  * @brief Image object.
    */
    Nui_Image_Typedef Img;

} ImageGraphic_Typedef;

/**

* @brief Get image width.
*
* Returns the width of the specified image.
*
* @param[in] image Pointer to image object.
*
* @return Image width in pixels.
  */
  uint16_t NUI_IMAGE_GET_WIDTH(const Nui_Image_Typedef *image);

/**

* @brief Get image height.
*
* Returns the height of the specified image.
*
* @param[in] image Pointer to image object.
*
* @return Image height in pixels.
  */
  uint16_t NUI_IMAGE_GET_HEIGHT(const Nui_Image_Typedef *image);

/**

* @brief Draw an image.
*
* Draws the specified image at the given position
* using the active display driver.
*
* @param[in] ctx Display context.
* @param[in] x Left coordinate.
* @param[in] y Top coordinate.
* @param[in] image Pointer to image object.
*
* @note The image format must be supported by the
* active display driver.
  */
  void NUI_IMAGE_DRAW_IMAGE(void *ctx,int16_t x,int16_t y,const Nui_Image_Typedef *image);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
