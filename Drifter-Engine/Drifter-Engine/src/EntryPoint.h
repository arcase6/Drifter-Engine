#pragma once
#include "Drifter.h"

#ifdef DF_PLATFORM_WINDOWS
extern Drifter::Application* Drifter::CreateApplication();

int main() {
	BEGIN_PROFILING_SESSION("Setup.json");
	{
		PROFILE_SCOPE("Setup Logger");
		Drifter::Log::Init();
		Drifter::Log::GetCoreLoggger()->trace("Initialized Log");
	}
	auto app = Drifter::CreateApplication();
	END_PROFILING_SESSION();
	
	BEGIN_PROFILING_SESSION("Runtime.json");
	app->Run();
	END_PROFILING_SESSION();

	BEGIN_PROFILING_SESSION("Cleanup.json");
	delete app;
	END_PROFILING_SESSION();
}
#endif