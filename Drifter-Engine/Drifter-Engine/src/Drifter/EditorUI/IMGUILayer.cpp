//#include "dfpch.h"
#include <glad/glad.h>

#include "IMGUILayer.h"

#include "GLFW/glfw3.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "Drifter/Application.h"

inline GLFWwindow* GetGLFWwindow(Drifter::Window& window) { return (GLFWwindow*)window.GetNativeWindow(); }

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
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		DF_LOG_INFO("Config flags set");
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

#if DF_PLATFORM_WINDOWS
		ImGui_ImplGlfw_InitForOpenGL(GetGLFWwindow(m_window), false);
#endif
		ImGui_ImplOpenGL3_Init(glsl_version);
		DF_LOG_INFO("Backends called");
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
		ImGuiIO& io = ImGui::GetIO();
		Window& window = Application::Get().GetWindow();
		io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImguiLayer::OnEvent(Drifter::Event& e)
	{
	}
}