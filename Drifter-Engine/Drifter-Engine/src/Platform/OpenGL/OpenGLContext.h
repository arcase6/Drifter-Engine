#pragma once
#include "Drifter/Renderer/GraphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Drifter {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		void SetTarget(GLFWwindow * window);
		virtual void SwapBuffers() override;

	private:
		GLFWwindow * m_window;
	};
}

