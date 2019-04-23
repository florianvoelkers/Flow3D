#include "RenderingEngine.hpp"

#include "Flow3D/Log.hpp"
#include "Flow3D/Math.hpp"

#include "Texture.hpp"

namespace Flow {

	RenderingEngine::RenderingEngine(const Window& window)
		: m_Window(&window)
	{
		m_Camera = new Camera(Vec3(0.0f, 0.0f, 3.0f));
		m_Camera->SetWindow(*m_Window);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Texture logoTexture("resources/textures/logo.png", "diffuse");
		Texture containerTexture("resources/textures/container.jpg", "diffuse");
		Texture wallTexture("resources/textures/wall.jpg", "diffuse");
		Texture brickTexture("resources/textures/brickwall.jpg", "diffuse");
		testCube = new Cube(brickTexture);
		redCube = new Cube(containerTexture);
		yellowCube = new Cube(containerTexture);
		testPlane = new Plane(wallTexture);
	}

	void RenderingEngine::OnUpdate(double deltaTime)
	{
		m_Camera->OnUpdate(deltaTime);
		Render();
	}

	void RenderingEngine::OnEvent(Event& event)
	{
		m_Camera->OnEvent(event);
	}

	void RenderingEngine::Render()
	{
		glClearColor(0.18f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Mat4 model = Mat4();
		model.Translate(Vec3(0.0f, 0.0f, 0.0f));

		Mat4 view = m_Camera->GetViewMatrix();

		Mat4 projection = Mat4();
		projection = Mat4::GetPerspectiveProjection(Math::Radians(m_Camera->m_Zoom), (float)m_Window->GetWidth() / (float)m_Window->GetHeight(), 0.1f, 100.0f);

		model.Translate(Vec3(0.0f, 0.5f, 0.0f));
		testCube->Draw(model, view, projection);

		model.Translate(Vec3(-1.5f, 0.0f, 0.0f));
		redCube->Draw(model, view, projection);

		model.Translate(Vec3(3.0f, 0.0f, 0.0f));
		yellowCube->Draw(model, view, projection);

		model.Translate(Vec3(-1.5f, -0.51f, 0.0f));
		model.Scale(Vec3(10.0f));
		model.Rotate(90.0f, Vec3(1, 0, 0));
		testPlane->Draw(model, view, projection);
	}
}