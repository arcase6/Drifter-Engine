#pragma once

#include "Drifter/Events/Event.h"

namespace Drifter {
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_keyCode; }
		EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)
	protected:
		KeyEvent(int keyCode) : m_keyCode(keyCode) {}
		int m_keyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatedCount):
			KeyEvent(keyCode),
			m_repeatCount(repeatedCount)
		{}

		inline int GetRepeatCount() const { return m_repeatCount; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_repeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode) :
			KeyEvent(keyCode)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}