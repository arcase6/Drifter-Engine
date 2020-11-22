#pragma once

#include <Drifter/Window.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace Drifter {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnFrameBegin() override;
		void OnFrameEnd() override;

		inline void* GetNativeWindow() const override { return m_window; };

		inline unsigned int GetWidth() const override { return m_data.Width; }
		inline unsigned int GetHeight() const override { return m_data.Height; }
		inline GLFWwindow * GetGlfwWindow() { return m_window; }
		
		//window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
		
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		void SetWindowCallbacks();
		void SetKeyCallbacks();
		void SetMouseCallbacks();
		virtual void Shutdown();
	private: 
		GLFWwindow* m_window;
		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		WindowData m_data;
		GraphicsContext* m_context;
	};

}

