#include "../inc/nui_binary_reader.h"

uint32_t NUI_BINARY_READER_UINT32(const uint8_t *buf)
{
	return ((uint32_t)buf[0]) | ((uint32_t)buf[1]<<8) | ((uint32_t)buf[2]<<16) | ((uint32_t)buf[3]<<24);
}

uint16_t NUI_BINARY_READER_UINT16(const uint8_t *buf)
{
	return ((uint16_t)buf[0]) | ((uint16_t)buf[1]<<8);
}
