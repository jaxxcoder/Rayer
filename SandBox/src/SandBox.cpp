#include <Rayer.h>

class SandBox : public Rayer::Application {

public:

	SandBox() {

		

	}

};


Rayer::Application* Rayer::CreateApplication() {

	return new SandBox();
}

int main() {

	auto app = Rayer::CreateApplication();

	app->ApplicationLoop();
	
	delete app;

	return 0;
}