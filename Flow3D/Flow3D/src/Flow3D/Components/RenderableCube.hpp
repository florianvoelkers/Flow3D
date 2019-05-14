#pragma once

#include "Component.hpp"

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shapes/Cube.hpp"

namespace Flow {

	// Constructor: RenderableCube(GameObject* gameObject, Cube* cube)
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
			model.Translate(GetTransform()->GetPosition());
			model.Scale(GetTransform()->GetScale());

			// rotate around all axis; could produce gimbal lock?
			model.Rotate(GetTransform()->GetRotation().x, Vec3(1, 0, 0));
			model.Rotate(GetTransform()->GetRotation().y, Vec3(0, 1, 0));
			model.Rotate(GetTransform()->GetRotation().z, Vec3(0, 0, 1));

			m_Cube->Draw(model, view, projection, renderingEngine);
		}

	private:
		Cube* m_Cube;
	};
}