#include "PlaneCollider.hpp"

PlaneCollider PlaneCollider::Normalized() const
{
	float magnitude = m_Normal.Length();

	return PlaneCollider(m_Normal / magnitude, m_Distance / magnitude);
}

IntersectData PlaneCollider::IntersectSphere(const BoundingSphere & other) const
{
	float distanceFromSphereCenter = fabs(m_Normal.Dot(other.GetCenter()) + m_Distance);
	float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();

	return IntersectData(distanceFromSphere < 0, distanceFromSphere);
}

IntersectData PlaneCollider::IntersectAABB(const AABB & other) const
{
	Vec3 centerAABB = (other.GetMaxExtents() + other.GetMinExtents()) * 0.5f;
	Vec3 extentsAABB = other.GetMaxExtents() - centerAABB;

	// projection interval radius of the aabb
	float r = extentsAABB.x * fabs(m_Normal.x) + extentsAABB.y * fabs(m_Normal.y) + extentsAABB.z * fabs(m_Normal.z);

	// distance of box center from plane
	float s = m_Normal.Dot(centerAABB) - m_Distance;

	std::cout << "r is " << r << std::endl;
	std::cout << "s is " << s << std::endl;

	return IntersectData((fabs(s) <= r), s);
}

IntersectData PlaneCollider::IntersectPlane(const PlaneCollider & other) const
{
	Vec3 direction = Vec3::Cross(m_Normal, other.GetNormal());

	return IntersectData(direction.Dot(direction) > 0.0001f, 0.0f);
}
