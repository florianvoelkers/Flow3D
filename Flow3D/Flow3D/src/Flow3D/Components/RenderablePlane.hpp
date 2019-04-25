#pragma once

#include "Component.hpp"

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shapes/Plane.hpp"

namespace Flow {

	// temporary solution to test GameObject / Component architecture
	// Goal: stores Mesh and Material to create Model that needs to be rendered 
	class RenderablePlane : public Component
	{
	public:
		RenderablePlane(GameObject* gameObject, Plane* plane);
		~RenderablePlane();

		virtual void Render(Mat4 view, Mat4 projection) override;

	private:
		Plane* m_Plane;
	};
}