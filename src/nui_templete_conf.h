/**

---

* @file    nui_conf.h
* @brief   Templete configuration file for the NUI library.

---

* @attention
*
* Copy this file to nui_conf.h and modify the settings
* according to your project requirements.
*

---

*/

#ifndef __NUI_CONF_H__
#define __NUI_CONF_H__

/**

* @brief Enable widget support.
*
* Set to 1 to include widget-related modules.
  */
  #define NUI_USE_WIDGET             0

/**

* @brief Enable font rendering support.
  */
  #define NUI_USE_FONT               1

/**

* @brief Enable image rendering support.
  */
  #define NUI_USE_IMAGE              1

/**

* @brief Enable geometry drawing support.
  */
  #define NUI_USE_GEOMETRY           0

#if NUI_USE_WIDGET

```
/**
 * @brief Enable Button widget.
 *
 * @note Available only when @ref NUI_USE_WIDGET is enabled.
 */
#define NUI_WDG_USE_BUTTON     1

/**
 * @brief Enable TextBox widget.
 *
 * @note Available only when @ref NUI_USE_WIDGET is enabled.
 */
#define NUI_WDG_USE_TXTBOX     1
```

#endif

/**

* @brief Enable memory resources.
*
* Allows fonts and images to be stored in memory.
  */
  #define NUI_USE_MEMORY             1

/**

* @brief Enable SD card resources.
*
* Allows fonts and images to be loaded from an SD card.
  */
  #define NUI_USE_SD                 1

/**
  * @cond
  */

#if NUI_USE_WIDGET
#include "wdg/inc/nui_wdg_conf.h"
#endif

#include "core/inc/nui_default_conf.h"

/**
  * @endcond
  */

#endif
