#pragma once

#include "Drifter/Core/Base.h"

namespace Drifter {
	class MouseCodes {
	public:
		static int BUTTON_1() { return IMP_BUTTON_1; }
		static int BUTTON_2() { return IMP_BUTTON_2; }
		static int BUTTON_3() { return IMP_BUTTON_3; }
		static int BUTTON_4() { return IMP_BUTTON_4; }
		static int BUTTON_5() { return IMP_BUTTON_5; }
		static int BUTTON_6() { return IMP_BUTTON_6; }
		static int BUTTON_7() { return IMP_BUTTON_7; }
		static int BUTTON_8() { return IMP_BUTTON_8; }
		static int LAST() { return IMP_LAST; }
		static int LEFT() { return IMP_LEFT; }
		static int RIGHT() { return IMP_RIGHT; }
		static int MIDDLE() { return IMP_MIDDLE; }
	private:
		static int IMP_BUTTON_1;
		static int IMP_BUTTON_2;
		static int IMP_BUTTON_3;
		static int IMP_BUTTON_4;
		static int IMP_BUTTON_5;
		static int IMP_BUTTON_6;
		static int IMP_BUTTON_7;
		static int IMP_BUTTON_8;
		static int IMP_LAST;
		static int IMP_LEFT;
		static int IMP_RIGHT;
		static int IMP_MIDDLE;
	};
}