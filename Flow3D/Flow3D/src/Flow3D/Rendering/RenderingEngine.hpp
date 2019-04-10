#pragma once


#include "Flow3D/Layer.hpp"
#include "Flow3D/Window.hpp"
#include "Camera.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shapes/Cube.hpp"
#include "Shapes/Plane.hpp"

namespace Flow {

	class RenderingEngine : public Layer
	{
	public:
		RenderingEngine(const Window& window);
		virtual ~RenderingEngine() {}

		void OnUpdate(double deltaTime) override;
		void OnEvent(Event& event) override;

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