#include "dfpch.h"
#include "WindowsWindow.h"
#include "Drifter/Events/ApplicationEvent.h"
#include "Drifter/Events/KeyEvent.h"
#include "Drifter/Events/MouseEvent.h"
#include <Platform/OpenGL/OpenGLContext.h>

#include "Drifter/Renderer/Renderer.h"
#include "Debug/Instrumentation.h"

namespace Drifter
{
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error, const char * description) {
		DF_LOG_ERROR("GLFW error{0} : {1}", error, description);
	}
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		PROFILE_FUNCTION();
		m_data.Title = props.Title;
		m_data.Width = props.Width;
		m_data.Height = props.Height;

		DF_LOG_INFO("Creating window: {0} {1}W x {2}H)", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on sstem shutdown
			int success = glfwInit();
			DF_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)m_data.Width, (int)m_data.Height, m_data.Title.c_str(), nullptr, nullptr);
		
		m_context = static_cast<GraphicsContext *>(new OpenGLContext(m_window));


		glfwSetWindowUserPointer(m_window, &m_data);

		SetVSync(true);

		//set glfw callbacks
		SetWindowCallbacks();
		SetKeyCallbacks();
		SetMouseCallbacks();


	}

	void WindowsWindow::SetWindowCallbacks()
	{
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowResizeEvent event(width, height);
			data.Width = width;
			data.Height = height;
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
	}

	void WindowsWindow::SetKeyCallbacks()
	{
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int modes) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
		});
	}

	void WindowsWindow::SetMouseCallbacks()
	{
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xpos, (float)ypos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		PROFILE_FUNCTION();
		glfwDestroyWindow(m_window);
		delete(m_context);
	}


	void WindowsWindow::OnFrameBegin() {
		PROFILE_FUNCTION();
		Renderer::Clear();
	}

	void WindowsWindow::OnFrameEnd() {
		PROFILE_FUNCTION();
		glfwPollEvents();
		m_context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled) {
		PROFILE_FUNCTION();
		glfwSwapInterval(enabled ? 1 : 0);
		m_data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_data.VSync;
	}
}