#include "BoundingSphere.hpp"

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other)
{
	float radiusDistance = m_Radius + other.GetRadius();
	float centerDistance = (other.GetCenter() - m_Center).Length();
	float distance = centerDistance - radiusDistance;

	return IntersectData((centerDistance < radiusDistance), distance);
}


IntersectData BoundingSphere::IntersectAABB(const AABB & other)
{
	auto check = [&](const float pn, const float bmin, const float bmax) -> float
	{
		float out = 0.0f;
		float v = pn;

		if (v < bmin)
		{
			float val = (bmin - v);
			out += val * val;
		}

		if (v > bmax)
		{
			float val = (v - bmax);
			out += val * val;
		}

		return out;
	};

	float squaredDistance = 0.0f;
	squaredDistance += check(m_Center.x, other.GetMinExtents().x, other.GetMaxExtents().x);
	squaredDistance += check(m_Center.y, other.GetMinExtents().y, other.GetMaxExtents().y);
	squaredDistance += check(m_Center.z, other.GetMinExtents().z, other.GetMaxExtents().z);

	return IntersectData((squaredDistance < m_Radius * m_Radius), sqrt(squaredDistance));
}