#pragma once

#include<filesystem>
namespace fs = std::filesystem;

#include "rpch.h"
#include "window/WindowsWindow.h"
#include "gui/WindowsGUI.h"
#include "event/Event.h"
#include "event/ApplicationEvent.h"
#include "layer/LayerStack.h"
#include "layer/Layer.h"

namespace Rayer {

	class Application {

	public:
		Application(int aWidth, int aHeight, const char* aTitle,bool aVSync);

		//The Actual Running loop for the application
		void applicationLoop();

		void OnEvent(Event& e);

		bool OnWindowClosed(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		
		LayerStack layerStack;

		std::unique_ptr<Rayer::WindowsWindow> mWindow;
		

		std::string parentDir;
	};
}