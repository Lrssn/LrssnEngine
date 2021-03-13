#pragma once

#include "LrssnEngine/Core/Base.h"
#include "LrssnEngine/Core/Log.h"

#include <filesystem>

#ifdef LE_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define LE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LE##type##ERROR(msg, __VA_ARGS__); LE_DEBUGBREAK(); } }
#define LE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) LE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define LE_INTERNAL_ASSERT_NO_MSG(type, check) LE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", LE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define LE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define LE_INTERNAL_ASSERT_GET_MACRO(...) LE_EXPAND_MACRO( LE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, LE_INTERNAL_ASSERT_WITH_MSG, LE_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define LE_ASSERT(...) LE_EXPAND_MACRO( LE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define LE_CORE_ASSERT(...) LE_EXPAND_MACRO( LE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define LE_ASSERT(...)
#define LE_CORE_ASSERT(...)
#endif