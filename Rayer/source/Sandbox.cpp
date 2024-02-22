#include "rpch.h"
#include "Application.h"

static bool guiEnabled = false;

class UiLayer : public Rayer::Layer {
public:
    UiLayer() : Layer("UiLayer") {}

    virtual void OnAttach() override {}
    virtual void OnDetach() override {}
    virtual void OnUpdate() override {}
    virtual void OnEvent(Rayer::Event& e) override {
        

        if (guiEnabled) {
            std::cout << "APP(GUI): " << e.ToString() << std::endl;
            e.m_Handled = true;
        }

        else {
            e.m_Handled = false;
        }
    }
};


class ViewportLayer : public Rayer::Layer {
public:
    ViewportLayer() : Layer("ViewportLayer") {}

    virtual void OnAttach() override {}
    virtual void OnDetach() override {}
    virtual void OnUpdate() override {}
    virtual void OnEvent(Rayer::Event& e) override {

        
		
		if (!guiEnabled) {
            std::cout << "APP(Viewport): " << e.ToString() << std::endl;
			e.m_Handled = true;
		}

        else {
            e.m_Handled = false;
        }


    }
};

class SandBox : public Rayer::Application {
    
public :
    SandBox() : Application(1920, 1080, "Rayer", false) {

		PushLayer(new UiLayer());
		PushLayer(new ViewportLayer());
	}

    

};

int main() {
    
        
    auto app = std::make_unique<SandBox>();

    app->applicationLoop();
       
    

    return 0;
}
