#pragma once
#ifndef _IUNKNOWN_DEFINED
typedef struct IUnknown IUnknown;
#define _IUNKNOWN_DEFINED
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifdef _HAS_STD_BYTE
#undef _HAS_STD_BYTE
#endif
#include <Windows.h>
