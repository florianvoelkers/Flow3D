#pragma once

#ifdef FLOW_PLATFORM_WINDOWS

extern Flow::Application* Flow::CreateApplication();

// Entry Point of the application 
int main(int argc, char** argv)
{
	Flow::Log::Init();

	auto app = Flow::CreateApplication();
	app->Run();
	delete app;
}

#endif