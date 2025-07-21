#pragma once

#include "Reagent/Log.h"
#include <filesystem>

#ifdef RG_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define RG_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { RG##type##ERROR(msg, __VA_ARGS__); RG_DEBUGBREAK(); } }
#define RG_INTERNAL_ASSERT_WITH_MSG(type, check, ...) RG_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define RG_INTERNAL_ASSERT_NO_MSG(type, check) RG_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", RG_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define RG_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define RG_INTERNAL_ASSERT_GET_MACRO(...) RG_EXPAND_MACRO( RG_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, RG_INTERNAL_ASSERT_WITH_MSG, RG_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define RG_ASSERT(...) RG_EXPAND_MACRO( RG_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define RG_CORE_ASSERT(...) RG_EXPAND_MACRO( RG_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define RG_ASSERT(...)
#define RG_CORE_ASSERT(...)
#endif