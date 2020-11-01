#include "dfpch.h"

#include "Application.h"
#include <stdio.h>
#include "Log.h"

#include <GLFW/glfw3.h>

namespace Drifter {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& e)
	{
		DF_LOG_TRACE("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}

	void Application::Run() {
		DF_LOG_INFO("Welcome to Drifter!");
		
		
		while (m_running) {
			m_window->OnUpdate();
		}
	}
}