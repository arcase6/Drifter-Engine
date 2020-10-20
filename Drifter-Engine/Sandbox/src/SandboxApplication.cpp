#include <Drifter.h>
class SandboxApplication : public Drifter::Application
{
public:
	SandboxApplication(){}
	~SandboxApplication() {}
};


Drifter::Application* Drifter::CreateApplication() {
	DF_LOG_INFO("Creating Application\n");
	return new SandboxApplication();
}