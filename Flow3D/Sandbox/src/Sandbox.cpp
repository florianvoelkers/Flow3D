#include "Flow3D.hpp"

#include <stdio.h>

class Sandbox : public Flow3D::Application
{
public:
	Sandbox()
	{
		printf("Welcome to Flow3D");
	}

	~Sandbox()
	{
	}
};

Flow3D::Application* Flow3D::CreateApplication()
{
	return new Sandbox();
}