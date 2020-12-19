#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include <Drifter/LayerStack.h>

namespace Drifter {
	class Application
	{
	public:
		Application();

		virtual ~Application() = default;

		void Run();


		void OnEvent(Event& e);

		void PushLayer(Ref<Layer> layer);
		void PopLayer(Ref<Layer> layer);
		void PushOverlay(Ref<Layer> overlay);
		void PopOverlay(Ref<Layer> overlay);

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

