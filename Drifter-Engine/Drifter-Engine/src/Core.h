#pragma once
#include <memory>

#ifdef DF_PLATFORM_WINDOWS

#else
#error Drifter only supports Windows
#endif

#define BIT(X) (1 << X)

namespace Drifter {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;
}

#include "Debug/Log.h"
#include "Debug/Assert.h"
