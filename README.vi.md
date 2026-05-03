🌐 Ngôn ngữ:
- [English](README.md)
- Tiếng Việt (hiện tại)
# NUI - Thư viện UI cho hệ thống nhúng
## 📌 Giới thiệu
NUI là một thư viện UI được thiết kế cho hệ thống nhúng, hỗ trợ nhiều loại driver màn hình như SSD1306 và ST7789,...

## ✨ Tính năng
- 🖼️ Hiển thị ảnh (bitmap 1-bit)
- 🔤 Hiển thị font chữ
- 📐 Vẽ hình cơ bản (đường thẳng, hình chữ nhật, v.v.)
- ⚡ Tối ưu cho vi điều khiển có tài nguyên hạn chế
- 🔌 Dễ dàng tích hợp với nhiều loại driver màn hình

## 🧱 Kiến trúc

NUI được tổ chức theo các module:

- `core` - xử lý chính
- `font` - hiển thị văn bản
- `image` - xử lý hình ảnh
- `geometry` - vẽ các hình cơ bản
- `driver` - phần driver từng loại màn hình

## 📂 Cấu trúc thư mục
- NUI/
- ├── nui/
- ├── examples/

## 🚀 Cách sử dụng

### 1. Thêm thư viện
- Thêm `NUI/inc` vào include path
- Thêm `NUI/src` vào source

### 2. Cấu hình
Chỉnh sửa file `nui_conf.h`:

```c
#define NUI_USE_FONT     1
#define NUI_USE_IMAGE    1
#define NUI_USE_GEOMETRY 1

```
### 3. Công cụ chuyển đổi ảnh & font

Để sử dụng ảnh và font với NUI, bạn có thể dùng phần mềm NUI Tool:

👉 Tải tại: [NUI Tool](https://github.com/nam0907/NUI_Tool/releases)

**Tính năng:**
- Chuyển ảnh với các định dạng bitmap 1-bit, RGB565, RGB888 sang mảng C.
- Chuyển font sang mảng C
- Resize và xem trước

## 🖥️ Màn hình hỗ trợ
- SSD1306
- ST7789
- (Sẽ bổ sung thêm...)

## 📸 Ví dụ

### Xem thư mục /examples để tham khảo:

- Hiển thị ảnh
- Hiển thị font
- UI cơ bản