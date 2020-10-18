#include <Drifter.h>
#include <stdio.h>
class SandboxApplication : public Drifter::Application
{
public:
	SandboxApplication(){}
	~SandboxApplication() {}
};


Drifter::Application* Drifter::CreateApplication() {
	printf("Creating Application\n");
	return new SandboxApplication();
}