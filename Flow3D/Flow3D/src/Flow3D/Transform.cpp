#include "Transform.hpp"

#include "Flow3D/Log.hpp"

namespace Flow {

	Transform::Transform(const Vec3& position, const Vec3& rotation, const Vec3& scale)
		: m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{
		m_WorldUp = Vec3(0.0f, 1.0f, 0.0f);
		m_Orientation = Quaternion(m_Rotation);
		m_IsCamera = false;

		UpdateVectors();
	}

	Transform::~Transform()
	{
	}

	void Transform::Translate(const Vec3& translation)
	{
		m_Position += translation;
	}

	void Transform::Rotate(const Vec3 & axis, float angle)
	{
		Quaternion quat = Quaternion(axis, angle);
		Rotate(quat);
	}

	void Transform::Rotate(Quaternion& rotation)
	{
		m_Orientation = Quaternion(rotation * m_Orientation).Normalize();
		m_Rotation = m_Orientation.ToEulerAngles();
		UpdateVectors();
	}

	// Update vectors directly before this function
	void Transform::SetOrientation(const Quaternion & orientation)
	{
		m_Orientation = orientation;
		m_Rotation = m_Orientation.ToEulerAngles();
	}

	void Transform::SetIsCamera(bool isCamera)
	{
		m_IsCamera = isCamera;
		UpdateVectors(); // update vectors because the vector for cameras are inverted
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
			rotationMatrix = m_Orientation.ToMat4();

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
		glm::vec3 worldFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 worldRight = glm::vec3(1.0f, 0.0f, 0.0f);
		if (m_IsCamera)
		{
			worldFront = glm::vec3(0.0f, 0.0f, -1.0f);
			worldRight = glm::vec3(1.0f, 0.0f, 0.0f);
		}
			
		glm::quat quat = glm::quat(m_Orientation.w, m_Orientation.x, m_Orientation.y, m_Orientation.z);
		m_Front = Vec3(worldFront * quat).Normalize();
		m_Right = Vec3(worldRight * quat).Normalize();
		m_Up = Vec3::Cross(m_Right, m_Front).Normalize();
	}
}