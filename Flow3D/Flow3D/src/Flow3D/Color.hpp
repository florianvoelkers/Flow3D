#pragma once

#include "glm\vec4.hpp"

namespace Flow {

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
}