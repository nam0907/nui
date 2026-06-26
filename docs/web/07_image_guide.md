# Image Guide

The Image module allows applications to display graphics on monochrome and color displays.

NUI supports two image storage methods:

* **Memory Image** – Image data is compiled into the application.
* **SD Card Image** – Image data is stored externally and loaded from an SD card.

Both image types are generated using **NUI Tool**.

---

# Image Workflow

The complete workflow is shown below.

```text
Image File
(BMP, PNG, JPG, ...)
        │
        ▼
     NUI Tool
        │
        ▼
 Generate Image Resource
        │
        ├───────────────┐
        │               │
        ▼               ▼
 Memory Image      SD Card Image
        │               │
        ▼               ▼
 Initialize Image  Initialize Image
        │               │
        └───────┬───────┘
                ▼
          Draw Image
                │
                ▼
         Display Driver
                │
                ▼
             Display
```

Regardless of how the image is stored, the application always uses the same drawing APIs.

---

# Image Types

NUI provides two storage methods to accommodate different embedded systems.

## Memory Image

Memory images are compiled directly into the application.

Recommended when:

* Images are small.
* Flash memory is sufficient.
* Fast rendering is required.
* No external storage is available.

Advantages:

* Fast access
* No SD card required
* Simple deployment

---

## SD Card Image

SD images are stored externally and loaded when required.

Recommended when:

* Images are large.
* Multiple images are required.
* Flash memory is limited.
* Resources may need to be updated without rebuilding the firmware.

Advantages:

* Reduces Flash usage.
* Suitable for large image collections.
* Easy to replace resources.

---

# Generating Images

NUI does not display standard image formats directly.

Images must first be converted using **NUI Tool**.

Typical workflow:

1. Open **NUI Tool**.
2. Select **Image Converter**.
3. Choose an image file.
4. Configure the output format.
5. Generate the resource.
6. Add the generated resource to your project.

For more information about image conversion, see the **NUI Tool Guide**.

---

# Initializing Images

Before an image can be displayed, it must be initialized.

Initialization differs slightly between Memory Images and SD Images, but after initialization both are used in the same way.

Refer to the API Reference for the available initialization functions.

---

# Displaying Images

After initialization, images can be rendered using the NUI Image module.

The Image module reads the image resource and passes the generated pixel data to the active display driver.

```text
Application
      │
      ▼
 Image Module
      │
      ▼
Display Driver
      │
      ▼
 Display
```

The application never communicates directly with the display hardware.

---

# Choosing an Image Type

Use **Memory Images** when:

* Images are displayed frequently.
* Rendering speed is important.
* Flash memory is sufficient.

Use **SD Images** when:

* Flash memory is limited.
* Images are large.
* Many images are required.
* Resources should be replaceable without updating the firmware.

---

# Best Practices

* Store frequently used icons in Flash memory.
* Store large background images on the SD card.
* Reduce image dimensions whenever possible.
* Reuse initialized image objects.
* Remove unused images to reduce resource usage.

---

# Common Issues

## Image Is Not Displayed

Possible causes include:

* The image has not been initialized.
* The display driver has not been registered.
* The image resource is missing.

---

## Image Colors Are Incorrect

Verify that:

* The image format matches the display driver.
* The resource was generated correctly using NUI Tool.

---

## SD Image Cannot Be Loaded

Verify that:

* The image file exists.
* The file path is correct.
* The SD card has been initialized.

---

# Related Guides

* NUI Tool Guide
* Display Driver Guide
* Font Guide
* Examples
