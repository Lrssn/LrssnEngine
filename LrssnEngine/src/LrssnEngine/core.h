#pragma once

#ifdef LE_PLATFORM_WINDOWS
    #ifdef  LE_BUILD_DLL
        #define LrssnEngine_API __declspec(dllexport)
    #else
        #define LrssnEngine_API __declspec(dllimport)
    #endif
#else
    #error LrssnEngine only supports windows!
#endif

#define BIT(x) (1 << x)