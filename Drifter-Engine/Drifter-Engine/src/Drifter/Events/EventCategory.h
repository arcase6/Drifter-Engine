#pragma once

#include "Drifter/Core/Base.h"

enum class EventCategory {
	None = 0,
	Application = BIT(0),
	Input = BIT(1),
	Keyboard = BIT(2),
	Mouse = BIT(3),
	MouseButton = BIT(4)
};

inline EventCategory operator | (EventCategory lhs, EventCategory rhs)
{
	using T = std::underlying_type_t <EventCategory>;
	return static_cast<EventCategory>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

inline EventCategory& operator |= (EventCategory& lhs, EventCategory rhs)
{
	lhs = lhs | rhs;
	return lhs;
}

inline EventCategory operator & (EventCategory lhs, EventCategory rhs)
{
	using T = std::underlying_type_t <EventCategory>;
	return static_cast<EventCategory>(static_cast<T>(lhs) & static_cast<T>(rhs));
}

inline EventCategory& operator &= (EventCategory& lhs, EventCategory rhs)
{
	lhs = lhs & rhs;
	return lhs;
}