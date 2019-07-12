#pragma once

#include "Flow3D/Math.hpp"
#include "IntersectData.hpp"
#include "BoundingSphere.hpp"
#include "AABB.hpp"

class PlaneCollider
{
public:
	PlaneCollider(const Vec3& normal, float distance) : m_Normal(normal), m_Distance(distance) {}

	PlaneCollider Normalized() const;
	IntersectData IntersectSphere(const BoundingSphere& other) const;
	IntersectData IntersectAABB(const AABB& other) const;
	IntersectData IntersectPlane(const PlaneCollider& other) const;

	inline const Vec3& GetNormal() const { return m_Normal; }
	inline float GetDistance() const { return m_Distance; }

private:
	const Vec3 m_Normal;
	const float m_Distance;
};