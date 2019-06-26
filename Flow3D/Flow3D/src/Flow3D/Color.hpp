#pragma once

#include "glm\vec4.hpp"

// struct for colors which can be create with rgb or rgba value
struct Color {

	Color () : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}

	Color(float red, float green, float blue)
		: r(red), g(green), b(blue), a(1.0f)
	{}

	Color(float red, float green, float blue, float alpha)
		: r(red), g(green), b(blue), a(alpha)
	{}

	glm::vec4 ToVector4f()
	{
		return glm::vec4(r, g, b, a);
	}

	float r;
	float g;
	float b;
	float a;
};

#include <MetaStuff/include/Meta.h>

namespace meta {

	template <>
	inline auto registerMembers<Color>()
	{
		return members(
			member("r", &Color::r),
			member("g", &Color::g),
			member("b", &Color::b),
			member("a", &Color::a)
		);
	}

} // end of namespace meta