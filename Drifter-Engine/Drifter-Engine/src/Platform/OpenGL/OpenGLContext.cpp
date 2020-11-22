#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Drifter {

	

	void OpenGLContext::SetTarget(GLFWwindow* target)
	{
		glfwMakeContextCurrent(target);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DF_ASSERT(status, "Failed to initialize glad!");

		m_window = target;
	}

	void OpenGLContext::SwapBuffers()
	{
		if (m_window != nullptr) {
			glfwSwapBuffers(m_window);
		}
	}
}