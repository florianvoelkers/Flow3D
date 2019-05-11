#include "Transform.hpp"

namespace Flow {

	Transform::Transform(const Vec3& position, const Vec3& rotation, const Vec3& scale)
		: m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{
		m_WorldUp = Vec3(0.0f, 1.0f, 0.0f);
		m_Yaw = YAW;
		m_Pitch = PITCH;

		UpdateVectors();
	}

	Transform::~Transform()
	{
	}

	void Transform::SetYawAndPitch(float yaw, float pitch)
	{
		m_Yaw = yaw;
		m_Pitch = pitch;
		UpdateVectors();
	}

	void Transform::UpdateVectors()
	{
		Vec3 front;
		front.x = Math::Cos(m_Yaw) * Math::Cos(m_Pitch);
		front.y = Math::Sin(m_Pitch);
		front.z = Math::Sin(m_Yaw) * Math::Cos(m_Pitch);
		m_Front = front.Normalize();
		m_Right = Vec3::Cross(m_Front, m_WorldUp).Normalize();
		m_Up = Vec3::Cross(m_Right, m_Front).Normalize();
	}
}