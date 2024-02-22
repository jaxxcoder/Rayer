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

#include "event/Event.h"
#include "event/MouseEvent.h"
#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"

namespace Rayer {
	
	class WindowsWindow : public Rayer::IWindow {

	public:

		//Key repeat count conter
		static int _pressedKeyRepeatCount;

		using EventCallbackFn = std::function<void(Event&)>;

		WindowsWindow(int mWidth, int mHeight, const char* mTitle , bool mVSync);

		virtual void init(int width, int height, const char* title) override;

		virtual void* getNativeWindow() override {

			return (void*)_windowData.window;
		}

		virtual bool shouldClose() const override {

			return glfwWindowShouldClose(_windowData.window);
		}

		virtual void swapBuffers() const override {

			glfwSwapBuffers(_windowData.window);
		}

		virtual int getWindowWidth() const override {

			return _windowData.Width;
		}

		virtual int getWindowHeight() const override {

			return _windowData.Height;
		}

		
		virtual void poolEvents() const override {

			glfwPollEvents();
		}


		virtual void maximizeWindow() const override {

			glfwMaximizeWindow(_windowData.window);
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

		void SetEventCallback(const EventCallbackFn& callback);

		bool IsRunnning();

		void SetWindowRunningState(bool running);
	

	private:

		//Window data section
		struct WindowData{
			int Width;
			int Height;
			bool VSync;
			const char* Title;
			GLFWwindow* window;
			EventCallbackFn callback;

		};
		
		WindowData _windowData;

		//Window running state variable
		bool m_Running = true;
		

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