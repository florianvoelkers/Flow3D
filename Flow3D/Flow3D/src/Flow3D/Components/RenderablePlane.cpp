#include "RenderablePlane.hpp"

namespace Flow {

	RenderablePlane::RenderablePlane(GameObject* gameObject, Plane* plane)
		: m_Plane(plane), Component(gameObject)
	{
	}

	RenderablePlane::~RenderablePlane()
	{
		delete m_Plane;
	}

	void RenderablePlane::Render(Mat4 view, Mat4 projection)
	{
		// calculate position of model
		// TODO: consider the parents Transform
		Mat4 model = Mat4();
		model.Translate(Vec3(0.0f, 0.0f, 0.0f)); // necessary to make sure it is at 0, 0, 0 ???
		model.Translate(GetTransform()->m_Position);
		model.Scale(GetTransform()->m_Scale);

		// rotate around all axis; could produce gimbal lock?
		model.Rotate(GetTransform()->m_Rotation.x, Vec3(1, 0, 0));
		model.Rotate(GetTransform()->m_Rotation.y, Vec3(0, 1, 0));
		model.Rotate(GetTransform()->m_Rotation.z, Vec3(0, 0, 1));
		m_Plane->Draw(model, view, projection);
	}
}