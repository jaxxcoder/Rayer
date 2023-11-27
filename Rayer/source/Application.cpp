#include "Application.h"

namespace Rayer {

	Application::Application(int aWidth, int aHeight, const char* aTitle) {
		
		mWindow = std::make_unique<Rayer::WindowsWindow>(aWidth, aHeight, aTitle);;
	}

	void Application::applicationLoop() {

		mWindow->setContext();
		mWindow->maximizeWindow();

		while (!mWindow->shouldClose()) {

			mWindow->renderWindow();
		}
	}

}