#pragma once

#include <string>
#include <vector>

#include "Math.hpp"
#include "Events/Event.hpp"
#include "Transform.hpp"

namespace Flow {

	class Component; // because GameObject.hpp needs to be included in Component
	class RenderingEngine;

	// A game object represents one entity in the application. This can be anything, e.g. the player, a lamp, a collider,
	// depending on what components make up the GameObject. The GameObject can also have a number of game objects as children.
	// The position, rotation and scale of the game object is saved in the Transform and depends on it's parents objects.
	class GameObject 
	{
	public:
		GameObject();
		GameObject(const std::string& name, const Vec3& position = Vec3(0.0f), const Vec3& rotation = Vec3(0.0f), const Vec3& scale = Vec3(1.0f), bool isActive = true);
		virtual ~GameObject();

		void AddChild(GameObject* child);

		// from: https://stackoverflow.com/questions/44105058/how-does-unitys-getcomponent-work
		template<class ComponentType, typename... Args>
		void AddComponent(Args&&... params);
		
		template<class ComponentType, typename... Args>
		ComponentType& GetComponent();

		template<class ComponentType>
		bool RemoveComponent();

		GameObject* Find(std::string name);

		void OnUpdate(double deltaTime);
		void OnEvent(Event& e);
		void Render(Mat4 view, Mat4 projection, RenderingEngine& renderingEngine) const;

		void SetActive(bool isActive) { m_IsActive = isActive; }
		inline Transform* GetTransform() { return &m_Transform; }
		inline const std::string GetName() const { return m_Name; }
		
	private: 
		bool m_IsActive;
		std::vector<GameObject*> m_Children;
		Transform m_Transform;
		std::vector<std::unique_ptr<Component>> m_Components;
		std::string m_Name;
	};

	//***************
	// GameObject::AddComponent
	// perfect-forwards all params to the ComponentType constructor with the matching parameter list
	// DEBUG: be sure to compare the arguments of this fn to the desired constructor to avoid perfect-forwarding failure cases
	// EG: deduced initializer lists, decl-only static const int members, 0|NULL instead of nullptr, overloaded fn names, and bitfields
	//***************
	template<class ComponentType, typename ...Args>
	inline void GameObject::AddComponent(Args&& ...params)
	{
		m_Components.emplace_back(new ComponentType(std::forward<Args>(params)...));
	}

	//***************
	// GameObject::GetComponent
	// returns the first component that matches the template type
	// or that is derived from the template type
	// EG: if the template type is Component, and components[0] type is BoxCollider
	// then components[0] will be returned because it derives from Component
	//***************
	template<class ComponentType, typename ...Args>
	inline ComponentType& GameObject::GetComponent()
	{
		for (auto&& component : m_Components)
		{
			if (component->IsClassType(ComponentType::Type))
				return *static_cast<ComponentType*>(component.get());
		}

		return *std::unique_ptr< ComponentType >(nullptr);
	}

	//***************
	// GameObject::RemoveComponent
	// returns true on successful removal
	// returns false if components is empty, or no such component exists
	//***************
	template<class ComponentType>
	inline bool GameObject::RemoveComponent()
	{
		if (m_Components.empty())
			return false;

		auto& index = std::find_if(m_Components.begin(), 
			m_Components.end(),
			[classType = ComponentType::Type](auto& component) {
			return component->IsClassType();
		});

		bool success = index != m_Components.end();

		if (success)
			m_Components.erase(index);

		return success;
	}
}