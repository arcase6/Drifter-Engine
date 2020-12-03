#include <Drifter.h>
#include <Drifter/Core/EntryPoint.h>
#include "ExampleLayer.h"

namespace Sandbox {
	class SandboxApplication : public Drifter::Application
	{
	public:
		SandboxApplication() {
			auto debugLayer = new Drifter::EditorUI::ImguiLayer(GetWindow());
			PushOverlay(debugLayer);
			PushLayer(new ExampleLayer());
		}
		~SandboxApplication() {}
	};


}
	
Drifter::Application* Drifter::CreateApplication() {
	DF_LOG_INFO("Creating Application\n");
	return new Sandbox::SandboxApplication();
}