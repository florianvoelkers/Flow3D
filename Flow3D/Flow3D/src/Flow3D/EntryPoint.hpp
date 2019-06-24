#pragma once

#ifdef FLOW_PLATFORM_WINDOWS

extern Application* CreateApplication();

// Entry Point of the application 
int main(int argc, char** argv)
{
	Log::Init();

	auto app = CreateApplication();
	app->Run();
	delete app;
}

#endif