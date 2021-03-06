#pragma once

#include "Drifter/Events/Event.h"

namespace Drifter {

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float xOffset, float y) 
			: m_mouseX(xOffset), m_mouseY(y) {}

		inline float GetX() const { return m_mouseX; }
		inline float GetY() const { return m_mouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
	private:
		float m_mouseX, m_mouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset) {}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
	private:
		float m_xOffset, m_yOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_button; }
		EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
	protected:
		MouseButtonEvent(int button) : m_button(button) {}
		int m_button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		inline int GetMouseButtonPressed() const { return m_button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		inline int GetMouseButtonReleased() const { return m_button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}