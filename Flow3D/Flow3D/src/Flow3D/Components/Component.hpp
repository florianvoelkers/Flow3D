#pragma once

#include "Flow3D/Transform.hpp"
#include "Flow3D/GameObject.hpp"

namespace Flow {

	class Component
	{
	public:
		Component(GameObject* gameObject) : m_GameObject(gameObject) {}
		virtual ~Component() {}

		virtual void OnUpdate (double deltaTime) {}
		virtual void OnEvent (Event& event) {}
		virtual void Render (Mat4 view, Mat4 projection) {}

		inline Transform* GetTransform() { return m_GameObject->GetTransform(); }
		inline const Transform& GetTransform() const { return *m_GameObject->GetTransform(); }

	protected:
		GameObject* m_GameObject;
	};
}
