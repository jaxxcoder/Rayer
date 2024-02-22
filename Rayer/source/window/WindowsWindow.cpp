#include "WindowsWindow.h"

namespace Rayer {

	WindowsWindow::WindowsWindow(int mWidth, int mHeight, const char* mTitle, bool mVSync) {

		//Setting up the window data
		_windowData.Width = mWidth;
		_windowData.Height = mHeight;
		_windowData.Title = mTitle;
		_windowData.VSync = mVSync;

		//Key repeat count conter initialization to 0
		_pressedKeyRepeatCount = 0;

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

		//Create a windowed mode window and its OpenGL context
		init(_windowData.Width, _windowData.Height, _windowData.Title);


		mGui = std::make_unique<Rayer::WindowsGUI>();
		mGui->setupContext((void*)_windowData.window);
		mGui->setFont((parentDir + "/Resources/Font/Padauk-Font.ttf").c_str(), 20.0f);

		//Initializing glew
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {

			std::cerr << "Failed to initialize glew" << std::endl;
			glfwDestroyWindow(_windowData.window);
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

	void WindowsWindow::init(int width, int height, const char* title) {

		_windowData.window = glfwCreateWindow(width, height, title, NULL, NULL);


		if (!_windowData.window) {
			glfwTerminate();
			std::cerr << "Failed to create GLFW window" << std::endl;
			std::terminate();
		}


		// Make the context current
		glfwMakeContextCurrent(_windowData.window);

		// Set the _windowData to the user pointer for further use
		glfwSetWindowUserPointer(_windowData.window, &_windowData);

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<Mouse Callbacks>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		//CALLBACK -> Mouse move callback:
		glfwSetCursorPosCallback(_windowData.window, [](GLFWwindow* window, double xpos, double ypos) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(xpos, ypos);

			data.callback(event);

			});

		//CALLBACK -> Mouse button pressed callback:
		glfwSetMouseButtonCallback(_windowData.window, [](GLFWwindow* window, int button, int action, int mods) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action) {

			case GLFW_PRESS: {
				MouseButtonPressedEvent event(button);
				data.callback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button);
				data.callback(event);
				break;
			}
			}
			
			});

		//CALLBACK -> Mouse wheel callback:
		glfwSetScrollCallback(_windowData.window, [](GLFWwindow* window, double xoffset, double yoffset) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.callback(event);

			});

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<Mouse Callbacks>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


		//<<<<<<<<<<<<<<<<<<<<<<<<<<<Key Callbacks>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			
		glfwSetKeyCallback(_windowData.window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			

			switch (action) {

			case GLFW_PRESS: {
				WindowsWindow::_pressedKeyRepeatCount = 0;
				KeyPressedEvent event(key, WindowsWindow::_pressedKeyRepeatCount);
				data.callback(event);
				break;
			}

			case GLFW_REPEAT: {
				WindowsWindow::_pressedKeyRepeatCount++;
				KeyPressedEvent event(key, WindowsWindow::_pressedKeyRepeatCount);
				data.callback(event);
				break;
			}

			case GLFW_RELEASE: {

				KeyReleasedEvent event(key);
				data.callback(event);
				break;
			}


			}


			});
			
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<Key Callbacks>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<Application Callbacks>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		//CALLBACK -> Window close callback:
		glfwSetWindowCloseCallback(_windowData.window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowClosedEvent event;
			data.callback(event);
			});

		//CALLBACK -> Window resize callback:
		glfwSetWindowSizeCallback(_windowData.window, [](GLFWwindow* window, int width, int height) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowResizedEvent event(width, height);
			data.callback(event);

			});

		//CALLBACK -> Window move callback:
		glfwSetWindowPosCallback(_windowData.window, [](GLFWwindow* window, int xpos, int ypos) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowMovedEvent event(xpos, ypos);
			data.callback(event);

			});

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<Application Callbacks>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



	}

	void WindowsWindow::setIcon(const char* iconPath) {
		icon_data = stbi_load(iconPath, &iWidth, &iHeight, &iChannels, 0);

		if (icon_data) {

			icon.width = iWidth;
			icon.height = iHeight;
			icon.pixels = icon_data;

			// Set the window icon
			glfwSetWindowIcon(_windowData.window, 1, &icon);
		}
	}

	void WindowsWindow::renderWindow() {

		glViewport(0, 0, mViewportSize.x, mViewportSize.y);
		renderer->bindFrameBuffer();
		clearFrame();
		poolEvents();

		mViewportPos = mGui->getViewportPos();
		mViewportSize = mGui->getViewportSize();

		mGui->guiNewFrame();


		renderer->render(shader->getInstance(), RenderType::DrawArrays);
		renderer->unbindFrameBuffer();

		mGui->getGuiPanels(renderer->getRenderTextureID());



		mGui->renderGUI();

		swapBuffers();

	}

	void WindowsWindow::cleanup() {

		mGui->cleanup();

		glfwDestroyWindow(_windowData.window);
		glfwTerminate();
	}

	void WindowsWindow::storeBufferSize() {

		glfwGetFramebufferSize(_windowData.window, &bufferWidth, &bufferHeight);

	}

	void WindowsWindow::clearFrame() {

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void WindowsWindow::SetEventCallback(const EventCallbackFn& callback) {

		_windowData.callback = callback;

	}

	bool WindowsWindow::IsRunnning() {

		return m_Running;
	}

	void WindowsWindow::SetWindowRunningState(bool running) {

		m_Running = running;

	}

	int WindowsWindow::_pressedKeyRepeatCount = 0;


}