# Installation

This guide explains how to integrate the **NUI Library** into your project.

The installation procedure is independent of the target MCU and display driver. Once the library has been added correctly, the same application code can be reused on different hardware platforms.

---

# Requirements

Before installing NUI, make sure your development environment meets the following requirements.

* C99 compatible compiler
* Standard C library
* A supported display driver
* Doxygen (optional, for documentation generation)
* NUI Tool (recommended for font and image generation)

---

# Library Structure

A typical NUI library directory is shown below.

```text
Library Structure

The NUI library is organized into several modules. Each module provides a specific set of functionality and can be enabled or disabled through nui_conf.h.

A typical directory structure is shown below.

Nui_lib
│
├── docs/                  Documentation
│
├── Example/               Example projects
│
├── src/
│   │
│   ├── nui.h              Main library header
│   ├── nui_conf.h         Library configuration
│   ├── nui_template_conf.h
│   │
│   ├── align/             Alignment utilities
│   │
│   ├── core/
│   │   ├── inc/
│   │   │   ├── nui_port.h
│   │   │   ├── nui_disp.h
│   │   │   ├── nui_color.h
│   │   │   ├── nui_font.h
│   │   │   ├── nui_image.h
│   │   │   ├── nui_geometry.h
│   │   │   └── ...
│   │   │
│   │   └── src/
│   │
│   ├── sd/                SD card interface
│   │
│   ├── int/               Internal implementation
│   │
│   └── wdg/
│       ├── inc/
│       │   ├── nui_wdg.h
│       │   ├── nui_wdg_button.h
│       │   ├── nui_wdg_txtbox.h
│       │   ├── nui_wdg_checkbox.h
│       │   └── ...
│       │
│       └── src/
│
├── README.md
└── README.vi.md
```

Only **nui.h** should normally be included by the application.

```c
#include "nui.h"
```

---

# Copy the Library

Copy the entire **NUI** folder into your project folder.

Example:

```text
Project
│
├── Application
├── Drivers
├── NUI
└── main.c
```

It is recommended to keep the original directory structure unchanged.

---

# Configure Include Paths

Your compiler must be able to locate **nui.h**.

The recommended include path is the root directory of the library.

Example:

```text
<Project>/NUI
```

Avoid adding individual subdirectories whenever possible.

---

# IDE Configuration

The procedure depends on your development environment.

## Keil MDK

1. Open **Options for Target**.
2. Select the **C/C++** tab.
3. Add the NUI root directory to **Include Paths**.

Example:

```text
..\NUI
```

---

## STM32CubeIDE

1. Open **Project Properties**.
2. Navigate to:

```text
C/C++
    ↓
Includes
```

3. Add the NUI root directory.

---

## PlatformIO

Copy the library into:

```text
lib/
    NUI/
```

PlatformIO automatically detects the library.

---

## ESP-IDF

Copy the library into:

```text
components/
    NUI/
```

or add it as an external component.

---

## GCC / Makefile

Add the include directory.

Example:

```make
-I./NUI
```

Also make sure all required source files are compiled.

---

## CMake

Example:

```cmake
target_include_directories(
    app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/NUI
)
```

---

# Add Source Files

The compiler must compile all required source files.

At minimum, include the following modules:

* core
* font (optional)
* image (optional)
* geometry (optional)
* widget (optional)

Only compile the modules enabled in **nui_conf.h**.

---

# Verify the Installation

Create a simple application.

```c
#include "nui.h"
```

If the project compiles successfully, the library has been installed correctly.

Next, register a display driver and draw your first graphics as described in the **Getting Started** guide.

---

# Common Issues

## Cannot find "nui.h"

Verify that the compiler include path contains the NUI root directory.

---

## Undefined Reference

Make sure the corresponding source files are compiled.

---

## Missing Modules

Verify that the required modules are enabled in **nui_conf.h**.

---

# Next Steps

Continue with the following guides:

* NUI Tool
* Configuration
* Display Driver

These guides explain how to configure the library, generate resources and implement a display driver.
