#include "Shader.hpp"

#include <fstream>
#include <sstream>

#include "Flow3D\Log.hpp"

namespace Flow {

	Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
	{
		// 1. retrieve the vertex/fragment source code from the file paths
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		// ensure ifstream objects can throw exceptions
		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// open files
			vertexShaderFile.open(vertexPath);
			fragmentShaderFile.open(fragmentPath);
			std::stringstream vertexShaderStream, fragmentShaderStream;
			
			// read file's buffer contents into streams
			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();

			// convert stream into string
			vertexCode = vertexShaderStream.str();
			fragmentCode = fragmentShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			FLOW_CORE_ERROR("SHADER::FILE_NOT_SUCCESFULLY_READ");
		}

		const char* vertexShaderCode = vertexCode.c_str();
		const char* fragmentShaderCode = fragmentCode.c_str();

		// 2. compile shaders
		unsigned int vertex, fragment;

		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexShaderCode, NULL);
		glCompileShader(vertex);

		CheckCompileErrors(vertex, "VERTEX");

		// fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
		glCompileShader(fragment);

		CheckCompileErrors(fragment, "FRAGMENT");

		// shader program
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex);
		glAttachShader(m_ID, fragment);
		glLinkProgram(m_ID);

		CheckCompileErrors(m_ID, "Program");

		// delete the shaders because they're linked into our program now and are no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	Shader::~Shader()
	{

	}

	void Shader::Use()
	{
		glUseProgram(m_ID);
	}

	void Shader::SetBool(const std::string & name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
	}

	void Shader::SetInt(const std::string & name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void Shader::SetFloat(const std::string & name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void Shader::SetVec2(const std::string & name, const Vec2 & value) const
	{
		glUniform2f(glGetUniformLocation(m_ID, name.c_str()), value.x, value.y);
	}

	void Shader::SetVec2(const std::string & name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
	}

	void Shader::SetVec3(const std::string & name, const Vec3 & value) const
	{
		glUniform3f(glGetUniformLocation(m_ID, name.c_str()), value.x, value.y, value.z);
	}

	void Shader::SetVec3(const std::string & name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
	}

	void Shader::SetVec4(const std::string & name, const Vec4 value) const
	{
		glUniform4f(glGetUniformLocation(m_ID, name.c_str()), value.x, value.y, value.z, value.w);
	}

	void Shader::SetVec4(const std::string & name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
	}

	void Shader::SetMat2(const std::string & name, const Mat2 & mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat.mat[0][0]);
	}

	void Shader::SetMat3(const std::string & name, const Mat3 & mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat.mat[0][0]);
	}

	void Shader::SetMat4(const std::string & name, const Mat4 & mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat.mat[0][0]);
	}

	void Shader::CheckCompileErrors(GLuint shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				FLOW_CORE_ERROR("SHADER_COMPILATION_ERROR of type: {0}\n{1}\n{0}", type, infoLog);
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				FLOW_CORE_ERROR("SHADER::PROGRAM::LINKING_FAILED\n\n{0}", infoLog);
			}
		}
			
	}
}