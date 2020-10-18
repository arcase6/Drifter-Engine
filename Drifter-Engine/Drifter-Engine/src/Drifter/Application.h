#pragma once

#include "Core.h"

namespace Drifter {
	class DRIFTER_API Application
	{
	public:
		Application();
		
		~Application();

		void Run();
	};

	Application* CreateApplication();

}

