#include "GameObject.hpp"

#include "Log.hpp"
#include "Application.hpp"
#include "Components/Component.hpp"

GameObject::GameObject() {}

GameObject::GameObject(const std::string& name, const Vec3& position, const Vec3& rotation, const Vec3& scale, bool isActive)
	: m_Name(name), m_Transform(this, position, rotation, scale), m_IsActive(isActive), m_ObjectID(Application::Get().GetNextObjectID())
{
}

GameObject::~GameObject()
{
	FLOW_CORE_INFO("destructor of {0} called", m_Name);
}

void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_Children.push_back(child);
	child->GetTransform().SetParent(&m_Transform);
	child->SetParent(this);
}

void GameObject::RemoveChild(int gameObjectID)
{
	int index = -1;
	for (int i = 0; i < m_Children.size(); i++)
	{
		if (gameObjectID == m_Children[i]->GetObjectID())
		{
			index = i;
			break;
		}
	}

	std::vector<std::shared_ptr<GameObject>>::iterator iterator = m_Children.begin() + index;
	m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), *iterator));
	std::move(*iterator);
}

void GameObject::RemoveComponent(std::string name)
{
	int index = -1;
	for (int i = 0; i < m_Components.size(); i++)
	{
		std::string currentName = m_Components[i]->GetName();
		if (name == currentName)
		{
			index = i;
			break;
		}
	}

	std::vector<std::shared_ptr<Component>>::iterator iterator = m_Components.begin() + index;
	m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), *iterator));
	std::move(*iterator);
}

GameObject* GameObject::Find(std::string name)
{
	// checks if this is the GameObject we're looking for
	if (name == GetName())
		return this;
		
	// if not check all the children, if they return a GameObject which name is not "NULL", this is the GameObject we're looking for
	for (unsigned int i = 0; i < m_Children.size(); i++)
	{
		GameObject* placeholder = m_Children[i]->Find(name);
		if (placeholder != nullptr)
			return placeholder;
	}

	// if you can't find it, return a nullptr
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

bool GameObject::GetParentsActive()
{
	if (m_Parent != nullptr)
	{
		if (m_Parent->GetParentsActive())
			return m_IsActive;
		else
			return false;
	}			
	else
		return m_IsActive;


	return false;
}

void GameObject::Destroy(GameObject * object)
{
	const std::vector<std::shared_ptr<Component>>& components = object->GetComponents();
	std::vector<std::string> componentNames;

	Scene& currentScene = Application::Get().GetCurrentScene();

	for (unsigned int i = 0; i < components.size(); i++)
	{
		Component& component = *components[i];
		std::string componentName = component.GetName();
		componentNames.push_back(componentName);
	}

	for (unsigned int i = 0; i < componentNames.size(); i++)
	{
		if (componentNames[i] == "DirectionalLight")
		{
			FLOW_CORE_INFO("should be removed from array in scene");
		}
		else if (componentNames[i] == "PointLight")
		{
			currentScene.RemovePointLight(&object->GetComponent<PointLight>());
		}
		else if (componentNames[i] == "SpotLight")
		{
			currentScene.RemoveSpotLight(&object->GetComponent<SpotLight>());
		}
	}

	const std::vector<std::shared_ptr<GameObject>>& children = object->GetChildren();
	for (unsigned int i = 0; i < children.size(); i++)
	{
		const std::vector<std::shared_ptr<Component>>& childrenComponents = children[i]->GetComponents();
		for (unsigned int j = 0; j < childrenComponents.size(); j++)
		{
			const std::string childComponentName = childrenComponents[j]->GetName();
			if (childComponentName == "DirectionalLight")
			{
				FLOW_CORE_INFO("should be removed from array in scene");
			}
			else if (childComponentName == "PointLight")
			{
				currentScene.RemovePointLight(&children[i]->GetComponent<PointLight>());
			}
			else if (childComponentName == "SpotLight")
			{
				currentScene.RemoveSpotLight(&children[i]->GetComponent<SpotLight>());
			}
		}
	}

	object->GetParent()->RemoveChild(object->GetObjectID());
}
