#pragma once

#include <string>
#include <vector>

#include "Math.hpp"
#include "Events/Event.hpp"
#include "Transform.hpp"

namespace Flow {

	class Component; // because GameObject.hpp needs to be included in Component

	class GameObject 
	{
	public:
		GameObject(const Vec3& position = Vec3(0.0f), const Vec3& rotation = Vec3(0.0f), const Vec3& scale = Vec3(1.0f));
		virtual ~GameObject();

		void AddChild(GameObject* child);
		void AddComponent(Component* component);

		void OnUpdate(double deltaTime);
		void OnEvent(Event& e);
		void Render(Mat4 view, Mat4 projection) const;

		void SetActive(bool isActive) { m_IsActive = isActive; }
		inline Transform* GetTransform() { return &m_Transform; }
		
	private: 
		bool m_IsActive;
		std::vector<GameObject*> m_Children;
		Transform m_Transform;
		std::vector<Component*> m_Components;
	};
}