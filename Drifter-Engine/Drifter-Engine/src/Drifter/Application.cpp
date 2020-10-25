#include "dfpch.h"

#include "Application.h"
#include <stdio.h>
#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Drifter {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		DF_LOG_INFO("Welcome to Drifter!");
		DF_LOG_WARNING("Run has not yet been implemented! Entering into an infinite loop");
		
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication)) {
			DF_LOG_Trace(e.ToString() + " is an Application Event");
		}
		else if(e.IsInCategory(EventCategoryInput)){
			DF_LOG_Trace(e.ToString() + " is an Input Event");
		}
		while (true);
	}
}