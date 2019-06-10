#include "Transform.hpp"

#include "Flow3D/Log.hpp"
#include "GameObject.hpp"

namespace Flow {

	Transform::Transform(const GameObject& gameObject, const Vec3& position, const Vec3& rotation, const Vec3& scale)
		: m_GameObject(gameObject), m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{
		m_WorldUp = Vec3(0.0f, 1.0f, 0.0f);
		m_Orientation = Quaternion(m_Rotation);
		m_IsCamera = false;

		UpdateVectors();
	}

	void Transform::Translate(const Vec3& translation)
	{
		m_Position += translation;
	}

	void Transform::Rotate(const Vec3& amount)
	{
		m_Rotation += amount;
		m_Orientation = Quaternion(m_Rotation);
		UpdateVectors();
	}

	void Transform::SetOrientation(const Quaternion & orientation)
	{
		m_Orientation = orientation;
		m_Rotation = m_Orientation.ToEulerAngles();
	}

	void Transform::SetRotation(const Vec3& rotation)
	{ 
		m_Rotation = rotation; 
		m_Orientation = Quaternion(m_Rotation);
		UpdateVectors();
	}

	void Transform::SetIsCamera(bool isCamera)
	{
		m_IsCamera = isCamera;
	}

	Mat4 Transform::GetTransformation() const
	{
		Mat4 translationMatrix = Mat4();
		translationMatrix.Translate(m_Position);

		Mat4 rotationMatrix;
		
		if (m_IsCamera)
		{
			Vec3 adjustedEuler = Vec3(-1 * m_Rotation.x, -1 * m_Rotation.y, - 1 * m_Rotation.z);
			rotationMatrix = Quaternion(adjustedEuler).ToMat4();
		}
		else
		{
			// This produces gimbal lock when z is 90 or 270°
			Quaternion rotation = Quaternion(Vec3(0.0f, m_Rotation.y, 0.0f));
			rotation = rotation * Quaternion(Vec3(0.0f, 0.0f, m_Rotation.z));
			rotation = rotation * Quaternion(Vec3(m_Rotation.x, 0.0f, 0.0f));			

			rotationMatrix = rotation.ToMat4();
		}
			

		Mat4 scaleMatrix = Mat4();
		scaleMatrix.Scale(m_Scale);

		Mat4 result = translationMatrix * rotationMatrix * scaleMatrix;
		if (m_Parent != nullptr) 
			result = m_Parent->GetTransformation() * result;		

		return result;
	}

	const Vec3 Transform::GetWorldPosition() const
	{
		Vec3 position = Vec3(0.0f);
		if (m_Parent != nullptr)
			position = m_Parent->GetWorldPosition();

		position += m_Position;

		return position;
	}

	const Vec3 Transform::GetWorldRotation() const
	{
		Vec3 rotation = Vec3(0.0f);
		if (m_Parent != nullptr)
			rotation = m_Parent->GetWorldRotation();

		rotation += m_Rotation;

		return rotation;
	}

	const Quaternion Transform::GetOrientation() const
	{
		return m_Orientation;
	}

	const Vec3 Transform::GetWorldScale() const
	{
		Vec3 scale = Vec3(1.0f);
		if (m_Parent != nullptr)
		{
			Vec3 parentScale = m_Parent->GetWorldScale();
			scale.x *= parentScale.x;
			scale.y *= parentScale.y;
			scale.z *= parentScale.z;
		}
		
		scale.x *= m_Scale.x;
		scale.y *= m_Scale.y;
		scale.z *= m_Scale.z;

		return scale;
	}

	void Transform::UpdateVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		front.y = sin(glm::radians(-m_Rotation.x));
		front.z = cos(glm::radians(m_Rotation.x)) * cos(glm::radians(m_Rotation.y));		

		m_Front = Vec3(glm::normalize(front));
		// Also re-calculate the Right and Up vector
		m_Right = Vec3(glm::normalize(glm::cross(glm::vec3(m_Front.x, m_Front.y, m_Front.z), glm::vec3(m_WorldUp.x, m_WorldUp.y, m_WorldUp.z))));
		// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = glm::normalize(glm::cross(glm::vec3(m_Right.x, m_Right.y, m_Right.z), glm::vec3(m_Front.x, m_Front.y, m_Front.z)));
	}
}