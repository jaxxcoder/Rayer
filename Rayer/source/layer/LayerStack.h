#pragma once

#include "Layer.h"

namespace Rayer {

	class LayerStack {

	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	public:

		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;


	};

}