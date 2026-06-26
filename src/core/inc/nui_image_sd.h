/**

---

* @file    nui_image_sd.h
* @brief   SD card image implementation.

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

#ifndef __NUI_IMAGE_SD_H__
#define __NUI_IMAGE_SD_H__

#include "nui_conf.h"

#if NUI_IMAGE_USE_SD

#include <stdint.h>
#include <string.h>

#include "nui_image.h"
#include "nui_image_bin.h"
#include "../../sd/nui_sd.h"

#ifdef __cplusplus
extern "C" {
#endif

/**

* @ingroup NUI_Image
* @{
  */

/**

* @brief Maximum image path length.
*
* Defines the maximum number of characters
* allowed in an image file path.
  */
  #define NUI_IMAGE_PATH_MAX_SIZE       50

/**

* @brief Image header size.
*
* Specifies the size of the binary image
* header stored in image files.
  */
  #define NUI_IMAGE_HEADER_SIZE         26

/**

* @brief SD card image descriptor.
*
* This structure contains the information
* required to access an image stored on
* an SD card.
*
* Image data is loaded on demand during
* rendering, reducing Flash memory usage.
  */
  typedef struct
  {
  /**

  * @brief Binary image descriptor.
  *
  * Stores image metadata and file access
  * information.
    */
    Nui_Image_Bin_Typedef img;

  /**

  * @brief SD card interface.
  *
  * Used to access image data from the
  * storage device.
    */
    Nui_SD_Typedef sd;

} Nui_Image_SD_Typedef;

/**

* @brief Initialize an image from an SD card.
*
* Opens an image file and prepares it for
* rendering through the NUI image interface.
*
* @param[out] img Image object to initialize.
* @param[in,out] imgSD SD image descriptor.
* @param[in] pathFile Path to the image file.
*
* @retval true Image initialized successfully.
* @retval false Failed to open or load image file.
*
* @note The file path depends on the location
* of the image on the SD card.
  */
  bool NUI_IMAGE_SD_INIT(Nui_Image_Typedef *img,Nui_Image_SD_Typedef *imgSD,const uint8_t *pathFile);

/** @} */

#ifdef __cplusplus
}
#endif

#endif

#endif
