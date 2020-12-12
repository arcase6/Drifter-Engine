#include "Core/dfpch.h"

#include "Application.h"
#include <stdio.h>
#include "Core/Log.h"
#include "Drifter/Input/Input.h"
#include "Drifter/Core/Time.h"

namespace Drifter {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		DF_CORE_ASSERT(!s_Instance, "Application instance already exists!");
		s_Instance = this;

		WindowProps windowProps("Drifter Engine", 720,720);
		m_window = Scope<Window>(Window::Create(windowProps));
		m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}



	Application::~Application() {

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_layerStack.PopLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_layerStack.PopOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}

	void Application::Run() {
		DF_LOG_INFO("Welcome to Drifter!");

		while (m_running) {
			m_window->OnFrameBegin();
			Time::Tick();
			for (Layer* layer : m_layerStack) {
				layer->OnUpdate();
			}
			m_window->OnFrameEnd();
		}
	}
}