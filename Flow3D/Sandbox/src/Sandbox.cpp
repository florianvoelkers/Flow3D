#include "Flow3D.hpp"

// just an example layer to test out the layer stack outside the engine
class ExampleLayer : public Flow::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		FLOW_CLIENT_INFO("example layer added");
	}

	void OnUpdate(double deltaTime) override
	{

	}

	void OnEvent(Flow::Event& event) override 
	{
		// just temporary solution; should dispatch the event and implement the reaction in a seperate function
		if (event.GetEventType() == Flow::KeyPressedEvent::GetStaticType())
		{
			// exit the application when "escape" is pressed
			Flow::KeyPressedEvent& keyPressedEvent = (Flow::KeyPressedEvent&) event;
			if (keyPressedEvent.GetKeyCode() == (int) Flow::Keycode::Escape)
			{
				Flow::Application::Get().Quit();
			}
		}
	}
};

class Sandbox : public Flow::Application
{
public:
	Sandbox()
	{
		FLOW_CLIENT_INFO("Welcome to the Sandbox Application of the Flow3D Engine!");
		PushLayer(new ExampleLayer());
		PushOverlay(new Flow::ImGuiLayer());
	}

	~Sandbox()
	{
	}
};

Flow::Application* Flow::CreateApplication()
{
	return new Sandbox();
}