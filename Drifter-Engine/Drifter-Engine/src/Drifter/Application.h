#pragma once

#include "Drifter/Core/Base.h"
#include "Window.h"
#include <Drifter/LayerStack.h>

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"

#include "Drifter/EditorUI/IMGUILayer.h"

namespace Drifter {
	class Application
	{
	public:
		Application();

		virtual ~Application() = default;

		void Run();

		void UpdateImgui();

		void UpdateLayers();


		void OnEvent(Event& e);

		void PushLayer(Ref<Layer> layer);
		void PopLayer(Ref<Layer> layer);
		void PushOverlay(Ref<Layer> overlay);
		void PopOverlay(Ref<Layer> overlay);

		static inline Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool HandleProfileCallback(KeyPressedEvent& e);


		Scope<Window> m_window;
		bool m_running = true;
		bool m_IsMinimized = false;
		LayerStack m_layerStack;
		Ref<EditorUI::ImguiLayer> m_ImguiLayer;

	private:
		static Application* s_Instance;

	};

	Application* CreateApplication();
}

