#pragma once

#include "Component.hpp"

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shapes/Plane.hpp"

namespace Flow {

	// Gives functionality to render a 2 dimensional plane at the position of the GameObject with the anchor of the Plane in the middle; 
	class RenderablePlane : public Component
	{
		CLASS_DECLARATION(RenderablePlane)

	public:
		RenderablePlane(GameObject* gameObject, Plane* plane)
			: m_Plane(plane), Component(gameObject)
		{
		}

		~RenderablePlane()
		{
			delete m_Plane;
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
			m_Plane->Draw(model, view, projection);
		}

	private:
		Plane* m_Plane;
	};
}