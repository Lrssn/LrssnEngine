#include "lepch.h"
#include "LrssnEngine/Core/LayerStack.h"

namespace LrssnEngine {

	LayerStack::~LayerStack() 	{
		for (Layer* layer : mLayers) {
			layer->OnDetach();
			delete layer;

		}
	}

	void LayerStack::PushLayer(Layer* layer) 	{
		mLayers.emplace(mLayers.begin() + mLayerInsertIndex, layer);
		mLayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) 	{
		mLayers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) 	{
		auto it = std::find(mLayers.begin(), mLayers.begin() + mLayerInsertIndex, layer);
		if (it != mLayers.end()){
			layer->OnDetach();
			mLayers.erase(it);
			mLayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) 	{
		auto it = std::find(mLayers.begin() + mLayerInsertIndex, mLayers.end(), overlay);
		if (it != mLayers.begin() + mLayerInsertIndex){
			overlay->OnDetach();
			mLayers.erase(it);
		}
	}
}