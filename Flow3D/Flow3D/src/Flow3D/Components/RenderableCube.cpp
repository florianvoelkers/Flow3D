#include "RenderableCube.hpp"

#include "Flow3D/Log.hpp"

namespace Flow {

	RenderableCube::RenderableCube(GameObject* gameObject, Cube* cube)
		: m_Cube(cube), Component(gameObject)
	{

	}

	RenderableCube::~RenderableCube()
	{
		delete m_Cube;
	}

	void RenderableCube::Render(Mat4 view, Mat4 projection)
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

		m_Cube->Draw(model, view, projection);		
	}
}
