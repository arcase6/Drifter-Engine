#include "dfpch.h"

#include "LayerStack.h"

namespace Drifter {
	LayerStack::LayerStack()
	{
	}

	void LayerStack::PushLayer(Ref<Layer> layer)
	{
		m_layers.emplace(layersEnd(), layer);
		++m_insertOffset;
		layer->OnAttach();
	}
	void LayerStack::PushOverlay(Ref<Layer> overlay)
	{
		m_layers.emplace_back(overlay);
		overlay->OnAttach();
	}
	void LayerStack::PopLayer(Ref<Layer> layer)
	{
		auto it = std::find(begin(), layersEnd(), layer);
		if (it != end()) {
			(*it)->OnDetach();
			m_layers.erase(it);
			--m_insertOffset;
		}
	}
	void LayerStack::PopOverlay(Ref<Layer> overlay)
	{
		auto it = std::find(layersEnd(), end(), overlay);
		if (it != end()) {
			(*it)->OnDetach();
			m_layers.erase(it);
		}
	}
}