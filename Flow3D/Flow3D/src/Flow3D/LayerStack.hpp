#pragma once

#include "Core.hpp"
#include "Layer.hpp"

#include <vector>

namespace Flow {

	// The LayerStack manages all the layers. It provides functionality for adding and removing layers.
	// Overlays are special layers that are always in front of "normal layers". They will therefore receive events first
	// but will update last.
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}
