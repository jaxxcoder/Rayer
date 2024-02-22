#include "Application.h"

namespace Rayer {

#define BIND_EVENT_FN(x) std::bind(&Application::x , this , std::placeholders::_1)

	Application::Application(int aWidth, int aHeight, const char* aTitle , bool aVSync) {

		parentDir = (fs::current_path().fs::path::parent_path()).string();
		mWindow = std::make_unique<Rayer::WindowsWindow>(aWidth, aHeight, aTitle , aVSync);
		mWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));

	}

	void Application::OnEvent(Event& e) {

		//Object of the event dispatcher for dispatching event stuff
		EventDispatcher dispatcher(e);
		
		std::cout << e.ToString() << std::endl;

		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClosed));

		for (auto it = layerStack.end(); it != layerStack.begin();) {

			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
		

	}

	bool Application::OnWindowClosed(Event& e) {

		mWindow->SetWindowRunningState(false);
		return true;
	}

	void Application::applicationLoop() {

		mWindow->setIcon((parentDir + "/Resources/Logo/Rayer-logo.png").c_str());
		mWindow->maximizeWindow();
		
		

		while (mWindow->IsRunnning()) {

			mWindow->renderWindow();

			for (Layer* layer : layerStack) {
				layer->OnUpdate();
			}
			
		}

		mWindow->cleanup();

		
	}

	void Application::PushLayer(Layer* layer) {

		layerStack.PushLayer(layer);

	}

	void Application::PushOverlay(Layer* overlay) {

		layerStack.PushOverlay(overlay);
	}

}