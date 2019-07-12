#include "Collider.hpp"
#include "BoundingSphere.hpp"

IntersectData Collider::Intersect(const Collider& other) const
{
	if (m_Type == TYPE_SPHERE && other.GetType() == TYPE_SPHERE)
	{
		BoundingSphere* self = (BoundingSphere*)this;
		return self->IntersectBoundingSphere((BoundingSphere&)other);
	}

	std::cerr << "Error: Collisions not implemented between specified colliders." << std::endl;

	exit(1);

	return IntersectData(false, 0);
}