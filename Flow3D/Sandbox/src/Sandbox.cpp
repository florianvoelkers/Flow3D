#include "Flow3D.hpp"


class Sandbox : public Flow::Application
{
public:
	Sandbox()
	{
		FLOW_CLIENT_INFO("Welcome to the Sandbox Application of the Flow3D Engine!");
	}

	~Sandbox()
	{
	}
};

Flow::Application* Flow::CreateApplication()
{
	return new Sandbox();
}