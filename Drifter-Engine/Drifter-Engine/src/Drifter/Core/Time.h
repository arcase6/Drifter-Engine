#pragma once
#include "Drifter/Application.h"

namespace Drifter {
	class Timestep
	{
	public:
		Timestep(float timeSeconds)
			:m_Time(timeSeconds)
		{ }

		operator float() const { return m_Time; }
		inline float TimeMilliseconds() {return m_Time * 1000;}
		inline float TimeSeconds(){ return m_Time; }

		inline float ToFrames30FPS(){ return m_Time / 30; }
		inline float ToFrames60FPS(){ return m_Time / 60; }
	private:
		float m_Time;
	};

	class Time
	{
	protected:
		Time() = default;
	public:
		Time(Time& time) = delete;
		Time& operator=(Time& time) = delete;

		inline static Timestep GetDeltaTime() { return s_Instance->GetDeltaTimeImpl(); }
		inline static double GetTime() { return s_Instance->GetTimeImpl(); }
		inline static void Tick() { s_Instance->TickImpl(); }

	protected:
		virtual Timestep GetDeltaTimeImpl() = 0;
		virtual double GetTimeImpl() = 0;
		virtual void TickImpl() = 0;
	private:
		static Time* s_Instance;

		friend class Application;
	};
}