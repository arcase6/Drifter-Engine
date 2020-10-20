#pragma once

#ifdef DF_PLATFORM_WINDOWS
extern Drifter::Application* Drifter::CreateApplication();

int main() {
	Drifter::Log::Init();
	Drifter::Log::GetCoreLoggger()->trace("Initialized Log");
	auto app = Drifter::CreateApplication();
	app->Run();
	delete app;
}
#endif