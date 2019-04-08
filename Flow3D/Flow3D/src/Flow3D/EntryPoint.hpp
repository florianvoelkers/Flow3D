#pragma once

#ifdef FLOW_PLATFORM_WINDOWS

extern Flow3D::Application* Flow3D::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Flow3D::CreateApplication();
	app->Run();
	delete app;
}

#endif