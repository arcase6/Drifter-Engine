#pragma once
#include "Drifter/Core/Time.h"

#include "GLFW/glfw3.h"
namespace Drifter {
	class WindowsTime : public Time
	{
	private:
		double m_Time;
		Timestep m_DeltaTime;
	public:
		WindowsTime()
			:m_Time(0.0), m_DeltaTime(0.0)
		{
			TickImpl();
			if (m_DeltaTime < 1 / 60.0f) {
				m_DeltaTime = 1 / 60.0f;
			}
		}
	protected:
		// Inherited via Time
		virtual Timestep GetDeltaTimeImpl() override
		{
			return m_DeltaTime;
		}
		virtual double GetTimeImpl() override
		{
			return m_Time;
		}
		virtual void TickImpl() override
		{
			m_DeltaTime = Timestep( static_cast<float>( glfwGetTime() - m_Time ) );
			m_Time = glfwGetTime();
		}
	};

	Time* Time::s_Instance = new WindowsTime();

}