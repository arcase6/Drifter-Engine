#pragma once

#include "Core.h"
#include "Events/Event.h"
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
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
	
		static Application* s_Instance;

	private: //OpenGL buffer data
		unsigned int m_vertexArray, m_vertexBuffer, m_indexBuffer;
		void GenerateOpenGLBuffers();
		void SetBufferData();
	};

	Application* CreateApplication();

}

