#pragma once
#include "rpch.h"
#include "window.h"

namespace Rayer {
	
	class WindowsWindow : public Rayer::IWindow {

	public:

		WindowsWindow(int mWidth, int mHeight, const char* mTitle);

		virtual void* init(int width, int height, const char* title) override;

		virtual void* getNativeWindow() override {

			return (void*)window;
		}

		virtual bool shouldClose() const override {

			return glfwWindowShouldClose(window);
		}

		virtual void swapBuffers() const override {

			glfwSwapBuffers(window);
		}

		virtual int getWindowWidth() const override {

			return Width;
		}

		virtual int getWindowHeight() const override {

			return Height;
		}

		virtual void setContext() const override {

			glfwMakeContextCurrent(window);
		}
		
		virtual void poolEvents() const override {

			glfwPollEvents();
		}

		virtual void renderWindow() const override {

			poolEvents();
			swapBuffers();
		}

		virtual void maximizeWindow() const override {

			glfwMaximizeWindow(window);
		}


	private:
		int Width;
		int Height;
		const char* Title;
		GLFWwindow* window;

	};
}