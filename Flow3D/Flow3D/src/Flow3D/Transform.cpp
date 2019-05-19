#include "Transform.hpp"

#include "Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


namespace Flow {

	Transform::Transform(const Vec3& position, const Vec3& rotation, const Vec3& scale)
		: m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{
		m_WorldUp = Vec3(0.0f, 1.0f, 0.0f);
		m_Orientation = Quaternion(m_Rotation);
		m_ParentIsCamera = false;

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
		Rotate(Quaternion(axis, angle));
	}

	void Transform::Rotate(const Quaternion& rotation)
	{
		m_Orientation = Quaternion(m_Orientation * rotation).Normalize();
		m_Rotation = m_Orientation.ToEulerAngles();
		UpdateVectors();
	}

	void Transform::SetOrientation(const Quaternion & orientation)
	{
		m_Orientation = orientation;
		m_Rotation = m_Orientation.ToEulerAngles();
		UpdateVectors();
	}

	glm::mat4 Transform::GetTransformation() const
	{
		/*
		Mat4 translationMatrix = Mat4();
		translationMatrix.Translate(m_Position);

		Mat4 scaleMatrix = Mat4();
		scaleMatrix.Scale(m_Scale);

		Mat4 rotationMatrix = m_RotationQuaternion.ToRotationMatrix();

		Mat4 result = translationMatrix * rotationMatrix * scaleMatrix;
		if (m_Parent != nullptr)
			result = m_Parent->GetTransformation() * result;*/

		glm::mat4 translationMatrix = glm::mat4();
		translationMatrix = glm::translate(translationMatrix, glm::vec3(m_Position.x, m_Position.y, m_Position.z));
		glm::mat4 rotationMatrix = glm::toMat4(glm::quat(m_Orientation.w, m_Orientation.x, m_Orientation.y, m_Orientation.z));
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(), glm::vec3(m_Scale.x, m_Scale.y, m_Scale.z));

		glm::mat4 result = translationMatrix * rotationMatrix * scaleMatrix;
		if (m_Parent != nullptr) 
			result = m_Parent->GetTransformation() * result;		

		return result;
	}

	const Vec3 Transform::GetPosition() const
	{
		Vec3 position = Vec3(0.0f);
		if (m_Parent != nullptr)
			position = m_Parent->GetPosition();

		position += m_Position;

		return position;
	}

	const Vec3 Transform::GetRotation() const
	{
		Vec3 rotation = Vec3(0.0f);
		if (m_Parent != nullptr)
			rotation = m_Parent->GetRotation();

		rotation += m_Rotation;

		return rotation;
	}

	const Quaternion Transform::GetOrientation() const
	{
		return m_Orientation;
	}

	const Vec3 Transform::GetScale() const
	{
		Vec3 scale = Vec3(1.0f);
		if (m_Parent != nullptr)
		{
			Vec3 parentScale = m_Parent->GetScale();
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
		Vec3 front;
		front.x = Math::Cos(m_Rotation.y) * Math::Cos(m_Rotation.z);
		front.y = Math::Sin(m_Rotation.z);
		front.z = Math::Sin(m_Rotation.y) * Math::Cos(m_Rotation.z);
		m_Front = front.Normalize();
		m_Right = Vec3::Cross(m_Front, m_WorldUp).Normalize();
		m_Up = Vec3::Cross(m_Right, m_Front).Normalize();
	}
}