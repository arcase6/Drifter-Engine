#pragma once
#include "dfpch.h"
#include "Platform/Windows/WindowsTime.h"

#include "GLFW/glfw3.h"
namespace Drifter {
	WindowsTime::WindowsTime()
		:m_Time(0.0), m_DeltaTime(0.0), m_Frame(0)
	{
		TickImpl();
		if (m_DeltaTime < 1 / 60.0f) {
			m_DeltaTime = 1 / 60.0f;
		}
	}

	// Inherited via Time

	Timestep WindowsTime::GetDeltaTimeImpl()
	{
		return m_DeltaTime;
	}
	void WindowsTime::TickImpl()
	{
		++m_Frame;
		m_DeltaTime = Timestep(static_cast<float>(glfwGetTime() - m_Time));
		m_Time = glfwGetTime();
	}
}