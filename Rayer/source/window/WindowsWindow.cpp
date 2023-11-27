#include "WindowsWindow.h"

namespace Rayer {

	WindowsWindow::WindowsWindow(int mWidth, int mHeight, const char* mTitle) : Width(mWidth), Height(mHeight), Title(mTitle) {

		if (!glfwInit()) {

			std::cerr << "Failed to create GLFW window" << std::endl;
			std::terminate();
		}

		// Set GLFW window hints as needed
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		// Create a windowed mode window and its OpenGL context
		window = (GLFWwindow*)init(Width, Height, Title);

		if (!window) {
			glfwTerminate();
			std::cerr << "Failed to create GLFW window" << std::endl;
			std::terminate();
		}
	}

	void* WindowsWindow::init(int width, int height, const char* title) {

		GLFWwindow* tempWindow = glfwCreateWindow(width, height, title, NULL, NULL);
		return (void*)tempWindow;

	}

	

}