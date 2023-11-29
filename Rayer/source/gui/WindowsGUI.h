#pragma once

#include "gui.h"

//ImGui includes
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Rayer {

	class WindowsGUI : public Rayer::IGui {

	public:
		

		virtual void renderGUI() override;
		virtual void setFont(const char* fontPath , float fontSize) override;
		virtual void setupContext(void* gWindow) override;
		virtual void cleanup() override;

	private:
		
		ImGuiIO* io = nullptr;

	};

}