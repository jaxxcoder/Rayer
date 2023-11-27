#include "rpch.h"
#include "Application.h"


int main() {

	auto app = std::make_unique<Rayer::Application>(1920, 1080, "Rayer");
	app->applicationLoop();

	return 0;
}