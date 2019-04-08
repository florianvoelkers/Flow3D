#pragma once

namespace Flow3D {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// to be defined in client
	Application* CreateApplication();
}
