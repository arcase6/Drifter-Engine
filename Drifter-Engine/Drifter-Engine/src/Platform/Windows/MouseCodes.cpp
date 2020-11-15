
#include "Drifter/MouseCodes.h"
#include "GLFW/glfw3.h"

#if DF_PLATFORM_WINDOWS
namespace Drifter
{
	int MouseCodes::IMP_BUTTON_1 = GLFW_MOUSE_BUTTON_1;
	int MouseCodes::IMP_BUTTON_2 = GLFW_MOUSE_BUTTON_2;
	int MouseCodes::IMP_BUTTON_3 = GLFW_MOUSE_BUTTON_3;
	int MouseCodes::IMP_BUTTON_4 = GLFW_MOUSE_BUTTON_4;
	int MouseCodes::IMP_BUTTON_5 = GLFW_MOUSE_BUTTON_5;
	int MouseCodes::IMP_BUTTON_6 = GLFW_MOUSE_BUTTON_6;
	int MouseCodes::IMP_BUTTON_7 = GLFW_MOUSE_BUTTON_7;
	int MouseCodes::IMP_BUTTON_8 = GLFW_MOUSE_BUTTON_8;
	int MouseCodes::IMP_LAST = GLFW_MOUSE_BUTTON_LAST;
	int MouseCodes::IMP_LEFT = GLFW_MOUSE_BUTTON_LEFT;
	int MouseCodes::IMP_RIGHT = GLFW_MOUSE_BUTTON_RIGHT;
	int MouseCodes::IMP_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE;
}

#endif