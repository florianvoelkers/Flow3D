#pragma once

#include "Flow3D/Math.hpp"

#include "glad\glad.h"

#include <string>


namespace Flow {

	class Shader {

	public:
		unsigned int m_ID;

		Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
		~Shader();

		void Use();
		void SetBool(const std::string &name, bool value) const;
		void SetInt(const std::string &name, int value) const;
		void SetFloat(const std::string &name, float value) const;
		void SetVec2(const std::string &name, const Vec2 &value) const;
		void SetVec2(const std::string &name, float x, float y) const;
		void SetVec3(const std::string &name, const Vec3 &value) const;
		void SetVec3(const std::string &name, float x, float y, float z) const;
		void SetVec4(const std::string &name, const Vec4 value) const;
		void SetVec4(const std::string &name, float x, float y, float z, float w) const;
		void SetMat2(const std::string &name, const Mat2 &mat) const;
		void SetMat3(const std::string &name, const Mat3 &mat) const;
		void SetMat4(const std::string &name, const Mat4 &mat) const;
	};
}
