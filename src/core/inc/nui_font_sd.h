/**

---

* @file    nui_font_sd.h
* @brief   SD card font implementation.

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

#ifndef __NUI_FONT_SD_H__
#define __NUI_FONT_SD_H__

#include "nui_conf.h"

#if NUI_FONT_USE_SD

#include <stdint.h>
#include <string.h>

#include "nui_font.h"
#include "nui_font_bin.h"
#include "../../sd/nui_sd.h"

#ifdef __cplusplus
extern "C" {
#endif

/**

* @ingroup NUI_Font
* @{
  */

/**

* @brief SD card font descriptor.
*
* This structure stores the information required to access
* a font file located on an SD card.
*
* The font data is loaded on demand during rendering,
* reducing RAM and Flash memory usage.
  */
  typedef struct
  {
  /**

  * @brief Binary font descriptor.
    */
    Nui_Font_Bin_Typedef font;

  /**

  * @brief SD card interface.
    */
    Nui_SD_Typedef sd;

} Nui_Font_SD_Typedef;

/**

* @brief Initialize a font from an SD card.
*
* Opens a font file and prepares it for use by the
* NUI font rendering engine.
*
* @param[out] font Font object to initialize.
* @param[in,out] fontSd SD font descriptor.
* @param[in] pathFile Path to the font file.
*
* @retval true Initialization successful.
* @retval false Failed to open or load font file.
*
* @note The file path depends on where the font file is
* stored on the SD card.
  */
  bool NUI_FONT_SD_INIT(Nui_Font_Typedef *font,Nui_Font_SD_Typedef *fontSd,const uint8_t *pathFile);

/** @} */

#ifdef __cplusplus
}
#endif

#endif

#endif
