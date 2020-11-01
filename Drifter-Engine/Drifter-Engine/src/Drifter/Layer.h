#pragma once
#include "Drifter/Core.h"
#include "Drifter/Events/Event.h"

namespace Drifter {
	class DRIFTER_API Layer
	{
	public:
		Layer(const std::string & name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() { return m_debugName; }
	private:
		std::string m_debugName;

	};
}
