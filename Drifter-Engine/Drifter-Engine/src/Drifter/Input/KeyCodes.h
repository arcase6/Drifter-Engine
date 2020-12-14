#pragma once

#include "Core.h"


namespace Drifter {
	class KeyCodes {
	public:
		static int SPACE() { return IMP_SPACE; }
		static int APOSTROPHE() { return IMP_APOSTROPHE; }
		static int COMMA() { return IMP_COMMA; }
		static int MINUS() { return IMP_MINUS; }
		static int PERIOD() { return IMP_PERIOD; }
		static int SLASH() { return IMP_SLASH; }
		static int NUM_0() { return IMP_NUM_0; }
		static int NUM_1() { return IMP_NUM_1; }
		static int NUM_2() { return IMP_NUM_2; }
		static int NUM_3() { return IMP_NUM_3; }
		static int NUM_4() { return IMP_NUM_4; }
		static int NUM_5() { return IMP_NUM_5; }
		static int NUM_6() { return IMP_NUM_6; }
		static int NUM_7() { return IMP_NUM_7; }
		static int NUM_8() { return IMP_NUM_8; }
		static int NUM_9() { return IMP_NUM_9; }
		static int SEMICOLON() { return IMP_SEMICOLON; }
		static int EQUAL() { return IMP_EQUAL; }
		static int A() { return IMP_A; }
		static int B() { return IMP_B; }
		static int C() { return IMP_C; }
		static int D() { return IMP_D; }
		static int E() { return IMP_E; }
		static int F() { return IMP_F; }
		static int G() { return IMP_G; }
		static int H() { return IMP_H; }
		static int I() { return IMP_I; }
		static int J() { return IMP_J; }
		static int K() { return IMP_K; }
		static int L() { return IMP_L; }
		static int M() { return IMP_M; }
		static int N() { return IMP_N; }
		static int O() { return IMP_O; }
		static int P() { return IMP_P; }
		static int Q() { return IMP_Q; }
		static int R() { return IMP_R; }
		static int S() { return IMP_S; }
		static int T() { return IMP_T; }
		static int U() { return IMP_U; }
		static int V() { return IMP_V; }
		static int W() { return IMP_W; }
		static int X() { return IMP_X; }
		static int Y() { return IMP_Y; }
		static int Z() { return IMP_Z; }
		static int LEFT_BRACKET() { return IMP_LEFT_BRACKET; }
		static int BACKSLASH() { return IMP_BACKSLASH; }
		static int RIGHT_BRACKET() { return IMP_RIGHT_BRACKET; }
		static int GRAVE_ACCENT() { return IMP_GRAVE_ACCENT; }
		static int WORLD_1() { return IMP_WORLD_1; }
		static int WORLD_2() { return IMP_WORLD_2; }

		static int ESCAPE() { return IMP_ESCAPE; }
		static int ENTER() { return IMP_ENTER; }
		static int TAB() { return IMP_TAB; }
		static int BACKSPACE() { return IMP_BACKSPACE; }
		static int INSERT() { return IMP_INSERT; }
		static int DEL() { return IMP_DEL; }
		static int RIGHT() { return IMP_RIGHT; }
		static int LEFT() { return IMP_LEFT; }
		static int DOWN() { return IMP_DOWN; }
		static int UP() { return IMP_UP; }
		static int PAGE_UP() { return IMP_PAGE_UP; }
		static int PAGE_DOWN() { return IMP_PAGE_DOWN; }
		static int HOME() { return IMP_HOME; }
		static int END() { return IMP_END; }
		static int CAPS_LOCK() { return IMP_CAPS_LOCK; }
		static int SCROLL_LOCK() { return IMP_SCROLL_LOCK; }
		static int NUM_LOCK() { return IMP_NUM_LOCK; }
		static int PRINT_SCREEN() { return IMP_PRINT_SCREEN; }
		static int PAUSE() { return IMP_PAUSE; }
		static int F1() { return IMP_F1; }
		static int F2() { return IMP_F2; }
		static int F3() { return IMP_F3; }
		static int F4() { return IMP_F4; }
		static int F5() { return IMP_F5; }
		static int F6() { return IMP_F6; }
		static int F7() { return IMP_F7; }
		static int F8() { return IMP_F8; }
		static int F9() { return IMP_F9; }
		static int F10() { return IMP_F10; }
		static int F11() { return IMP_F11; }
		static int F12() { return IMP_F12; }
		static int F13() { return IMP_F13; }
		static int F14() { return IMP_F14; }
		static int F15() { return IMP_F15; }
		static int F16() { return IMP_F16; }
		static int F17() { return IMP_F17; }
		static int F18() { return IMP_F18; }
		static int F19() { return IMP_F19; }
		static int F20() { return IMP_F20; }
		static int F21() { return IMP_F21; }
		static int F22() { return IMP_F22; }
		static int F23() { return IMP_F23; }
		static int F24() { return IMP_F24; }
		static int F25() { return IMP_F25; }
		static int KP_0() { return IMP_KP_0; }
		static int KP_1() { return IMP_KP_1; }
		static int KP_2() { return IMP_KP_2; }
		static int KP_3() { return IMP_KP_3; }
		static int KP_4() { return IMP_KP_4; }
		static int KP_5() { return IMP_KP_5; }
		static int KP_6() { return IMP_KP_6; }
		static int KP_7() { return IMP_KP_7; }
		static int KP_8() { return IMP_KP_8; }
		static int KP_9() { return IMP_KP_9; }
		static int KP_DECIMAL() { return IMP_KP_DECIMAL; }
		static int KP_DIVIDE() { return IMP_KP_DIVIDE; }
		static int KP_MULTIPLY() { return IMP_KP_MULTIPLY; }
		static int KP_SUBTRACT() { return IMP_KP_SUBTRACT; }
		static int KP_ADD() { return IMP_KP_ADD; }
		static int KP_ENTER() { return IMP_KP_ENTER; }
		static int KP_EQUAL() { return IMP_KP_EQUAL; }
		static int LEFT_SHIFT() { return IMP_LEFT_SHIFT; }
		static int LEFT_CONTROL() { return IMP_LEFT_CONTROL; }
		static int LEFT_ALT() { return IMP_LEFT_ALT; }
		static int LEFT_SUPER() { return IMP_LEFT_SUPER; }
		static int RIGHT_SHIFT() { return IMP_RIGHT_SHIFT; }
		static int RIGHT_CONTROL() { return IMP_RIGHT_CONTROL; }
		static int RIGHT_ALT() { return IMP_RIGHT_ALT; }
		static int RIGHT_SUPER() { return IMP_RIGHT_SUPER; }
		static int MENU() { return IMP_MENU; }
	private:
		static int IMP_SPACE;
		static int IMP_APOSTROPHE;
		static int IMP_COMMA;
		static int IMP_MINUS;
		static int IMP_PERIOD;
		static int IMP_SLASH;
		static int IMP_NUM_0;
		static int IMP_NUM_1;
		static int IMP_NUM_2;
		static int IMP_NUM_3;
		static int IMP_NUM_4;
		static int IMP_NUM_5;
		static int IMP_NUM_6;
		static int IMP_NUM_7;
		static int IMP_NUM_8;
		static int IMP_NUM_9;
		static int IMP_SEMICOLON;
		static int IMP_EQUAL;
		static int IMP_A;
		static int IMP_B;
		static int IMP_C;
		static int IMP_D;
		static int IMP_E;
		static int IMP_F;
		static int IMP_G;
		static int IMP_H;
		static int IMP_I;
		static int IMP_J;
		static int IMP_K;
		static int IMP_L;
		static int IMP_M;
		static int IMP_N;
		static int IMP_O;
		static int IMP_P;
		static int IMP_Q;
		static int IMP_R;
		static int IMP_S;
		static int IMP_T;
		static int IMP_U;
		static int IMP_V;
		static int IMP_W;
		static int IMP_X;
		static int IMP_Y;
		static int IMP_Z;
		static int IMP_LEFT_BRACKET;
		static int IMP_BACKSLASH;
		static int IMP_RIGHT_BRACKET;
		static int IMP_GRAVE_ACCENT;
		static int IMP_WORLD_1;
		static int IMP_WORLD_2;

		//function keys
		static int IMP_ESCAPE;
		static int IMP_ENTER;
		static int IMP_TAB;
		static int IMP_BACKSPACE;
		static int IMP_INSERT;
		static int IMP_DEL;
		static int IMP_RIGHT;
		static int IMP_LEFT;
		static int IMP_DOWN;
		static int IMP_UP;
		static int IMP_PAGE_UP;
		static int IMP_PAGE_DOWN;
		static int IMP_HOME;
		static int IMP_END;
		static int IMP_CAPS_LOCK;
		static int IMP_SCROLL_LOCK;
		static int IMP_NUM_LOCK;
		static int IMP_PRINT_SCREEN;
		static int IMP_PAUSE;
		static int IMP_F1;
		static int IMP_F2;
		static int IMP_F3;
		static int IMP_F4;
		static int IMP_F5;
		static int IMP_F6;
		static int IMP_F7;
		static int IMP_F8;
		static int IMP_F9;
		static int IMP_F10;
		static int IMP_F11;
		static int IMP_F12;
		static int IMP_F13;
		static int IMP_F14;
		static int IMP_F15;
		static int IMP_F16;
		static int IMP_F17;
		static int IMP_F18;
		static int IMP_F19;
		static int IMP_F20;
		static int IMP_F21;
		static int IMP_F22;
		static int IMP_F23;
		static int IMP_F24;
		static int IMP_F25;
		static int IMP_KP_0;
		static int IMP_KP_1;
		static int IMP_KP_2;
		static int IMP_KP_3;
		static int IMP_KP_4;
		static int IMP_KP_5;
		static int IMP_KP_6;
		static int IMP_KP_7;
		static int IMP_KP_8;
		static int IMP_KP_9;
		static int IMP_KP_DECIMAL;
		static int IMP_KP_DIVIDE;
		static int IMP_KP_MULTIPLY;
		static int IMP_KP_SUBTRACT;
		static int IMP_KP_ADD;
		static int IMP_KP_ENTER;
		static int IMP_KP_EQUAL;
		static int IMP_LEFT_SHIFT;
		static int IMP_LEFT_CONTROL;
		static int IMP_LEFT_ALT;
		static int IMP_LEFT_SUPER;
		static int IMP_RIGHT_SHIFT;
		static int IMP_RIGHT_CONTROL;
		static int IMP_RIGHT_ALT;
		static int IMP_RIGHT_SUPER;
		static int IMP_MENU;
	};
}