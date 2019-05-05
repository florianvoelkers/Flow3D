#pragma once

#include "Flow3D/Window.hpp"

#include "glad/glad.h"
#include "GLFW/include/GLFW/glfw3.h"

#include "Shapes/Cube.hpp"
#include "Shapes/Plane.hpp"

#include "Flow3D/GameObject.hpp"

// TEMPORARY
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Model.hpp"
#include "Shader.hpp"

namespace Flow {

	// Handles rendering graphics with OpenGL in a GLFW Window
	class RenderingEngine
	{
	public:
		RenderingEngine(const Window& window);
		virtual ~RenderingEngine() {}

		void Render(const GameObject& root, GameObject* mainCamera); // TODO: is it bad to pass a pointer here?
		// TODO:
		// Light functions
		// SetCamera

	private:
		const Window* m_Window;

		// TEMPORARY
		Shader* modelShader;
		Model* testModel;
		Model* nanosuit;
	};
}