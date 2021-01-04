#include "dfpch.h"

#include "Application.h"
#include "Core/Log.h"
#include "Drifter/Input/Input.h"
#include "Drifter/Core/Time.h"

#include "Drifter/Events/ApplicationEvent.h"
#include "Drifter/Events/KeyEvent.h"
#include "Drifter/Events/MouseEvent.h"

#include "Drifter/Renderer/Renderer.h"
#include "Debug/Instrumentation.h"

#include <fmt/core.h>

namespace Drifter {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		//DF_CORE_ASSERT(!s_Instance);
		DF_CORE_ASSERT(!s_Instance, "Application instance already exists!");
		s_Instance = this;

		WindowProps windowProps("Drifter Engine", 720,720);
		m_window = Scope<Window>(Window::Create(windowProps));
		m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();
		Renderer::SetClearColor({ 0.0f, 0.0f, 0.05f, 1.0f });
		m_ImguiLayer = std::make_shared<EditorUI::ImguiLayer>();
		PushOverlay(m_ImguiLayer);

	}

	void Application::Run() {
		DF_LOG_INFO("Welcome to Drifter!");

		while (m_running) {
			PROFILE_SCOPE("One Frame");
			m_window->OnFrameBegin();
			UpdateLayers();

			UpdateImgui();

			m_window->OnFrameEnd();
			if (Instrumentor::HasActiveSession()) {
				Instrumentor::GetActiveSession()->FlushLog();
			}
		}
		Renderer::Shutdown();
	}

	void Application::UpdateLayers()
	{
		Time::Tick();
		PROFILE_FUNCTION();
		if (!m_IsMinimized) {
			for (Ref<Layer> layer : m_layerStack)
				layer->OnUpdate();
		}
	}

	void Application::UpdateImgui()
	{
		PROFILE_FUNCTION();
		m_ImguiLayer->NewFrameGLFW();
		for (Ref<Layer> layer : m_layerStack)
			layer->OnImgui();
		m_ImguiLayer->EndFrameGLFW();
	}


	void Application::OnEvent(Event& e)
	{
		PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
#if DF_PROFILE_LEVEL >= DF_PROFILE_LEVEL_BASIC
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(HandleProfileCallback));
#endif
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Ref<Layer> layer)
	{
		m_layerStack.PushLayer(layer);
	}

	void Application::PopLayer(Ref<Layer> layer)
	{
		m_layerStack.PopLayer(layer);
	}

	void Application::PushOverlay(Ref<Layer> overlay)
	{
		m_layerStack.PushOverlay(overlay);
	}

	void Application::PopOverlay(Ref<Layer> overlay)
	{
		m_layerStack.PopOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_IsMinimized = e.GetWidth() == 0 || e.GetHeight() == 0;
		if (!m_IsMinimized) {
			Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		}

		return false;
	}

	bool Application::HandleProfileCallback(KeyPressedEvent& e)
	{
		static int sessionID = 1;
		if (e.GetKeyCode() == KeyCodes::PERIOD()) {
			if (Instrumentor::HasActiveSession() == false) {
				std::string file = fmt::format("Session_{0}_Frame_{1}.json", sessionID++, Time::GetFrame());
				DF_LOG_INFO("Starting Profile Session: ", file);
				BEGIN_PROFILING_SESSION(file);
			}
			else {
				END_PROFILING_SESSION();
			}
			return true;
		}

		return false;
	}
}