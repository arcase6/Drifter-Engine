#pragma once

#include "Core/Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include <Drifter/LayerStack.h>

namespace Drifter {
	class Application
	{
	public:
		Application();

		~Application();

		void Run();


		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		static inline Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		Scope<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;

	private:
		static Application* s_Instance;

	};

	Application* CreateApplication();
}

