#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Drifter {
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack() = default;

		void PushLayer(Ref<Layer> layer);
		void PushOverlay(Ref<Layer> overlay);
		void PopLayer(Ref<Layer> layer);
		void PopOverlay(Ref<Layer> overlay);

		std::vector<Ref<Layer>>::iterator begin() { return m_layers.begin(); }
		std::vector<Ref<Layer>>::iterator end() { return m_layers.end(); }

	private:
		std::vector<Ref<Layer>> m_layers;
		int m_insertOffset{ 0 };
		std::vector<Ref<Layer>>::iterator layersEnd(){ return begin() + m_insertOffset;}
	};
}

