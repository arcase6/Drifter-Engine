#include "Application.h"
#include <stdio.h>
#include "Log.h"

namespace Drifter {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		DF_LOG_INFO("Welcome to Drifter!");
		DF_LOG_WARNING("Run has not yet been implemented! Entering into an infinite loop");
		while (true);
	}
}