#pragma once
#include "Drifter.h"

#ifdef DF_PLATFORM_WINDOWS
extern Drifter::Application* Drifter::CreateApplication();

int main() {
	Drifter::Instrumentor::DeleteLogs(".Benchmarking");
	BEGIN_PROFILING_SESSION("Setup.json");
	{
		PROFILE_SCOPE("Setup Logger");
		Drifter::Log::Init();
		Drifter::Log::GetCoreLoggger()->trace("Initialized Log");
	}
	auto app = Drifter::CreateApplication();
	END_PROFILING_SESSION();
	
	app->Run();

	BEGIN_PROFILING_SESSION("Cleanup.json");
	delete app;
	END_PROFILING_SESSION();
}
#endif