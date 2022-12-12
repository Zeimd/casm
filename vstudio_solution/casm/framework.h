#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>


#ifdef CASM_DLL_EXPORT
#define CASM_DLL_API __declspec(dllexport)
#else
#define CASM_DLL_API __declspec(dllimport)
#endif