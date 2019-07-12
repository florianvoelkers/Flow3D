#pragma once

#include "Flow3D/Math.hpp"
#include "IntersectData.hpp"

class AABB
{
public:
	AABB(const Vec3& minExtents, const Vec3& maxExtents) : m_MinExtents(minExtents), m_MaxExtents(maxExtents) {}

	IntersectData IntersectAABB(const AABB& other) const;

	inline const Vec3& GetMinExtents() const { return m_MinExtents; }
	inline const Vec3& GetMaxExtents() const { return m_MaxExtents; }

private:
	const Vec3 m_MinExtents;
	const Vec3 m_MaxExtents;
};
