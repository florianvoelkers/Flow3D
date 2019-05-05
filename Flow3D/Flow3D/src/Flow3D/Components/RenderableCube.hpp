#pragma once

#include "Component.hpp"

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shapes/Cube.hpp"

namespace Flow {

	// Gives functionality and data for drawing a cube at the position of the GameObject with anchor in the middle
	class RenderableCube : public Component 
	{
		CLASS_DECLARATION(RenderableCube)

	public:
		RenderableCube(GameObject* gameObject, Cube* cube)
			: m_Cube(cube), Component(gameObject)
		{

		}

		~RenderableCube()
		{
			delete m_Cube;
		}
		
		virtual void Render(Mat4 view, Mat4 projection, RenderingEngine& renderingEngine) override
		{
			// calculate position of model
			// TODO: consider the parents Transform
			Mat4 model = Mat4();
			model.Translate(GetTransform()->m_Position);
			model.Scale(GetTransform()->m_Scale);

			// rotate around all axis; could produce gimbal lock?
			model.Rotate(GetTransform()->m_Rotation.x, Vec3(1, 0, 0));
			model.Rotate(GetTransform()->m_Rotation.y, Vec3(0, 1, 0));
			model.Rotate(GetTransform()->m_Rotation.z, Vec3(0, 0, 1));

			m_Cube->Draw(model, view, projection);
		}

	private:
		Cube* m_Cube;
	};
}