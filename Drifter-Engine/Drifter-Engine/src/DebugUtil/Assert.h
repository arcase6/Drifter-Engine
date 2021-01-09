#pragma once
#include "DebugUtil/internal/DebugAssert.h"

#include "DebugUtil/Log.h"
#include "Drifter/Core/Format.h"

namespace Drifter {
	//global assert level define
	const static debug_assert::level AssertLevel = debug_assert::level<1>{};

	namespace detail {
		struct StandardAssertHandler {
			static void handle(unsigned level, const debug_assert::source_location& loc, const char* expression,
				const char* message = nullptr) noexcept
			{
				std::string consoleMessage;
				if (*expression == '\0')
				{
					if (message)
						consoleMessage = fmt::format("{0} ( line {1} ): Unreachable Code Reached : {3}", loc.file_name, loc.line_number, message);
					else
						consoleMessage = fmt::format("{0} ( line {1} ): Unreachable Code Reached", loc.file_name, loc.line_number, message);
				}
				else {
					if (message)
						consoleMessage = fmt::format("{0} ( line {1} ): lv. {4} Assertion failed ({2}): {3}",
							loc.file_name, loc.line_number, expression, message, level);
					else
						consoleMessage = fmt::format("{0} ( line {1} ): lv. {3} Assertion failed ({2})",
							loc.file_name, loc.line_number, expression, level);
				}
				DF_LOG_ERROR(consoleMessage);
				__debugbreak();
			}
		};

		struct AssertDebugLevel0
			: StandardAssertHandler,
			debug_assert::set_level<0> // level 1, i.e. all assertions, 0 would mean none, 1 would be level 1, 2 level 2 or lower,...
		{};

		struct AssertDebugLevel1
			: StandardAssertHandler,
			debug_assert::set_level<1> // level 1, i.e. all assertions, 0 would mean none, 1 would be level 1, 2 level 2 or lower,...
		{};

		struct AssertDebugLevel2
			: StandardAssertHandler,
			debug_assert::set_level<2> // level 2, i.e. all assertions, 0 would mean none, 1 would be level 1, 2 level 2 or lower,...
		{};

		struct AssertDebugLevel3
			: StandardAssertHandler,
			debug_assert::set_level<3> // level 3, i.e. all assertions, 0 would mean none, 1 would be level 1, 2 level 2 or lower,...
		{};

		struct CoreAssertHandler {
			static void handle(unsigned level, const debug_assert::source_location& loc, const char* expression,
				const char* message = nullptr) noexcept
			{
				std::string consoleMessage;
				if (*expression == '\0')
				{
					if (message)
						consoleMessage = fmt::format("{0} ( line {1} ): Unreachable Code Reached : {3}", loc.file_name, loc.line_number, message);
					else
						consoleMessage = fmt::format("{0} ( line {1} ): Unreachable Code Reached", loc.file_name, loc.line_number, message);
				}
				else {
					if (message)
						consoleMessage = fmt::format("{0} ( line {1} ): lv. {4} Assertion failed ({2}): {3}",
							loc.file_name, loc.line_number, expression, message, level);
					else
						consoleMessage = fmt::format("{0} ( line {1} ): lv. {3} Assertion failed ({2})",
							loc.file_name, loc.line_number, expression, level);
				}
				DF_CORE_ERROR(consoleMessage);
				__debugbreak();
			}
		};

		struct CoreAssertDebugLevel0
			: CoreAssertHandler,
			debug_assert::set_level<0> // level 1, i.e. all assertions, 0 would mean none, 1 would be level 1, 2 level 2 or lower,...
		{};

		struct CoreAssertDebugLevel1
			: CoreAssertHandler,
			debug_assert::set_level<1> // level 1, i.e. all assertions, 0 would mean none, 1 would be level 1, 2 level 2 or lower,...
		{};

		struct CoreAssertDebugLevel2
			: CoreAssertHandler,
			debug_assert::set_level<2> // level 2, i.e. all assertions, 0 would mean none, 1 would be level 1, 2 level 2 or lower,...
		{};

		struct CoreAssertDebugLevel3
			: CoreAssertHandler,
			debug_assert::set_level<3> // level 3, i.e. all assertions, 0 would mean none, 1 would be level 1, 2 level 2 or lower,...
		{};

	}
}

//macro definitions

#define DF_ASSERT_LV0(Expr, ...)  DEBUG_ASSERT(Expr, ::Drifter::detail::AssertDebugLevel0{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_ASSERT_LV1(Expr, ...)  DEBUG_ASSERT(Expr, ::Drifter::detail::AssertDebugLevel1{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_ASSERT_LV2(Expr, ...)  DEBUG_ASSERT(Expr, ::Drifter::detail::AssertDebugLevel2{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_ASSERT_LV3(Expr, ...)  DEBUG_ASSERT(Expr, ::Drifter::detail::AssertDebugLevel3{}, ::Drifter::AssertLevel, __VA_ARGS__);

#define DF_CORE_ASSERT_LV0(Expr, ...)  DEBUG_ASSERT(Expr, ::Drifter::detail::CoreAssertDebugLevel0{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_CORE_ASSERT_LV1(Expr, ...)  DEBUG_ASSERT(Expr, ::Drifter::detail::CoreAssertDebugLevel1{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_CORE_ASSERT_LV2(Expr, ...)  DEBUG_ASSERT(Expr, ::Drifter::detail::CoreAssertDebugLevel2{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_CORE_ASSERT_LV3(Expr, ...)  DEBUG_ASSERT(Expr, ::Drifter::detail::CoreAssertDebugLevel3{}, ::Drifter::AssertLevel, __VA_ARGS__);

#define DF_ASSERT_UNREACHABLE_LV0(...)  DEBUG_UNREACHABLE(::Drifter::detail::AssertDebugLevel0{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_ASSERT_UNREACHABLE_LV1(...)  DEBUG_UNREACHABLE(::Drifter::detail::AssertDebugLevel1{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_ASSERT_UNREACHABLE_LV2(...)  DEBUG_UNREACHABLE(::Drifter::detail::AssertDebugLevel2{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_ASSERT_UNREACHABLE_LV3(...)  DEBUG_UNREACHABLE(::Drifter::detail::AssertDebugLevel3{}, ::Drifter::AssertLevel, __VA_ARGS__);

#define DF_CORE_ASSERT_UNREACHABLE_LV0(...)  DEBUG_UNREACHABLE(::Drifter::detail::CoreAssertDebugLevel0{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_CORE_ASSERT_UNREACHABLE_LV1(...)  DEBUG_UNREACHABLE(::Drifter::detail::CoreAssertDebugLevel1{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_CORE_ASSERT_UNREACHABLE_LV2(...)  DEBUG_UNREACHABLE(::Drifter::detail::CoreAssertDebugLevel2{}, ::Drifter::AssertLevel, __VA_ARGS__);
#define DF_CORE_ASSERT_UNREACHABLE_LV3(...)  DEBUG_UNREACHABLE(::Drifter::detail::CoreAssertDebugLevel3{}, ::Drifter::AssertLevel, __VA_ARGS__);

