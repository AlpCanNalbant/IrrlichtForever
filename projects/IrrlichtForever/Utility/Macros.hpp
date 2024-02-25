// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once

#if defined(_DEBUG) || !defined(NDEBUG)
#define IRR_FOREVER_DEBUG
#endif

#if defined(IRR_FOREVER_DEBUG)
#include <assert.h>
#define IRR_FOREVER_ASSERT_IF(...) assert(!(__VA_ARGS__))
#else
#define IRR_FOREVER_ASSERT_IF(...)
#endif

#if defined(WIN64) || defined(_WIN64) || defined(WIN32) || defined(_WIN32)
#define IRR_FOREVER_WINDOWS
#endif
