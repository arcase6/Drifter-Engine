#include "dfpch.h"

#include "WindowsInput.h"

#include "Drifter/Application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Drifter {
	Input* Input::s_Instance = new WindowsInput();
	
	GLFWwindow* GetWindow()
	{
		return static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
	}

	bool WindowsInput::IsKeyPressImpl(int keycode)
	{
		int state = glfwGetKey(GetWindow(), keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}


	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		int state = glfwGetMouseButton(GetWindow(), button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		double x, y;
		glfwGetCursorPos(GetWindow(), &x, &y);
		return std::pair<float, float>((float)x,(float)y);
	}

	float WindowsInput::GetMouseXImpl()
	{
		double x, y;
		glfwGetCursorPos(GetWindow(), &x, &y);
		return (float)x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		double x, y;
		glfwGetCursorPos(GetWindow(), &x, &y);
		return (float)y;
	}
}