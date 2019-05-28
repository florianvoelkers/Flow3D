#include "GameObject.hpp"

#include "Log.hpp"

#include "Components/Component.hpp"

namespace Flow {

	GameObject::GameObject()
		: m_Name("NULL")
	{
	}

	GameObject::GameObject(const std::string& name, const Vec3& position, const Vec3& rotation, const Vec3& scale, bool isActive)
		: m_Name(name), m_Transform(position, rotation, scale), m_IsActive(isActive)
	{
	}

	GameObject::~GameObject()
	{
		m_Children.clear();
	}

	void GameObject::AddChild(GameObject* child)
	{
		m_Children.push_back(child);
		child->GetTransform()->SetParent(&m_Transform);
	}

	GameObject* GameObject::Find(std::string name)
	{
		FLOW_CORE_INFO("this game objects name is {0}", GetName());
		// checks if this is the GameObject we're looking for
		if (name == GetName())
			return this;
		
		// if not check all the children, if they return a GameObject which name is not "NULL", this is the GameObject we're looking for
		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			GameObject* placeholder = m_Children[i]->Find(name);
			if (placeholder != nullptr)
			{
				FLOW_CORE_INFO("the name is {0} equal to {1}", placeholder->GetName(), name);
				return placeholder;
			}
		}

		// if you can't find it, return a nullptr
		FLOW_CORE_INFO("return null object");
		return nullptr;
	}

	void GameObject::OnUpdate(double deltaTime)
	{
		if (m_IsActive)
		{
			// update itself
			for (unsigned int j = 0; j < m_Components.size(); j++)
			{
				if (m_Components[j]->GetEnabled())
					m_Components[j]->OnUpdate(deltaTime);
			}

			// update its children
			for (unsigned int i = 0; i < m_Children.size(); i++)
			{
				m_Children[i]->OnUpdate(deltaTime);
			}
		}		
	}

	void GameObject::OnEvent(Event& e)
	{
		if (m_IsActive)
		{
			for (unsigned int j = 0; j < m_Components.size(); j++)
			{
				if (m_Components[j]->GetEnabled())
					m_Components[j]->OnEvent(e);
			}

			for (unsigned int i = 0; i < m_Children.size(); i++)
			{
				m_Children[i]->OnEvent(e);
			}
		}
	}

	void GameObject::Render(Mat4 view, Mat4 projection, RenderingEngine& renderingEngine) const
	{
		if (m_IsActive)
		{
			for (unsigned int j = 0; j < m_Components.size(); j++)
			{
				if (m_Components[j]->GetEnabled())
					m_Components[j]->Render(view, projection, renderingEngine);
			}

			for (unsigned int i = 0; i < m_Children.size(); i++)
			{
				m_Children[i]->Render(view, projection, renderingEngine);
			}
		}
	}
}