#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Drifter {
	class DRIFTER_API Application
	{
	public:
		Application();
		
		~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	Application* CreateApplication();

}

