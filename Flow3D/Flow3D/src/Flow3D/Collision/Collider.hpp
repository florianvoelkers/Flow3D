#pragma once

#include "IntersectData.hpp"

class Collider
{	
public:
	enum
	{
		TYPE_SPHERE,
		TYPE_AABB,
		TYPE_PLANE,

		TYPE_SIZE
	};

	Collider(int type) : m_Type(type) {}

	IntersectData Intersect(const Collider& other) const;

	inline int GetType() const { return m_Type; }

private:
	int m_Type;
};