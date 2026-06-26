/**

---

* @file    nui_color.h
* @brief   Color definitions for the NUI graphics library.

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

#ifndef __NUI_COLOR_H__
#define __NUI_COLOR_H__

/**

* @defgroup NUI_Color Color
* @brief Predefined color definitions.
*
* This module provides a collection of predefined
* colors that can be used throughout the NUI
* graphics library.
*
* Colors are stored in 24-bit RGB888 format:
*
* @code
* 0x00RRGGBB
* @endcode
*
* @{
  */

/* =========================================================================

* Basic Colors
* ========================================================================= */

/** @brief Black color */
#define NUI_COLOR_BLACK                0x00000000

/** @brief White color */
#define NUI_COLOR_WHITE                0x00FFFFFF

/** @brief Red color */
#define NUI_COLOR_RED                  0x00FF0000

/** @brief Green color */
#define NUI_COLOR_GREEN                0x00008000

/** @brief Lime color */
#define NUI_COLOR_LIME                 0x0000FF00

/** @brief Blue color */
#define NUI_COLOR_BLUE                 0x000000FF

/** @brief Yellow color */
#define NUI_COLOR_YELLOW               0x00FFFF00

/** @brief Cyan color */
#define NUI_COLOR_CYAN                 0x0000FFFF

/** @brief Magenta color */
#define NUI_COLOR_MAGENTA              0x00FF00FF

/* =========================================================================

* Gray Scale
* ========================================================================= */

/** @brief Silver color */
#define NUI_COLOR_SILVER               0x00C0C0C0

/** @brief Gray color */
#define NUI_COLOR_GRAY                 0x00808080

/** @brief Dark gray color */
#define NUI_COLOR_DARKGRAY             0x00404040

/** @brief Light gray color */
#define NUI_COLOR_LIGHTGRAY            0x00D3D3D3

/** @brief White smoke color */
#define NUI_COLOR_WHITESMOKE           0x00F5F5F5

/* =========================================================================

* Dark Colors
* ========================================================================= */

/** @brief Navy color */
#define NUI_COLOR_NAVY                 0x00000080

/** @brief Maroon color */
#define NUI_COLOR_MAROON               0x00800000

/** @brief Olive color */
#define NUI_COLOR_OLIVE                0x00808000

/** @brief Purple color */
#define NUI_COLOR_PURPLE               0x00800080

/** @brief Teal color */
#define NUI_COLOR_TEAL                 0x00008080

/* =========================================================================

* UI Colors (Modern UI)
* ========================================================================= */

/** @brief Orange color */
#define NUI_COLOR_ORANGE               0x00FFA500

/** @brief Deep orange color */
#define NUI_COLOR_DEEPORANGE           0x00FF5722

/** @brief Gold color */
#define NUI_COLOR_GOLD                 0x00FFD700

/** @brief Pink color */
#define NUI_COLOR_PINK                 0x00FFC0CB

/** @brief Hot pink color */
#define NUI_COLOR_HOTPINK              0x00FF69B4

/** @brief Sky blue color */
#define NUI_COLOR_SKYBLUE              0x0087CEEB

/** @brief Deep sky blue color */
#define NUI_COLOR_DEEPSKYBLUE          0x0000BFFF

/** @brief Dodger blue color */
#define NUI_COLOR_DODGERBLUE           0x001E90FF

/** @brief Turquoise color */
#define NUI_COLOR_TURQUOISE            0x0040E0D0

/** @brief Aqua color */
#define NUI_COLOR_AQUA                 0x0000FFFF

/** @brief Indigo color */
#define NUI_COLOR_INDIGO               0x004B0082

/** @brief Violet color */
#define NUI_COLOR_VIOLET               0x00EE82EE

/** @brief Brown color */
#define NUI_COLOR_BROWN                0x00A52A2A

/** @brief Chocolate color */
#define NUI_COLOR_CHOCOLATE            0x00D2691E

/** @} */

#endif
