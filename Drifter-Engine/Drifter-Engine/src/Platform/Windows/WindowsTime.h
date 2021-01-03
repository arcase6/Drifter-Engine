#pragma once
#include "Drifter/Core/Time.h"
namespace Drifter {
	class WindowsTime : public Time
	{
	private:
		long long m_Frame;
		double m_Time;
		Timestep m_DeltaTime;
	public:
		WindowsTime();
	protected:
		// Inherited via Time
		virtual Timestep GetDeltaTimeImpl() override;
		virtual double GetTimeImpl() override{ return m_Time; }
		virtual long long GetFrameImpl() { return m_Frame; }
		virtual void TickImpl() override;

	};
}