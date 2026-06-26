# Display Driver

The NUI Graphics Library is hardware independent.

Instead of communicating directly with a display controller, NUI uses a display driver interface. This allows the same application code to run on different display controllers without modification.

---

# Driver Architecture

The relationship between the application, NUI and the display driver is illustrated below.

```text
Application
        │
        ▼
NUI Graphics Library
        │
        ▼
Display Driver
        │
        ▼
Display Controller
(ST7789, SSD1306, HUB75, ...)
```

The application communicates only with the NUI API.

The display driver is responsible for transferring drawing operations to the display hardware.

---

# Driver Interface

Every display driver must implement the callbacks defined by **Nui_Driver_Typedef**.

These callbacks provide the communication layer between NUI and the display.

Typical operations include:

* Draw a pixel
* Clear the display
* Clear a display region
* Draw monochrome bitmaps
* Draw color images
* Update the display

---

# Hardware Interface

Before implementing a display driver, the low-level hardware interface must be provided.

These functions are responsible for controlling the display pins and transferring data through the communication peripheral (SPI, QSPI, etc.).

The following example shows the required interface for an ST7789 display.

```c
void ST7789_WRITE_DC(uint8_t value);
void ST7789_WRITE_CS(uint8_t value);
void ST7789_WRITE_RESET(uint8_t value);

void ST7789_SPI_TRANSMIT(const uint8_t *data, uint16_t len);
```

## Description

| Function                | Description                                           |
| ----------------------- | ----------------------------------------------------- |
| `ST7789_WRITE_DC()`     | Controls the Data/Command (DC) pin.                   |
| `ST7789_WRITE_CS()`     | Controls the Chip Select (CS) pin.                    |
| `ST7789_WRITE_RESET()`  | Controls the hardware reset pin.                      |
| `ST7789_SPI_TRANSMIT()` | Sends data to the display through the SPI peripheral. |

An STM32 HAL implementation may look like this:

```c
void ST7789_WRITE_DC(uint8_t value)
{
    HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void ST7789_WRITE_CS(uint8_t value)
{
    HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void ST7789_WRITE_RESET(uint8_t value)
{
    HAL_GPIO_WritePin(RST_GPIO_Port,RST_Pin,value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void ST7789_SPI_TRANSMIT(const uint8_t *data,uint16_t len)
{
    HAL_SPI_Transmit(&hspi2,data,len,100);
}
```

> **Note**
>
> The implementation shown above uses the STM32 HAL library.
> If another platform or SDK is used, these functions should be implemented using the corresponding GPIO and SPI APIs provided by that platform.


# Register a Driver

After initializing the hardware, register the driver before calling any drawing function.

Example:

```c
NUI_REGISTER_Driver(&st7789_driver);
```

Once the driver has been registered, all NUI drawing APIs automatically use the active display driver.

---

# Driver Context

Most callbacks receive a context pointer.

```c
void *ctx
```

The context is provided by the application and may contain any information required by the driver.

Typical examples include:

* SPI handle
* Display object
* Frame buffer
* DMA configuration
* User-defined driver data

NUI does not interpret the context object. It is passed directly to the display driver.

---

# Minimal Driver

A minimal driver typically implements:

* Set Pixel
* Clear Display
* Update Display

Additional callbacks can be implemented to improve performance.

---

# Example Driver

The following example uses an **ST7789** TFT display.

The driver implements all callbacks required by **Nui_Driver_Typedef** and communicates with the display through SPI.

Initialization:

```c

Nui_Driver_Typedef st7789_drv;
ST7789_Typedef ST7789;

ST7789.SPITransmit=ST7789_SPI_TRANSMIT;
ST7789.WriteDC=ST7789_WRITE_DC;
ST7789.WriteCS=ST7789_WRITE_CS;
ST7789.Delay=ST7789_DELAY;
ST7789.WriteReset=ST7789_WRITE_RESET;

st7789_drv.set_px=ST7789_SET_PX;
st7789_drv.blit_color=ST7789_BLIT_COLOR;
st7789_drv.clear_window=ST7789_CLEAR_WINDOW;
st7789_drv.clear=ST7789_CLEAR;
st7789_drv.blit_mono=ST7789_BLIT_MONO;

NUI_REGISTER_Driver(&st7789_drv);

ST7789_INIT(&ST7789);
```

The application can then draw graphics normally.

```c
NUI_DISP_CLEAR(ctx, NUI_COLOR_BLACK);

NUI_FONT_DRAW_STRING(ctx,10,10(uint8_t *)"Hello NUI",&font,NUI_COLOR_WHITE,NUI_COLOR_BLACK);

NUI_DISP_UPDATE(ctx);
```

---

# Performance

For monochrome displays, drawing operations are usually transferred directly.

The driver implementation determines the transfer method.

---

# Driver Repository

This document provides only a basic overview of the display driver interface.

Complete driver implementations for various display controllers are maintained in a separate repository.

Available drivers include examples for different display controllers and communication interfaces.

Refer to the driver repository for the latest implementations and updates.

---

# Best Practices

* Keep the driver independent from the application.
* Implement bitmap callbacks whenever possible.
* Store hardware-specific code inside the driver.
* Keep the application portable by using only the NUI API.

---

# Next Steps

After a display driver has been registered, continue with:

* Font Guide
* Image Guide

These guides explain how to render fonts and images using the NUI Graphics Library.
