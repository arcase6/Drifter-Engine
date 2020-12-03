#pragma once

#include "Drifter/Core/Core.h"
#include "Layer.h"

#include <vector>

namespace Drifter {
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }

	private:
		std::vector<Layer*> m_layers;
		int m_insertOffset{ 0 };
		std::vector<Layer*>::iterator layersEnd(){ return begin() + m_insertOffset;}
	};
}

