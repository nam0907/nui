#ifndef __NUI_BINARY_READER_H__
#define __NUI_BINARY_READER_H__

#include <stdint.h>

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

uint32_t NUI_BINARY_READER_UINT32(const uint8_t *buf);
uint16_t NUI_BINARY_READER_UINT16(const uint8_t *buf);

#ifdef __cplusplus // Compatible with C++
}
#endif

#endif
