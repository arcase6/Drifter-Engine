#include "dfpch.h"

#include "Drifter/Input/KeyCodes.h"
#include "GLFW/glfw3.h"

#if DF_PLATFORM_WINDOWS

namespace Drifter {
	//PrintableKeys
	int KeyCodes::IMP_SPACE = GLFW_KEY_SPACE;
	int KeyCodes::IMP_APOSTROPHE = GLFW_KEY_APOSTROPHE;
	int KeyCodes::IMP_COMMA = GLFW_KEY_COMMA;
	int KeyCodes::IMP_MINUS = GLFW_KEY_MINUS;
	int KeyCodes::IMP_PERIOD = GLFW_KEY_PERIOD;
	int KeyCodes::IMP_SLASH = GLFW_KEY_SLASH;
	int KeyCodes::IMP_NUM_0 = GLFW_KEY_0;
	int KeyCodes::IMP_NUM_1 = GLFW_KEY_1;
	int KeyCodes::IMP_NUM_2 = GLFW_KEY_2;
	int KeyCodes::IMP_NUM_3 = GLFW_KEY_3;
	int KeyCodes::IMP_NUM_4 = GLFW_KEY_4;
	int KeyCodes::IMP_NUM_5 = GLFW_KEY_5;
	int KeyCodes::IMP_NUM_6 = GLFW_KEY_6;
	int KeyCodes::IMP_NUM_7 = GLFW_KEY_7;
	int KeyCodes::IMP_NUM_8 = GLFW_KEY_8;
	int KeyCodes::IMP_NUM_9 = GLFW_KEY_9;
	int KeyCodes::IMP_SEMICOLON = GLFW_KEY_SEMICOLON;
	int KeyCodes::IMP_EQUAL = GLFW_KEY_EQUAL;
	int KeyCodes::IMP_A = GLFW_KEY_A;
	int KeyCodes::IMP_B = GLFW_KEY_B;
	int KeyCodes::IMP_C = GLFW_KEY_C;
	int KeyCodes::IMP_D = GLFW_KEY_D;
	int KeyCodes::IMP_E = GLFW_KEY_E;
	int KeyCodes::IMP_F = GLFW_KEY_F;
	int KeyCodes::IMP_G = GLFW_KEY_G;
	int KeyCodes::IMP_H = GLFW_KEY_H;
	int KeyCodes::IMP_I = GLFW_KEY_I;
	int KeyCodes::IMP_J = GLFW_KEY_J;
	int KeyCodes::IMP_K = GLFW_KEY_K;
	int KeyCodes::IMP_L = GLFW_KEY_L;
	int KeyCodes::IMP_M = GLFW_KEY_M;
	int KeyCodes::IMP_N = GLFW_KEY_N;
	int KeyCodes::IMP_O = GLFW_KEY_O;
	int KeyCodes::IMP_P = GLFW_KEY_P;
	int KeyCodes::IMP_Q = GLFW_KEY_Q;
	int KeyCodes::IMP_R = GLFW_KEY_R;
	int KeyCodes::IMP_S = GLFW_KEY_S;
	int KeyCodes::IMP_T = GLFW_KEY_T;
	int KeyCodes::IMP_U = GLFW_KEY_U;
	int KeyCodes::IMP_V = GLFW_KEY_V;
	int KeyCodes::IMP_W = GLFW_KEY_W;
	int KeyCodes::IMP_X = GLFW_KEY_X;
	int KeyCodes::IMP_Y = GLFW_KEY_Y;
	int KeyCodes::IMP_Z = GLFW_KEY_Z;
	int KeyCodes::IMP_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET;
	int KeyCodes::IMP_BACKSLASH = GLFW_KEY_BACKSLASH;
	int KeyCodes::IMP_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET;
	int KeyCodes::IMP_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT;
	int KeyCodes::IMP_WORLD_1 = GLFW_KEY_WORLD_1;
	int KeyCodes::IMP_WORLD_2 = GLFW_KEY_WORLD_2;

	//function keys
	int KeyCodes::IMP_ESCAPE = GLFW_KEY_ESCAPE;
	int KeyCodes::IMP_ENTER = GLFW_KEY_ENTER;
	int KeyCodes::IMP_TAB = GLFW_KEY_TAB;
	int KeyCodes::IMP_BACKSPACE = GLFW_KEY_BACKSPACE;
	int KeyCodes::IMP_INSERT = GLFW_KEY_INSERT;
	int KeyCodes::IMP_DEL = GLFW_KEY_DELETE;
	int KeyCodes::IMP_RIGHT = GLFW_KEY_RIGHT;
	int KeyCodes::IMP_LEFT = GLFW_KEY_LEFT;
	int KeyCodes::IMP_DOWN = GLFW_KEY_DOWN;
	int KeyCodes::IMP_UP = GLFW_KEY_UP;
	int KeyCodes::IMP_PAGE_UP = GLFW_KEY_PAGE_UP;
	int KeyCodes::IMP_PAGE_DOWN = GLFW_KEY_PAGE_DOWN;
	int KeyCodes::IMP_HOME = GLFW_KEY_HOME;
	int KeyCodes::IMP_END = GLFW_KEY_END;
	int KeyCodes::IMP_CAPS_LOCK = GLFW_KEY_CAPS_LOCK;
	int KeyCodes::IMP_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK;
	int KeyCodes::IMP_NUM_LOCK = GLFW_KEY_NUM_LOCK;
	int KeyCodes::IMP_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN;
	int KeyCodes::IMP_PAUSE = GLFW_KEY_PAUSE;
	int KeyCodes::IMP_F1 = GLFW_KEY_F1;
	int KeyCodes::IMP_F2 = GLFW_KEY_F2;
	int KeyCodes::IMP_F3 = GLFW_KEY_F3;
	int KeyCodes::IMP_F4 = GLFW_KEY_F4;
	int KeyCodes::IMP_F5 = GLFW_KEY_F5;
	int KeyCodes::IMP_F6 = GLFW_KEY_F6;
	int KeyCodes::IMP_F7 = GLFW_KEY_F7;
	int KeyCodes::IMP_F8 = GLFW_KEY_F8;
	int KeyCodes::IMP_F9 = GLFW_KEY_F9;
	int KeyCodes::IMP_F10 = GLFW_KEY_F10;
	int KeyCodes::IMP_F11 = GLFW_KEY_F11;
	int KeyCodes::IMP_F12 = GLFW_KEY_F12;
	int KeyCodes::IMP_F13 = GLFW_KEY_F13;
	int KeyCodes::IMP_F14 = GLFW_KEY_F14;
	int KeyCodes::IMP_F15 = GLFW_KEY_F15;
	int KeyCodes::IMP_F16 = GLFW_KEY_F16;
	int KeyCodes::IMP_F17 = GLFW_KEY_F17;
	int KeyCodes::IMP_F18 = GLFW_KEY_F18;
	int KeyCodes::IMP_F19 = GLFW_KEY_F19;
	int KeyCodes::IMP_F20 = GLFW_KEY_F20;
	int KeyCodes::IMP_F21 = GLFW_KEY_F21;
	int KeyCodes::IMP_F22 = GLFW_KEY_F22;
	int KeyCodes::IMP_F23 = GLFW_KEY_F23;
	int KeyCodes::IMP_F24 = GLFW_KEY_F24;
	int KeyCodes::IMP_F25 = GLFW_KEY_F25;
	int KeyCodes::IMP_KP_0 = GLFW_KEY_KP_0;
	int KeyCodes::IMP_KP_1 = GLFW_KEY_KP_1;
	int KeyCodes::IMP_KP_2 = GLFW_KEY_KP_2;
	int KeyCodes::IMP_KP_3 = GLFW_KEY_KP_3;
	int KeyCodes::IMP_KP_4 = GLFW_KEY_KP_4;
	int KeyCodes::IMP_KP_5 = GLFW_KEY_KP_5;
	int KeyCodes::IMP_KP_6 = GLFW_KEY_KP_6;
	int KeyCodes::IMP_KP_7 = GLFW_KEY_KP_7;
	int KeyCodes::IMP_KP_8 = GLFW_KEY_KP_8;
	int KeyCodes::IMP_KP_9 = GLFW_KEY_KP_9;
	int KeyCodes::IMP_KP_DECIMAL = GLFW_KEY_KP_DECIMAL;
	int KeyCodes::IMP_KP_DIVIDE = GLFW_KEY_KP_DIVIDE;
	int KeyCodes::IMP_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY;
	int KeyCodes::IMP_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT;
	int KeyCodes::IMP_KP_ADD = GLFW_KEY_KP_ADD;
	int KeyCodes::IMP_KP_ENTER = GLFW_KEY_KP_ENTER;
	int KeyCodes::IMP_KP_EQUAL = GLFW_KEY_KP_EQUAL;
	int KeyCodes::IMP_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT;
	int KeyCodes::IMP_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL;
	int KeyCodes::IMP_LEFT_ALT = GLFW_KEY_LEFT_ALT;
	int KeyCodes::IMP_LEFT_SUPER = GLFW_KEY_LEFT_SUPER;
	int KeyCodes::IMP_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT;
	int KeyCodes::IMP_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL;
	int KeyCodes::IMP_RIGHT_ALT = GLFW_KEY_RIGHT_ALT;
	int KeyCodes::IMP_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER;
	int KeyCodes::IMP_MENU = GLFW_KEY_MENU;
}

#endif