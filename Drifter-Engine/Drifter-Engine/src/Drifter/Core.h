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

#define BIT(X) (1 << X)