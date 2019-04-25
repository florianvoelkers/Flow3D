#pragma once

#include "Flow3D/Window.hpp"
#include "Camera.hpp"

#include "glad/glad.h"
#include "GLFW/include/GLFW/glfw3.h"

#include "Shapes/Cube.hpp"
#include "Shapes/Plane.hpp"

#include "Flow3D/GameObject.hpp"

namespace Flow {

	class RenderingEngine
	{
	public:
		RenderingEngine(const Window& window);
		virtual ~RenderingEngine() {}

		void OnUpdate(double deltaTime, const GameObject& root);
		void OnEvent(Event& event);

		void Render(const GameObject& root);
		// TODO
		// Light functions
		// SetCamera

	private:
		const Window* m_Window;
		Camera* m_Camera;

	};
}