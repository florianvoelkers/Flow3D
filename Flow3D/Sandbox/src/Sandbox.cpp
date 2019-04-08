#include "Flow3D.hpp"

class Sandbox : public Flow3D::Application
{
public:
	Sandbox()
	{
		FLOW_CORE_INFO("Welcome to the Sandbox Application of the Flow3D Engine!");
	}

	~Sandbox()
	{
	}
};

Flow3D::Application* Flow3D::CreateApplication()
{
	return new Sandbox();
}