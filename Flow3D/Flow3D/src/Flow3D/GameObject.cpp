#include "GameObject.hpp"

#include "Log.hpp"

#include "Components/Component.hpp"

namespace Flow {

	GameObject::GameObject(const Vec3& position, const Vec3& rotation, const Vec3& scale, bool isActive)
		: m_Transform(position, rotation, scale), m_IsActive(isActive)
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