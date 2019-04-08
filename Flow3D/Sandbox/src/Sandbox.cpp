#include "Flow3D.hpp"

class Sandbox : public Flow3D::Application
{
public:
	Sandbox()
	{
		FLOW_CLIENT_INFO("Welcome to the Sandbox Application of the Flow3D Engine!");
		Flow::Mat4 testMatrix = Flow::Mat4();
		FLOW_CLIENT_INFO("identity matrix is {0}", testMatrix.ToString());
	}

	~Sandbox()
	{
	}
};

Flow3D::Application* Flow3D::CreateApplication()
{
	return new Sandbox();
}