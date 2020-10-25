#pragma once


#ifdef DF_PLATFORM_WINDOWS
#ifdef DRIFTER_BUILD_DLL
#define DRIFTER_API __declspec(dllexport)
#else
#define DRIFTER_API __declspec(dllimport)
#endif

#else
#error Drifter only supports Windows
#endif

#ifdef DF_ENABLE_ASSERTS
#define DF_ASSERT(x, ...) {if(!(x)){ DF_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define DF_CORE_ASSERT(x, ...) {if(!(x)){ DF_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define DF_ASSERT(x, ...)
#define DF_CORE_ASSERT(x, ...)
#endif

#define BIT(X) (1 << X)