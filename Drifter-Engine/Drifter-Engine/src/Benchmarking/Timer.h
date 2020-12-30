#pragma once
#include <chrono>
namespace Benchmarking {
	struct ProfileResult {
	public:
		const char* Name;
		float Start, End, Duration;
	};

	template<typename Fn>
	class Timer {
	public:
		Timer(const char* name, Fn&& callback)
			:
			m_Name(name),
			m_Callback(callback)
		{
			m_Start = GetTime();
		}

		~Timer() {
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			auto finish = GetTime();
			float duration = (finish - m_Start) * .001f;
			m_Callback({ m_Name, m_Start * .001f, finish * .001f, duration });
		}

	private:
		long long GetTime() {
			return std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()).time_since_epoch().count();
		}

	private:
		const char* m_Name;
		const Fn m_Callback;
		long long m_Start{ 0 };
	};

#define TOKENPASTE2(x, y) x ## y
#define TOKENPASTE(x, y) TOKENPASTE2(x, y)
#define PROFILE_SCOPE(name, list) Benchmarking::Timer TOKENPASTE(timer,__LINE__) (name,[&](Benchmarking::ProfileResult profileResult){list.push_back(profileResult); })
#define PROFILE_FUNCTION(list) PROFILE_SCOPE(__FUNCSIG__, list)

}