# Font Guide

The Font module allows applications to render text on both monochrome and color displays.

NUI supports two font storage methods:

* **Memory Font** – Font data is compiled into the application.
* **SD Font** – Font data is stored externally and loaded from an SD card.

Both font types are generated using **NUI Tool**.

---

# Font Workflow

The complete workflow is shown below.

```text
TrueType Font (.ttf)
        │
        ▼
     NUI Tool
        │
        ▼
 Generate Font Resource
        │
        ├───────────────┐
        │               │
        ▼               ▼
  Memory Font       SD Card Font
        │               │
        ▼               ▼
  Initialize Font   Initialize Font
        │               │
        └───────┬───────┘
                ▼
          Draw Text
                │
                ▼
         Display Driver
                │
                ▼
             Display
```

Regardless of how the font is stored, the application always uses the same drawing APIs.

---

# Choosing a Font Type

NUI provides two storage methods to suit different embedded systems.

## Memory Font

Memory fonts are compiled directly into the firmware.

Recommended when:

* Flash memory is sufficient.
* The font is used frequently.
* Fast rendering is required.
* No external storage is available.

Advantages:

* Fast access
* Simple deployment
* No SD card required

---

## SD Card Font

SD fonts are stored as binary files on an SD card.

Recommended when:

* Large fonts are required.
* Multiple languages are supported.
* Flash memory is limited.
* Resources need to be updated without rebuilding the firmware.

Advantages:

* Significantly reduces Flash usage.
* Supports very large resource collections.
* Easy to update by replacing files on the SD card.

---

# Generating Fonts

NUI does not read TrueType fonts directly.

Fonts must first be converted using **NUI Tool**.

Typical workflow:

1. Open **NUI Tool**.
2. Select **Font Converter**.
3. Choose a TrueType font.
4. Configure the font size.
5. Select the required Unicode range.
6. Choose the output type.
7. Generate the resource.

The generated files can then be added directly to your project.

For detailed information about the conversion process, see the **NUI Tool Guide**.

---

# Initializing Fonts

Before rendering text, the generated font resource must be initialized.

The initialization process differs slightly between Memory Fonts and SD Fonts, but once initialized, both are used in exactly the same way.

Refer to the API Reference for the available initialization functions and parameters.

---

# Rendering Text

After a font has been initialized, it can be used by the NUI drawing functions.

The Font module converts characters into pixels.

The generated pixels are then passed to the active display driver, which transfers them to the display hardware.

The application does not communicate directly with the display.

```text
Application
      │
      ▼
 Font Module
      │
      ▼
Display Driver
      │
      ▼
 Display
```

---

# Unicode Support

NUI Tool allows only the required Unicode ranges to be generated.

Generating fewer characters reduces the size of the generated font resource and improves memory efficiency.

Choose only the characters required by your application.

---

# Best Practices

* Generate only the required character ranges.
* Use Memory Fonts for frequently displayed text.
* Use SD Fonts for large fonts or multiple languages.
* Reuse initialized font objects instead of creating them repeatedly.
* Keep font sizes appropriate for the target display resolution.

---

# Common Issues

## Text is not displayed

Possible causes include:

* The font has not been initialized.
* The display driver has not been registered.
* The font resource is missing.

---

## Missing Characters

The required Unicode characters were not included during font generation.

Regenerate the font using NUI Tool and include the missing character range.

---

## SD Font Cannot Be Loaded

Verify that:

* The font file exists.
* The file path is correct.
* The SD card has been initialized correctly.

---

# Related Guides

* NUI Tool Guide
* Display Driver Guide
* Image Guide
* Examples
