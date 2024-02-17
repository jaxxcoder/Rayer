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


        //Setting up imgui window style

        //Start
        style->Colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };
        
        style->Colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
        style->Colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
        style->Colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
        
        style->Colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
        style->Colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
        style->Colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
        
        style->Colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
        style->Colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
        style->Colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
        
        style->Colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
        style->Colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.38f, 0.38f, 1.0f };
        style->Colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.28f, 0.28f, 1.0f };
        style->Colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
        style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
        
        style->Colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
        style->Colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
        style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

        ImGuiStyle* style = &ImGui::GetStyle();
        if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style->WindowRounding = 0.0f;
            style->Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        //End

    }

    void WindowsGUI::MenuBar() {


        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Create")) {
                }
                if (ImGui::MenuItem("Open", "Ctrl+O")) {
                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) {
                }
                if (ImGui::MenuItem("Save as..")) {
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Settings")) {
                if (ImGui::MenuItem("Create")) {
                }
                if (ImGui::MenuItem("Prefrences", "Ctrl+O")) {
                }
                if (ImGui::MenuItem("Project Settings", "Ctrl+Q")) {
                }
                
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help")) {
                if (ImGui::MenuItem("About Rayer")) {

                    
                }
                
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

    }

    void WindowsGUI::getGuiPanels(GLuint renderTextureID) {

        

        MenuBar();

        //Inspector window
        ImGui::Begin("Inspector");

        


        ImGui::End();

        //Viewport window
        ImGui::Begin("Viewport");

        viewportSize = ImGui::GetContentRegionAvail();
        ImGui::Image((void*)(intptr_t)renderTextureID, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();

        //Content Browser window 
        ImGui::Begin("Content Browser");

        

        ImGui::End();


        //Properties window 
        ImGui::Begin("Properties");

       

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
