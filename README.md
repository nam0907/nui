🌐 Language:
- English (current)
- [Tiếng Việt](README_vi.md)
- [Documention](docs/web/html/index.html)
# NUI - Lightweight Embedded UI Library

## 📌 Introduction
NUI is a lightweight UI library designed for embedded systems, supporting multiple display drivers such as SSD1306 and ST7789.

## ✨ Features
- 🖼️ Image rendering (1-bit, bitmap)
- 🔤 Font rendering
- 📐 Basic geometry (line, rectangle, etc.)
- ⚡ Optimized for low-resource MCUs
- 🔌 Easy integration with multiple display drivers

## 🧱 Architecture
NUI is structured into modular components:
- `core` - main logic
- `font` - text rendering
- `image` - image processing
- `geometry` - drawing primitives
- `driver` - display-specific implementations

## 📂 Project Structure
- NUI/
- ├── nui/
- ├── examples/

## 🚀 Getting Started

### 1. Include library
- Add `NUI/inc` to include path
- Add `NUI/src` to source

### 2. Configuration
Edit `nui_conf.h`:

```c
#define NUI_USE_FONT     1
#define NUI_USE_IMAGE    1
#define NUI_USE_GEOMETRY 1

```

### 3. Convert Image & Font Tool

To use images and fonts with NUI, you can use the NUI Tool:

👉 Download here: [NUI Tool](https://github.com/nam0907/NUI_Tool/releases)

**Features:**
- Convert image with format 1-bit bitmap, RGB565, RGB88 to C array
- Convert font to C array
- Resize and preview

---

## 🖥️ Supported Displays
- SSD1306
- ST7789
- (More coming...)

## 📸 Examples

### Check /examples folder for:

- Image rendering
- Font display
- Basic UI