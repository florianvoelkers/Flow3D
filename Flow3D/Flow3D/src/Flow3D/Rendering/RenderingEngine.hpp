#pragma once

#include "Flow3D/Window.hpp"

#include "glad/glad.h"
#include "GLFW/include/GLFW/glfw3.h"

#include "Flow3D/GameObject.hpp"
#include "Skybox.hpp"

namespace Flow {

	// Handles rendering graphics with OpenGL in a GLFW Window
	class RenderingEngine
	{
	public:
		RenderingEngine(const Window& window);
		virtual ~RenderingEngine() {}

		void Render(const GameObject& root, GameObject* mainCamera, const Skybox& skybox); // TODO: is it bad to pass a pointer here?
		// TODO:
		// Light functions
		// SetCamera
		void SetBlending(bool blending);

	private:
		const Window* m_Window;
	};
}