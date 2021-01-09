#include <Drifter.h>
#include <EntryPoint.h>
#include "Layers/ExampleLayer.h"
#include "Layers/Sandbox2DLayer.h"

namespace Sandbox {
	class SandboxApplication : public Drifter::Application
	{
	public:
		SandboxApplication() {
			//PushLayer(CreateRef());
			PushLayer(Drifter::CreateRef<Sandbox2DLayer>());
		}
		~SandboxApplication() = default;
	};


}
	
Drifter::Application* Drifter::CreateApplication() {
	PROFILE_FUNCTION();
	DF_LOG_INFO("Creating Application\n");
	return new Sandbox::SandboxApplication();
}