#pragma once
#include <Drifter/Input/Input.h>
namespace Drifter {
	class WindowsInput : public Input
	{
	protected:
		// Inherited via Input
		virtual bool IsKeyPressImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

	private:
		Window* m_window;
	};
}
