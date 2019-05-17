#pragma once

#include "Component.hpp"

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shapes/Plane.hpp"

namespace Flow {

	// Constructor: RenderablePlane(GameObject* gameObject, Plane* plane)
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
			Mat4 model = Mat4(GetTransform()->GetTransformation());
			m_Plane->Draw(model, view, projection, renderingEngine);
		}

	private:
		Plane* m_Plane;
	};
}