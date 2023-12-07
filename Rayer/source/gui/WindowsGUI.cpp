#include "WindowsGUI.h"
#include "rpch.h"

namespace Rayer {

    void WindowsGUI::cleanup() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void WindowsGUI::setupContext(void* gWindow) {
        // Initialize ImGui context
        IMGUI_CHECKVERSION();
        ImGuiContext* context = ImGui::CreateContext();
        if (context == NULL) {
            std::cout << "Failed to create ImGui context" << std::endl;
        }

        ImGui::SetCurrentContext(context);
        
        io = &ImGui::GetIO();

        // Setup ImGui for GLFW and OpenGL3
        bool initGlfw = ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)gWindow, true);
        if (!initGlfw) {
            std::cout << "Failed to initialize ImGui for GLFW" << std::endl;
        }

        const char* glslVersion = "#version 330";
        bool initGl3 = ImGui_ImplOpenGL3_Init(glslVersion);
        if (!initGl3) {
            std::cout << "Failed to initialize ImGui for OpenGL3 with GLSL version " << glslVersion << std::endl;
        }

        io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking

        style = &ImGui::GetStyle();

        setStyle(*io, *style);

    }

    void WindowsGUI::getGuiPanels(GLuint renderTextureID) {

        //Inspector window
        ImGui::Begin("Inspector");

        ImGui::Text("This is the inspector");


        ImGui::End();

        //Viewport window
        ImGui::Begin("Viewport");

        viewportSize = ImGui::GetContentRegionAvail();
        ImGui::Image((void*)(intptr_t)renderTextureID, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();

    }

    void WindowsGUI::renderGUI() {

   
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    

    void WindowsGUI::setFont(const char* fontPath , float fontSize) {

        ImFont* customFont = io->Fonts->AddFontFromFileTTF(fontPath, fontSize);

        // If you want to set this font as the default, you can do so:
        io->FontDefault = customFont;

    }

    void WindowsGUI::guiNewFrame() {

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // Create a dockspace
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    }

    void WindowsGUI::setStyle(ImGuiIO& io, ImGuiStyle& style) {

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;

        }

    }


    ImVec2 WindowsGUI::getViewportPos() {

        return viewportPos;
    }

    ImVec2 WindowsGUI::getViewportSize() {

        return viewportSize;
    }
}
