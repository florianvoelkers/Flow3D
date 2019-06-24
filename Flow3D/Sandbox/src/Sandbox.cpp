#include "Flow3D.hpp"


class Sandbox : public Application
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

Application* CreateApplication()
{
	return new Sandbox();
}