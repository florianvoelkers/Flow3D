#include "Transform.hpp"

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

	Mat4 Transform::GetTransformation() const
	{
		Mat4 translationMatrix = Mat4();
		translationMatrix.Translate(m_Position);

		Mat4 rotationMatrix;
		if (m_IsCamera)
			rotationMatrix = Quaternion(-1 * m_Orientation.x, -1 * m_Orientation.y, -1 * m_Orientation.z, m_Orientation.w).ToMat4();			
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
		Vec3 front;
		front.x = Math::Cos(m_Rotation.y) * Math::Cos(m_Rotation.z);
		front.y = Math::Sin(m_Rotation.z);
		front.z = Math::Sin(m_Rotation.y) * Math::Cos(m_Rotation.z);
		m_Front = front.Normalize();
		m_Right = Vec3::Cross(m_Front, m_WorldUp).Normalize();
		m_Up = Vec3::Cross(m_Right, m_Front).Normalize();
	}
}