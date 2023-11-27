#include "Application.h"

namespace Rayer {

	Application::Application(int aWidth, int aHeight, const char* aTitle) {
		parentDir = (fs::current_path().fs::path::parent_path()).string();
		mWindow = std::make_unique<Rayer::WindowsWindow>(aWidth, aHeight, aTitle);;
	}

	void Application::applicationLoop() {

		mWindow->setContext();
		mWindow->setIcon((parentDir + "/Resources/Logo/Rayer-logo.png").c_str());
		mWindow->maximizeWindow();

		while (!mWindow->shouldClose()) {

			mWindow->renderWindow();
		}
	}

}