//#include "dfpch.h"

#include "IMGUILayer.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <Drifter/Layer.h>

inline GLFWwindow* GetGLFWwindow(Drifter::Window& window) { return (GLFWwindow * )window.GetNativeWindow(); }

namespace Drifter::EditorUI {
	ImguiLayer::ImguiLayer(Drifter::Window& window, const std::string& name)
		:Layer(name), m_window(window)
	{
	}

	ImguiLayer::~ImguiLayer()
	{
	}

	void ImguiLayer::OnAttach()
	{
		const char* glsl_version = "#version 410";
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();
#if DF_PLATFORM_WINDOWS
		ImGui_ImplGlfw_InitForOpenGL(GetGLFWwindow(m_window), false);
#endif
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void ImguiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
	}

	void ImguiLayer::OnUpdate()
	{
		static bool show_demo_window = true;
		NewFrameGLFW();
		ImGui::ShowDemoWindow(&show_demo_window);
		EndFrameGLFW();

	}

	void ImguiLayer::NewFrameGLFW()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImguiLayer::EndFrameGLFW()
	{
		ImGui::Render();

		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		int display_w, display_h;
		glfwGetFramebufferSize(GetGLFWwindow(m_window), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiLayer::OnEvent(Drifter::Event& e)
	{
	}
}