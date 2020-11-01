#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include <Drifter/LayerStack.h>


namespace Drifter {
	class DRIFTER_API Application
	{
	public:
		Application();
		
		~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
	};

	Application* CreateApplication();

}

