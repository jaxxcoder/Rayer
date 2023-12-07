#include "WindowsWindow.h"

namespace Rayer {

	WindowsWindow::WindowsWindow(int mWidth, int mHeight, const char* mTitle) : Width(mWidth), Height(mHeight), Title(mTitle) {

		parentDir = (fs::current_path().fs::path::parent_path()).string();

		if (!glfwInit()) {

			std::cerr << "Failed to create GLFW window" << std::endl;
			std::terminate();
		}

		// Set GLFW window hints as needed
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		// Create a windowed mode window and its OpenGL context
		window = (GLFWwindow*)init(Width, Height, Title);

		if (!window) {
			glfwTerminate();
			std::cerr << "Failed to create GLFW window" << std::endl;
			std::terminate();
		}

		
		// Make the context current
		glfwMakeContextCurrent(window);
		
		

		mGui = std::make_unique<Rayer::WindowsGUI>();
		mGui->setupContext((void*)window);
		mGui->setFont((parentDir + "/Resources/Font/Padauk-Font.ttf").c_str() , 20.0f);

		//Initializing glew
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {

			std::cerr << "Failed to initialize glew" << std::endl;
			glfwDestroyWindow(window);
			glfwTerminate();
			std::terminate();
		}

		storeBufferSize();
		
		glViewport(0, 0, bufferWidth, bufferHeight);

		renderer = std::make_unique<OpenGL_Renderer>();
		shader = std::make_unique<Shader>();

		mViewportPos = mGui->getViewportPos();
		mViewportSize = mGui->getViewportSize();
		
		glViewport(0, 0, mViewportSize.x, mViewportSize.y);

	}

	void* WindowsWindow::init(int width, int height, const char* title) {

		GLFWwindow* tempWindow = glfwCreateWindow(width, height, title, NULL, NULL);
		return (void*)tempWindow;

	}

	void WindowsWindow::setIcon(const char* iconPath) {
		icon_data = stbi_load(iconPath, &iWidth, &iHeight, &iChannels, 0);

		if (icon_data) {

			icon.width = iWidth;
			icon.height = iHeight;
			icon.pixels = icon_data;

			// Set the window icon
			glfwSetWindowIcon(window, 1, &icon);
		}
	}
	
	void WindowsWindow::renderWindow()  {

		glViewport(0, 0, mViewportSize.x, mViewportSize.y);
		renderer->bindFrameBuffer();
		clearFrame();
		poolEvents();

		mViewportPos = mGui->getViewportPos();
		mViewportSize = mGui->getViewportSize();

		mGui->guiNewFrame();


		renderer->render(shader->getInstance() , RenderType::DrawArrays);
		renderer->unbindFrameBuffer();

		mGui->getGuiPanels(renderer->getRenderTextureID());

		

		mGui->renderGUI();

		swapBuffers();

	}

	void WindowsWindow::cleanup() {

		mGui->cleanup();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void WindowsWindow::storeBufferSize() {

		glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	}

	void WindowsWindow::clearFrame() {
		
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
	}

	
	

}