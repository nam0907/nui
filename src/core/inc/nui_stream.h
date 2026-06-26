#ifndef __NUI_STREAM_H__
#define __NUI_STREAM_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus // Compatible with C++
extern "C" {
#endif

typedef struct
{
	bool(*read)(void *userData, uint32_t offset, void *buffer, uint32_t Size);
	void *userData;
}Nui_Stream_Typedef;

#ifdef __cplusplus // Compatible with C++
}
#endif

#endif
