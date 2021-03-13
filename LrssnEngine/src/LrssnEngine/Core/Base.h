#pragma once

#include <memory>
#include "LrssnEngine/Core/PlatformDetection.h"


#ifdef LE_DEBUG
    #if defined(LE_PLATFORM_WINDOWS)
        #define LE_DEBUGBREAK() __debugbreak()
    #elif defined(LE_PLATFORM_LINUX)
        #include <signal.h>
        #define LE_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define LE_ENABLE_ASSERTS
#else
    #define LE_DEBUGBREAK()
#endif

#define LE_EXPAND_MACRO(x) x
#define LE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define LE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace LrssnEngine {
    //scopes
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args) 	{
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    //refs
    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args) 	{
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#include "LrssnEngine/Core/Log.h"
#include "LrssnEngine/Core/Assert.h"