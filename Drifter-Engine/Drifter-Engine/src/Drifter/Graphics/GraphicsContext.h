#pragma once

#include "Drifter/Window.h"

namespace Drifter {
	class Window;
	class GraphicsContext
	{
	public:
		virtual void SwapBuffers() = 0;
	};
}