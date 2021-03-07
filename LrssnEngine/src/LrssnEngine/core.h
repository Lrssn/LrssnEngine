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

#ifdef LE_DEBUG
    #define LE_ENABLE_ASSERTS
#endif

#ifdef LE_ENABLE_ASSERTS
#define LE_ASSERT(x, ...) { if(!(x)) { LE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define LE_CORE_ASSERT(x, ...) { if(!(x)) { LE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define LE_ASSERT(x, ...)
#define LE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) 