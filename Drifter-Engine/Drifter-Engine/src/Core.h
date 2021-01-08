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

template<class T, class U>
std::enable_if_t<std::is_same_v<std::remove_cv_t<T>, std::remove_cv_t<U>>, bool> CompareSharedPtrs(const std::shared_ptr<T>& a, const std::shared_ptr<U>& b)
{
	if (a == b) return true;
	if (a && b) return *a == *b;
	return false;
}

#include "DebugUtil/Log.h"
#include "DebugUtil/Assert.h"
