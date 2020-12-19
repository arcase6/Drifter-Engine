#include <Drifter.h>
#include <EntryPoint.h>
#include "ExampleLayer.h"

namespace Sandbox {
	class SandboxApplication : public Drifter::Application
	{
	public:
		SandboxApplication() {
			auto debugLayer = std::make_shared<Drifter::EditorUI::ImguiLayer>(GetWindow());
			PushOverlay(debugLayer);
			PushLayer(std::make_shared<ExampleLayer>());
		}
		~SandboxApplication() = default;
	};


}
	
Drifter::Application* Drifter::CreateApplication() {
	DF_LOG_INFO("Creating Application\n");
	return new Sandbox::SandboxApplication();
}