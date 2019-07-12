#include "AABB.hpp"

IntersectData AABB::IntersectAABB(const AABB & other) const
{
	Vec3 distances1 = other.GetMinExtents() - m_MaxExtents;
	Vec3 distances2 = m_MinExtents - other.GetMaxExtents();
	Vec3 distances = distances1.Max(distances2);
	float maxDistance = distances.Max();

	return IntersectData((maxDistance < 0), maxDistance);
}
