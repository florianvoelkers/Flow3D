#include "Transform.hpp"

namespace Flow {

	Transform::Transform(const Vec3& position, const Vec3& rotation, const Vec3& scale)
		: m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{
	}

	Transform::~Transform()
	{
	}
}