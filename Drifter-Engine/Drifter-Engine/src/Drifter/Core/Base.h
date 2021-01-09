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

	template <typename T, typename ... Args >
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<class T, class U>
	std::enable_if_t<std::is_same_v<std::remove_cv_t<T>, std::remove_cv_t<U>>, bool> CompareRefs(const Ref<T>& a, const Ref<U>& b)
	{
		if (a == b) return true;
		if (a && b) return *a == *b;
		return false;
	}
}
