#include "GameObject.hpp"

#include "Log.hpp"

namespace Flow {

	GameObject::GameObject(const Vec3& position, const Vec3& rotation, const Vec3& scale)
		: m_Transform(position, rotation, scale)
	{
	}

	GameObject::~GameObject()
	{
	
	}

	void GameObject::AddChild(GameObject* child)
	{
		m_Children.push_back(child);
		child->GetTransform()->SetParent(&m_Transform);
	}

	void GameObject::AddComponent(Component* component)
	{
		m_Components.push_back(component);
	}

	void GameObject::OnUpdate(double deltaTime)
	{
		// For testing
		FLOW_CORE_INFO("game object at {0}", m_Transform.m_Position.ToString());

		// update itself
		for (unsigned int j = 0; j < m_Components.size(); j++)
		{
			m_Components[j]->OnUpdate(deltaTime);
		}

		// update its children
		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			m_Children[i]->OnUpdate(deltaTime);
		}		
	}

	void GameObject::OnEvent(Event& e)
	{
		for (unsigned int j = 0; j < m_Components.size(); j++)
		{
			m_Components[j]->OnEvent(e);
		}

		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			m_Children[i]->OnEvent(e);
		}
	}

	void GameObject::Render()
	{
		for (unsigned int j = 0; j < m_Components.size(); j++)
		{
			m_Components[j]->Render();
		}

		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			m_Children[i]->Render();
		}
	}
}