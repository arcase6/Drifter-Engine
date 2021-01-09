#include "RenderCommand.h"

#include "Platform/OpenGL/Renderer/OpenGLRenderCommandParser.h"
namespace Drifter {
	// OpenGL is hardcoded right now. Need to add mechanism to chang the active rendering framework to DirectX and Vulkan
	RenderCommandParser * RenderCommand::s_CommandParser = new OpenGLRenderCommandParser();
}