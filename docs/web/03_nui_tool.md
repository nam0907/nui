# NUI Tool

NUI Tool is the official resource generation utility for the **NUI Graphics Library**.

It converts fonts and images into formats that can be used directly by NUI, eliminating the need for manual resource conversion.

---

# Overview

NUI Tool provides an easy way to generate resources for embedded applications.

Currently, the tool supports:

* Font Converter
* Image Converter

Both resources can be generated for:

* Memory
* SD Card

---

# Typical Workflow

The recommended workflow is shown below.

```text
Select Resource
        │
        ▼
Configure Options
        │
        ▼
Generate Resource
        │
        ▼
Add Resource to Project
        │
        ▼
Initialize Resource
        │
        ▼
Use in Application
```

---

# Font Converter

The Font Converter converts TrueType fonts into the internal NUI font format.

Typical workflow:

1. Open **NUI Tool**.
2. Select **Font Converter**.
3. Choose a TrueType font.
4. Configure the font size.
5. Select the desired Unicode range.
6. Choose the output type.
7. Generate the resource.

The generated resource can then be added directly to your project.

For more information about font rendering, see the **Font Guide**.

---

# Image Converter

The Image Converter converts standard image files into the NUI image format.

Typical workflow:

1. Open **NUI Tool**.
2. Select **Image Converter**.
3. Choose an image.
4. Configure the output format.
5. Generate the resource.

The generated image can be rendered immediately using the NUI Image module.

For more information about image rendering, see the **Image Guide**.

---

# Output Types

NUI Tool supports two output types.

## Memory Resource

Memory resources are compiled directly into the application.

The generated source files contain:

* Resource data arrays
* Predefined resource structures
* Ready-to-use initialization examples

For fonts, the generated code includes a memory font descriptor and an example of using:

```c
NUI_FONT_MEM_INIT(...)
```

For images, the generated code includes a memory image descriptor and an example of using:

```c
NUI_IMAGE_MEM_INIT(...)
```

Memory resources are recommended for:

* Icons
* Small images
* Frequently used fonts
* Applications without external storage

---

## SD Card Resource

SD resources are intended to be stored on an SD card.

The generated output contains:

* Binary resource file (`*.bin`)
* Ready-to-use initialization example

For fonts:

```c
NUI_FONT_SD_INIT(...)
```

For images:

```c
NUI_IMAGE_SD_INIT(...)
```

The path supplied to the initialization function depends on where the binary resource is stored on the SD card.

SD resources are recommended for:

* Large fonts
* Large image collections
* Applications with limited Flash memory
* Multi-language projects

---

# Add Resources to Your Project

## Memory Resources

Copy the generated source files into your project and compile them together with the application.

The generated initialization example can be used directly without modification.

---

## SD Card Resources

Copy the generated binary files to the SD card.

Initialize the resource using the generated example code.

Make sure the file path matches the actual location of the resource on the SD card.

---

# Best Practices

* Store frequently used resources in Flash memory.
* Store large resources on an SD card to reduce Flash usage.
* Generate only the required Unicode ranges to minimize font size.
* Keep image dimensions as small as practical for embedded displays.
* Organize generated resources into separate folders such as **Fonts** and **Images**.

---

# Next Steps

Continue with the following guides:

* Configuration Guide
* Display Driver Guide
* Font Guide
* Image Guide

These guides explain how to use the generated resources within the NUI Graphics Library.
