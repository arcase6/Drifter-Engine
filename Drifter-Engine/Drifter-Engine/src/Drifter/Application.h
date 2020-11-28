#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include <Drifter/LayerStack.h>

#include "Drifter/Renderer/Shader.h"
#include "Drifter/Renderer/Buffer.h"
#include "Drifter/Renderer/VertexArray.h"

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
		void SetBufferData();

	private:
		static Application* s_Instance;
	
		//OpenGL data for rendering -- likely to be removed later
		std::shared_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<Shader> m_Shader;

	};

	Application* CreateApplication();
}

