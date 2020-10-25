#include "dfpch.h"

#include "Application.h"
#include <stdio.h>
#include "Log.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Drifter {
	Application::Application() {
		m_window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {
		DF_LOG_INFO("Welcome to Drifter!");
		
		
		while (m_running) {
			m_window->OnUpdate();
		}
	}
}