#pragma once

#include "Event.h"

#include <sstream>

namespace Drifter {

	class DRIFTER_API MouseMovedEvent : public Event
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
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_mouseX, m_mouseY;
	};

	class DRIFTER_API MouseScrolledEvent : public Event
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
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_xOffset, m_yOffset;
	};

	class DRIFTER_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(float button) : m_button(button) {}
		float m_button;
	};

	class DRIFTER_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(float button)
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

	class DRIFTER_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(float button)
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