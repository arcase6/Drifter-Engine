#include "dfpch.h"
#include "Time.h"
#include "Platform/Windows/WindowsTime.h"
namespace Drifter {
	Time* Drifter::Time::s_Instance = new WindowsTime{};
}