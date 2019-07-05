#pragma once

#include "Flow3D/Math.hpp"

#include "glad\glad.h"

#include <string>


// taken from: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h

// Holds the functionality needed to represent an OpenGL shader
class Shader {

public:
	unsigned int m_ID;
	std::string m_Name;
	std::string m_VertexPath;
	std::string m_FragmentPath;

	Shader() {}
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, std::string name);
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

private:
	void CheckCompileErrors(GLuint shader, std::string type);
};

#include <MetaStuff/include/Meta.h>

namespace meta {

	template <>
	inline auto registerMembers<Shader>()
	{
		return members(
			member("m_ID", &Shader::m_ID),
			member("m_Name", &Shader::m_Name),
			member("m_VertexPath", &Shader::m_VertexPath),
			member("m_FragmentPath", &Shader::m_FragmentPath)
		);
	}

} // end of namespace meta

