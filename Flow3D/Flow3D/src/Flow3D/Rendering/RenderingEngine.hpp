#pragma once

#include "Flow3D/Window.hpp"

#include "glad/glad.h"
#include "GLFW/include/GLFW/glfw3.h"

#include "Flow3D/GameObject.hpp"
#include "Skybox.hpp"

// Handles rendering graphics with OpenGL in a GLFW Window
class RenderingEngine
{
public:
	RenderingEngine(const Window& window);
	virtual ~RenderingEngine() {}

	void Render(const GameObject& root, GameObject& mainCamera, Skybox& skybox);
	void SetBlending(bool blending);

	inline const Vec3 GetViewPosition() const { return viewPosition; }
	inline const unsigned int GetRenderTexture() const { return m_RenderTexture; }

private:
	const Window& m_Window;
	Vec3 viewPosition;
	unsigned int m_RenderTexture;
	unsigned int m_Framebuffer;
};
