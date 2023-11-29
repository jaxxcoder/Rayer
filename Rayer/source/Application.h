#pragma once

#include<filesystem>
namespace fs = std::filesystem;

#include "rpch.h"
#include "window/WindowsWindow.h"
#include "gui/WindowsGUI.h"

namespace Rayer {

	class Application {

	public:
		Application(int aWidth, int aHeight, const char* aTitle);

		//The Actual Running loop for the application
		void applicationLoop();

	private:
		
		std::unique_ptr<Rayer::WindowsWindow> mWindow;
		

		std::string parentDir;
	};
}