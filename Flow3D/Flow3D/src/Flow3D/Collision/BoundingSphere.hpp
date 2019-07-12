#pragma once

#include "Flow3D/Math.hpp"
#include "IntersectData.hpp"
#include "Collider.hpp"
#include "AABB.hpp"

class BoundingSphere : public Collider
{
public:
	BoundingSphere(const Vec3& center, float radius) : Collider(Collider::TYPE_SPHERE), m_Center(center), m_Radius(radius) {}

	IntersectData IntersectBoundingSphere(const BoundingSphere& other);
	IntersectData IntersectAABB(const AABB& other);

	inline const Vec3& GetCenter() const { return m_Center; }
	inline float GetRadius() const { return m_Radius; }

private:
	const Vec3 m_Center;
	float m_Radius;
};
