#pragma once

#include "Component.hpp"

#include "Flow3D/Input.hpp"

namespace Flow {

	class Rotatable : public Component
	{
		CLASS_DECLARATION(Rotatable)

	public: 
		Rotatable(GameObject* gameObject) : Component(gameObject), m_Input(Input::Get()) {}

		virtual void OnUpdate(double deltaTime) override
		{
			//float velocity = 3.0f * (float)deltaTime;

			if (m_Input.GetKey(Keycode::J))
			{
				GetTransform()->Rotate(Vec3(1.0f, 0.0f, 0.0f), 1.0f);
			}
			if (m_Input.GetKey(Keycode::K))
			{
				GetTransform()->Rotate(Vec3(0.0f, 1.0f, 0.0f), 1.0f);
			}
			if (m_Input.GetKey(Keycode::L))
			{
				GetTransform()->Rotate(Vec3(0.0f, 0.0f, 1.0f), 1.0f);
			}
		}

	private:
		Input& m_Input;

	};
}