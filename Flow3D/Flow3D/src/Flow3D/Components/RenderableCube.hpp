#pragma once

#include "Component.hpp"

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shapes/Cube.hpp"

namespace Flow {

	class RenderableCube : public Component 
	{
	public:
		RenderableCube(GameObject* gameObject, Cube* cube);
		~RenderableCube();
		
		virtual void Render(Mat4 view, Mat4 projection) override;

	private:
		Cube* m_Cube;
	};
}