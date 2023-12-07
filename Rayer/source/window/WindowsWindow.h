#pragma once

#define GLEW_STATIC

#include<filesystem>
namespace fs = std::filesystem;

#include "rpch.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "window.h"
#include <STB/stb_image.h>
#include "gui/WindowsGUI.h"
#include "render/OpenGL_Renderer.h"
#include "render/Shader.h"

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


		virtual void maximizeWindow() const override {

			glfwMaximizeWindow(window);
		}

		void newFrameGUI() {

			mGui->guiNewFrame();

		}

		virtual void storeBufferSize() override;

		virtual void setIcon(const char* iconPath) override;
		virtual void clearFrame() override;
		virtual void renderWindow()  override;
		virtual void cleanup() override;
		OpenGL_Renderer* getRenderer() {

			return renderer.get();
		}


	private:
		int Width;
		int Height;
		const char* Title;
		GLFWwindow* window;

		

		//************Window Icon properties************
		GLFWimage icon;
		unsigned char* icon_data;
		int iWidth, iHeight, iChannels;

		//************Frame Buffer*******************
		int bufferWidth;
		int bufferHeight;

		//**************For gui***************
		std::unique_ptr<Rayer::WindowsGUI> mGui = nullptr;

		std::string parentDir;

		//***********Rendering Stuff***************
		std::unique_ptr<OpenGL_Renderer> renderer = nullptr;
		std::unique_ptr<Shader> shader = nullptr;

		//***********Viewport Stuff****************
		ImVec2 mViewportSize;
		ImVec2 mViewportPos;

	};
}