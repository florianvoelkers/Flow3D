#pragma once

#include "Flow3D/Window.hpp"
#include "Camera.hpp"

#include "glad/glad.h"
#include "GLFW/include/GLFW/glfw3.h"

#include "Shapes/Cube.hpp"
#include "Shapes/Plane.hpp"

namespace Flow {

	class RenderingEngine
	{
	public:
		RenderingEngine(const Window& window);
		virtual ~RenderingEngine() {}

		void OnUpdate(double deltaTime);
		void OnEvent(Event& event);

		void Render();
		// TODO
		// Light functions
		// SetCamera

	private:
		const Window* m_Window;
		Camera* m_Camera;

		// just for testing purposes
		Cube* testCube;
		Cube* redCube;
		Cube* yellowCube;
		Plane* testPlane;
	};
}