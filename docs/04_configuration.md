# Configuration

The behavior of the NUI Graphics Library is controlled by **nui_conf.h**.

This file allows you to enable only the modules required by your application, reducing Flash and RAM usage while keeping the library lightweight.

---

# Configuration File

The main configuration file is located at:

```text
src/
├── nui_conf.h
```

The default configuration provided by the library is suitable for most applications.

Users are encouraged to modify **nui_conf.h** according to the requirements of their project.

---

# Module Configuration

NUI is organized into independent modules.

Each module can be enabled or disabled individually.

| Macro              | Description                    |
| ------------------ | ------------------------------ |
| `NUI_USE_FONT`     | Enable font rendering module   |
| `NUI_USE_IMAGE`    | Enable image rendering module  |
| `NUI_USE_GEOMETRY` | Enable geometry drawing module |
| `NUI_USE_WIDGET`   | Enable widget framework        |

Example:

```c
#define NUI_USE_FONT         1
#define NUI_USE_IMAGE        1
#define NUI_USE_GEOMETRY     0
#define NUI_USE_WIDGET       0
```

Only enabled modules are compiled into the application.

---

# Resource Backends

NUI supports multiple resource backends.

| Macro            | Description              |
| ---------------- | ------------------------ |
| `NUI_USE_MEMORY` | Enable memory resources  |
| `NUI_USE_SD`     | Enable SD card resources |

Example:

```c
#define NUI_USE_MEMORY    1
#define NUI_USE_SD        1
```

Memory resources are stored in Flash.

SD resources are loaded from external storage.

---

# Widget Configuration

Widget support can be enabled independently.

```c
#define NUI_USE_WIDGET    1
```

Individual widgets can also be enabled or disabled.

Example:

```c
#define NUI_WDG_USE_BUTTON      1
#define NUI_WDG_USE_TXTBOX      1
```

Only enabled widgets are compiled.

---

# Recommended Configurations

## Small OLED Display

Recommended for monochrome OLED displays with limited Flash memory.

```c
#define NUI_USE_FONT         1
#define NUI_USE_IMAGE        1
#define NUI_USE_GEOMETRY     0
#define NUI_USE_WIDGET       0

#define NUI_USE_MEMORY       1
#define NUI_USE_SD           0
```

---

## TFT Display

Recommended for color TFT displays.

```c
#define NUI_USE_FONT         1
#define NUI_USE_IMAGE        1
#define NUI_USE_GEOMETRY     1
#define NUI_USE_WIDGET       1

#define NUI_USE_MEMORY       1
#define NUI_USE_SD           1
```

---

## Low Memory MCU

Recommended for applications with very limited Flash memory.

```c
#define NUI_USE_FONT         1
#define NUI_USE_IMAGE        0
#define NUI_USE_GEOMETRY     0
#define NUI_USE_WIDGET       0

#define NUI_USE_MEMORY       1
#define NUI_USE_SD           0
```

---

# Tips

* Disable unused modules whenever possible.
* Disable unused widgets to reduce code size.
* Use SD resources for large fonts and images.
* Use memory resources for icons and frequently accessed graphics.

---

# Next Steps

Once the library has been configured, the next step is to implement a display driver.

Continue with the **Display Driver Guide**.
