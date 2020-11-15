#include <Drifter.h>

class ExampleLayer : public Drifter::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override 
	{
		DF_LOG_INFO("Example Layer update");
	}

	void OnEvent(Drifter::Event& e) override
	{
		DF_LOG_TRACE("{0}", e);
	}
};

class SandboxApplication : public Drifter::Application
{
public:
	SandboxApplication(){
		auto debugLayer = new Drifter::EditorUI::ImguiLayer(GetWindow());
		PushOverlay(debugLayer);
		//PushLayer(new ExampleLayer());
	}
	~SandboxApplication() {}
};


Drifter::Application* Drifter::CreateApplication() {
	DF_LOG_INFO("Creating Application\n");
	return new SandboxApplication();
}