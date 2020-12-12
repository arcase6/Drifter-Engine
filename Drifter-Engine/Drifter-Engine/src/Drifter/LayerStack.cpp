#include "Drifter/Core/dfpch.h"

#include "LayerStack.h"

namespace Drifter {
	LayerStack::LayerStack()
	{
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_layers.emplace(layersEnd(), layer);
		++m_insertOffset;
		layer->OnAttach();
	}
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
		overlay->OnAttach();
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(begin(), layersEnd(), layer);
		if (it != end()) {
			(*it)->OnDetach();
			m_layers.erase(it);
			--m_insertOffset;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layersEnd(), end(), overlay);
		if (it != end()) {
			(*it)->OnDetach();
			m_layers.erase(it);
		}
	}
}