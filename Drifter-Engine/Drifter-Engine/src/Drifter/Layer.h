#pragma once

#include "Drifter/Core/Base.h"
#include "Drifter/Events/Event.h"

namespace Drifter {
	class Layer
	{
	public:
		Layer(const std::string & name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImgui() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() { return m_debugName; }
	private:
		std::string m_debugName;

	};
}

