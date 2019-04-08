#include "Flow3D.hpp"

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
};

class Sandbox : public Flow::Application
{
public:
	Sandbox()
	{
		FLOW_CLIENT_INFO("Welcome to the Sandbox Application of the Flow3D Engine!");
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Flow::Application* Flow::CreateApplication()
{
	return new Sandbox();
}