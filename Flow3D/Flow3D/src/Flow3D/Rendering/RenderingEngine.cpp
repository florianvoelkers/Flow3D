#include "RenderingEngine.hpp"

#include "Flow3D/Log.hpp"
#include "Flow3D/Math.hpp"

#include "Flow3D/Components/FreeCamera.hpp"

#include "Texture.hpp"

namespace Flow {

	RenderingEngine::RenderingEngine(const Window& window)
		: m_Window(&window)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		// every Model will determine if GL_BLEND needs to be enabled: glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

	void RenderingEngine::Render(const GameObject& root, GameObject* mainCamera, const Skybox& skybox)
	{
		viewPosition = mainCamera->GetTransform()->m_Position;
		// when beginning to render clear everything
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// receive the view matrix from the current main camera
		Mat4 view = mainCamera->GetComponent<FreeCamera>().GetViewMatrix();

		// get the projection matrix
		Mat4 projection = Mat4();
		projection = Mat4::GetPerspectiveProjection(Math::Radians(mainCamera->GetComponent<FreeCamera>().GetZoom()), (float)m_Window->GetWidth() / (float)m_Window->GetHeight(), 0.1f, 100.0f);

		// render the scene starting with the scenes root object which contains all scene objects
		root.Render(view, projection, *this);
		//skybox.Draw(view, projection);
	}

	void RenderingEngine::SetBlending(bool blending)
	{
		if (blending)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
	}
}