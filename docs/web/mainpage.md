# NUI Graphics Library

> **Lightweight graphics library for embedded systems**

---

# Introduction

NUI (Nam User Interface) is a lightweight graphics library designed for resource-constrained embedded systems.

The library provides a simple and portable API for drawing graphics on monochrome and color displays while minimizing RAM and Flash usage.

NUI is hardware-independent. All drawing operations are performed through a display driver interface, allowing the same application to run on different display controllers with minimal modifications.

---

# Features

* Lightweight and portable
* Display driver abstraction
* Font rendering

  * Memory Font
  * SD Card Font
* Image rendering

  * Memory Image
  * SD Card Image
* Geometry drawing
* Widget framework

  * Button
  * TextBox
  * CheckBox
* UTF-8 text rendering
* Optimized for embedded systems

---

# Architecture

```text
Application
      │
      ▼
+---------------------------+
|         NUI API           |
+---------------------------+
| Display | Font | Image    |
| Geometry | Widget | Color |
+---------------------------+
|      Display Driver       |
+---------------------------+
|      Display Hardware     |
+---------------------------+
```

---

# Documentation

## User Guide

* [Getting Started](getting_started.md)
* [Installation](installation.md)
* [Configuration](configuration.md)
* [Display Driver](display_driver.md)
* [Font Guide](font.md)
* [Image Guide](image.md)
* [Geometry Guide](geometry.md)
* [Widget Guide](widget.md)
* [Examples](examples.md)
* [FAQ](faq.md)

---

# API Reference

The complete API reference is automatically generated from the source code.

Available modules include:

* Driver
* Display
* Color
* Font
* Image
* Geometry
* Widget

---

# License

Copyright (c) 2026 Nam Pham.

This software is licensed under the terms described in the LICENSE file.
