# Geometry Guide

The Geometry module provides a collection of basic drawing primitives for creating simple graphical user interfaces.

These primitives can be combined to build custom graphics or used as the foundation for higher-level components such as widgets.

---

# Geometry Workflow

All geometry primitives follow the same rendering process.

```text
Application
        │
        ▼
 Geometry Module
        │
        ▼
 Generate Pixels
        │
        ▼
 Display Driver
        │
        ▼
     Display
```

The application requests a primitive to be drawn.

The Geometry module calculates the required pixels and forwards them to the active display driver.

---

# Supported Primitives

The Geometry module currently provides the following primitives.

* Pixel
* Line
* Rectangle
* Filled Rectangle

Additional primitives may be added in future releases.

Refer to the API Reference for the complete list of available drawing functions.

---

# Coordinate System

NUI uses a standard screen coordinate system.

```text
(0,0)
 ┌────────────────────────────► X
 │
 │
 │
 │
 ▼
 Y
```

* The origin is located at the upper-left corner.
* The X-axis increases from left to right.
* The Y-axis increases from top to bottom.

All geometry functions use this coordinate system.

---

# Drawing Geometry

Geometry primitives are rendered directly through the active display driver.

Unlike images, no external resources are required.

```text
Geometry Function
        │
        ▼
 Generate Pixels
        │
        ▼
 Display Driver
        │
        ▼
 Display
```

This makes geometry drawing suitable for simple graphics such as borders, separators and user interface elements.

---

# Typical Applications

Geometry primitives are commonly used to create:

* Borders
* Frames
* Progress bars
* Simple indicators
* Background areas
* Widget outlines

Many widgets are internally composed of multiple geometry primitives.

---

# Performance

Geometry rendering is generally lightweight because no external resources need to be accessed.

Rendering performance depends mainly on:

* Display resolution
* Display interface
* Driver implementation

---

# Best Practices

* Use geometry primitives for simple graphics.
* Reuse existing primitives instead of creating custom drawing routines.
* Keep drawing operations inside the visible display area.
* Minimize unnecessary redraws to improve performance.

---

# Common Issues

## Nothing Is Displayed

Verify that:

* A display driver has been registered.
* The drawing coordinates are inside the display area.
* The display has been updated after drawing.

---

## Flickering

Frequent full-screen redraws may cause visible flickering.

Update only the regions that have changed whenever possible.

---

# Related Guides

* Display Driver Guide
* Font Guide
* Image Guide
* Widget Guide
* Examples
