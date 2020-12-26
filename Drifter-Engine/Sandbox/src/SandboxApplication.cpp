#include <Drifter.h>
#include <EntryPoint.h>
#include "Layers/ExampleLayer.h"
#include "Layers/Sandbox2DLayer.h"

namespace Sandbox {
	class SandboxApplication : public Drifter::Application
	{
	public:
		SandboxApplication() {
			//PushLayer(std::make_shared<ExampleLayer>());
			PushLayer(std::make_shared<Sandbox2DLayer>());
		}
		~SandboxApplication() = default;
	};


}
	
Drifter::Application* Drifter::CreateApplication() {
	DF_LOG_INFO("Creating Application\n");
	return new Sandbox::SandboxApplication();
}