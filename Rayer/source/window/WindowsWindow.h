#pragma once

#include<filesystem>
namespace fs = std::filesystem;

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "rpch.h"
#include "window.h"
#include <STB/stb_image.h>
#include "gui/WindowsGUI.h"

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

		void renderGui() {

			mGui->renderGUI();
		}

		virtual void setIcon(const char* iconPath) override;
		virtual void clearFrame() override;
		virtual void cleanup() override;


	private:
		int Width;
		int Height;
		const char* Title;
		GLFWwindow* window;

		//************Window Icon properties************
		GLFWimage icon;
		unsigned char* icon_data;
		int iWidth, iHeight, iChannels;

		//**************For gui***************
		std::unique_ptr<Rayer::WindowsGUI> mGui = nullptr;

		std::string parentDir;
		


	};
}