#pragma once

#ifdef DF_PLATFORM_WINDOWS
extern Drifter::Application* Drifter::CreateApplication();

int main() {
	auto app = Drifter::CreateApplication();
	app->Run();
	delete app;
}
#endif