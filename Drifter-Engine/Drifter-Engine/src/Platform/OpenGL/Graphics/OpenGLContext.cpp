#include "dfpch.h"
#include "OpenGLContext.h"

#include "DebugUtil/Debug.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Drifter {

	OpenGLContext::OpenGLContext(GLFWwindow* window) {
		PROFILE_FUNCTION();
		SetTarget(window);
	}

	void OpenGLContext::SetTarget(GLFWwindow* target)
	{
		glfwMakeContextCurrent(target);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DF_ASSERT_LV1(status, "Failed to initialize glad!");

		m_window = target;

		DF_LOG_INFO("OpenGL Vendor:   {0}", glGetString(GL_VENDOR));
		DF_LOG_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
		DF_LOG_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		PROFILE_RENDERER_FUNCTION();
		if (m_window != nullptr) {
			glfwSwapBuffers(m_window);
		}
	}
}