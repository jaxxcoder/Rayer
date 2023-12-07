#pragma once

#include "gui.h"

//ImGui includes
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Rayer {

	class WindowsGUI : public Rayer::IGui {

	public:
		
		virtual void getGuiPanels(GLuint renderTextureID) override;
		virtual void renderGUI() override;
		virtual void setFont(const char* fontPath , float fontSize) override;
		virtual void setupContext(void* gWindow) override;
		virtual void cleanup() override;
		void guiNewFrame();
		void setStyle(ImGuiIO& io , ImGuiStyle& style);
		ImVec2 getViewportSize();
		ImVec2 getViewportPos();

	private:
		
		ImGuiIO* io = nullptr;
		ImGuiStyle* style = nullptr;
		ImVec2 viewportSize;
		ImVec2 viewportPos;
	};

}