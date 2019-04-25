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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RenderingEngine::OnUpdate(double deltaTime, const GameObject& root)
	{		
	}

	void RenderingEngine::OnEvent(Event& event)
	{
	}

	void RenderingEngine::Render(const GameObject& root, GameObject* mainCamera)
	{
		glClearColor(0.18f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Mat4 model = Mat4();
		model.Translate(Vec3(0.0f, 0.0f, 0.0f));

		Mat4 view = mainCamera->GetComponent<FreeCamera>().GetViewMatrix();

		Mat4 projection = Mat4();
		projection = Mat4::GetPerspectiveProjection(Math::Radians(mainCamera->GetComponent<FreeCamera>().GetZoom()), (float)m_Window->GetWidth() / (float)m_Window->GetHeight(), 0.1f, 100.0f);

		root.Render(view, projection);
	}
}