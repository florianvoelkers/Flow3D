#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

#include "StructVisit.hpp"

namespace Flow {

	// Provides a wrapper around the glm library.
	// Contains several important Math functions and
	// definitions for Vectors (2-4) and Matrices (2-4)
	class Math {

	public:

		static float Radians(const float &degrees)
		{
			return glm::radians(degrees);
		}

		// angle in degrees, not radians
		static float Sin(const float &degrees)
		{
			float value = glm::sin(glm::radians(degrees));
			return value;
		}

		// angle in degrees, not radians
		static float Cos(const float &degrees)
		{
			float value = glm::cos(glm::radians(degrees));
			return value;
		}
	};

	class Vec2 {

	public:
		Vec2(const float& value) : x(value), y(value) {}
		Vec2(const float& x, const float& y) : x(x), y(y) {}
		Vec2(const glm::vec2 vec) : x(vec.x), y(vec.y) {}
		Vec2() {}

		Vec2 Normalize()
		{
			glm::vec2 normalized = glm::normalize(glm::vec2(x, y));
			return Vec2(normalized);
		}

		Vec2 operator+(const Vec2 &r)
		{
			return Vec2(x + r.x, y + r.y);
		}

		Vec2 operator+=(const Vec2 &r)
		{
			x += r.x;
			y += r.y;
			return *this;
		}

		Vec2 operator-(const Vec2 &r)
		{
			return Vec2(x - r.x, y - r.y);
		}

		Vec2 operator-=(const Vec2 &r)
		{
			x -= r.x;
			y -= r.y;
			return *this;
		}

		Vec2 operator*(const float &value)
		{
			return Vec2(x * value, y * value);
		}

		std::string ToString()
		{
			return glm::to_string(glm::vec2(x, y));
		}

		const std::string ToString() const
		{
			return glm::to_string(glm::vec2(x, y));
		}

		float x, y;
	};

	class Vec3 {

	public:
		Vec3(const float& value) : x(value), y(value), z(value) {}
		Vec3(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {}
		Vec3(const glm::vec3 vec) : x(vec.x), y(vec.y), z(vec.z) {}
		Vec3() {}

		friend std::ostream& operator<<(std::ostream& os, const Vec3& vec)
		{
			os << "Vec3: x = " << vec.x << ", y = " << vec.y << ", z = " << vec.z;
			return os;
		}

		Vec3 Cross(Vec3 b)
		{
			return Vec3(glm::cross(glm::vec3(x, y, z), glm::vec3(b.x, b.y, b.z)));
		}

		Vec3 Normalize()
		{
			glm::vec3 normalized = glm::normalize(glm::vec3(x, y, z));
			return Vec3(normalized);
		}

		Vec3 operator+(const Vec3 &r)
		{
			return Vec3(x + r.x, y + r.y, z + r.z);
		}

		Vec3 operator+=(const Vec3 &r)
		{
			x += r.x;
			y += r.y;
			z += r.z;
			return *this;
		}

		Vec3 operator-(const Vec3 &r)
		{
			return Vec3(x - r.x, y - r.y, z - r.z);
		}

		Vec3 operator-=(const Vec3 &r)
		{
			x -= r.x;
			y -= r.y;
			z -= r.z;
			return *this;
		}

		Vec3 operator*(const float &value)
		{
			return Vec3(x * value, y * value, z * value);
		}

		static Vec3 Cross(const Vec3 &a, const Vec3 &b)
		{
			glm::vec3 crossProduct = glm::cross(glm::vec3(a.x, a.y, a.z), glm::vec3(b.x, b.y, b.z));
			return Vec3(crossProduct);
		}

		std::string ToString()
		{
			return glm::to_string(glm::vec3(x, y, z));
		}

		const std::string ToString() const
		{
			return glm::to_string(glm::vec3(x, y, z));
		}

		float x, y, z;
	};

	class Vec4 {

	public:
		Vec4(const float& value) : x(value), y(value), z(value), w(value) {}
		Vec4(const float& x, const float& y, const float& z, const float& w) : x(x), y(y), z(z), w(w) {}
		Vec4(const glm::vec4 vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
		Vec4() {}

		Vec4 Normalize()
		{
			glm::vec4 normalized = glm::normalize(glm::vec4(x, y, z, w));
			return Vec4(normalized);
		}

		Vec4 operator+(const Vec4 &r)
		{
			return Vec4(x + r.x, y + r.y, z + r.z, w + r.w);
		}

		Vec4 operator+=(const Vec4 &r)
		{
			x += r.x;
			y += r.y;
			z += r.z;
			w += r.w;
			return *this;
		}

		Vec4 operator-(const Vec4 &r)
		{
			return Vec4(x - r.x, y - r.y, z - r.z, w - r.w);
		}

		Vec4 operator-=(const Vec4 &r)
		{
			x -= r.x;
			y -= r.y;
			z -= r.z;
			w -= r.w;
			return *this;
		}

		Vec4 operator*(const float &value)
		{
			return Vec4(x * value, y * value, z * value, w * value);
		}

		std::string ToString()
		{
			return glm::to_string(glm::vec4(x, y, z, w));
		}

		float x, y, z, w;
	};

	class Mat2 {

	public:
		Mat2() : mat(1.0f) {}
		Mat2(glm::mat2 matrix) : mat(matrix) {}

		std::string ToString()
		{
			return glm::to_string(mat);
		}

		glm::mat2 mat;
	};

	class Mat3 {

	public:
		Mat3() : mat(1.0f) {}
		Mat3(glm::mat3 matrix) : mat(matrix) {}
		Mat3(glm::mat4 matrix) : mat(matrix) {}

		std::string ToString()
		{
			return glm::to_string(mat);
		}

		glm::mat3 mat;
	};

	class Quaternion;

	class Mat4 {

	public:
		// create identity matrix
		Mat4() : mat(1.0f) {}
		Mat4(glm::mat4 matrix) : mat(matrix) {}
		Mat4(glm::mat3 matrix) : mat(matrix) {}

		void Translate(const Vec3 &translationVector)
		{
			mat = glm::translate(mat, glm::vec3(translationVector.x, translationVector.y, translationVector.z));
		}

		void Scale(const Vec3 &scalingVector)
		{
			mat = glm::scale(mat, glm::vec3(scalingVector.x, scalingVector.y, scalingVector.z));
		}

		// angle in degrees, not radians, Vector will be normalized in Rotate function
		void Rotate(const float &degrees, const Vec3 &rotationAxis)
		{
			mat = glm::rotate(mat, glm::radians(degrees), glm::normalize(glm::vec3(rotationAxis.x, rotationAxis.y, rotationAxis.z)));
		}

		Mat4 InitRotationFromVectors(const Vec3& forward, const Vec3& up, const Vec3& right)
		{
			mat[0][0] = right.x;	mat[1][0] = right.y;	mat[2][0] = right.z;	mat[3][0] = 0.0f;
			mat[0][1] = up.x;		mat[1][1] = up.y;		mat[2][1] = up.z;		mat[3][1] = 0.0f;
			mat[0][2] = forward.x;	mat[1][2] = forward.y;	mat[2][2] = forward.z;	mat[3][2] = 0.0f;
			mat[0][3] = 0.0f;		mat[1][3] = 0.0f;		mat[2][3] = 0.0f;		mat[3][3] = 1.0f;

			return *this;
		}

		Mat4 operator*(const Mat4& matrix) const
		{
			Mat4 ret(mat * matrix.mat);
			return ret;
		}

		static Mat4 GetPerspectiveProjection(float fovy, float aspect, float zNear, float zFar)
		{
			glm::mat4 perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);
			return Mat4(perspectiveMat);
		}

		static Mat4 LookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up)
		{
			glm::mat4 lookAtMatrix = glm::lookAt(glm::vec3(eye.x, eye.y, eye.z),
				glm::vec3(center.x, center.y, center.z), glm::vec3(up.x, up.y, up.z));
			return Mat4(lookAtMatrix);
		}

		std::string ToString()
		{
			return glm::to_string(mat);
		}

		glm::mat4 mat;
	};

	// mostly from https://github.com/BennyQBD/3DEngineCpp/blob/master/src/core/math3d.h
	class Quaternion
	{
	public:
		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : x(x), y(y), z(z), w(w) {}
		Quaternion(const Vec4& r) : x(r.x), y(r.y), z(r.z), w(r.w) {}
		Quaternion(const Quaternion& r) : x(r.x), y(r.y), z(r.z), w(r.w) {}
		Quaternion(const glm::quat& r) : x(r.x), y(r.y), z(r.z), w(r.w) {}
		Quaternion(const Vec3& axis, float angle) 
		{
			glm::quat quat = glm::angleAxis(glm::radians(angle), glm::vec3(axis.x, axis.y, axis.z));
			x = quat.x;
			y = quat.y;
			z = quat.z;
			w = quat.w;
		}

		Quaternion(const Vec3& eulerAngles)
		{
			glm::quat quat = glm::quat(glm::vec3(glm::radians(eulerAngles.x), glm::radians(eulerAngles.y), glm::radians(eulerAngles.z)));
			x = quat.x;
			y = quat.y;
			z = quat.z;
			w = quat.w;
		}

		// Order is XYZ, e.g. flips to 180, -90, 180 from 0, -89, 0
		Vec3 ToEulerAngles() const
		{
			glm::quat quat = glm::quat(w, x, y, z);
			glm::vec3 eulerAnglesRadians = glm::eulerAngles(quat);
			glm::vec3 eulerAngles = glm::vec3(glm::degrees(eulerAnglesRadians.x), glm::degrees(eulerAnglesRadians.y), glm::degrees(eulerAnglesRadians.z));
			return Vec3(eulerAngles);
		}

		Mat4 ToMat4() const
		{
			Mat4 asMatrix = Mat4(glm::toMat4(glm::quat(w, x, y, z)));
			return asMatrix;
		}

		Quaternion Normalize()
		{
			glm::quat normalized = glm::normalize(glm::quat(w, x, y, z));
			return Quaternion(normalized);
		}

		Quaternion operator+(const Vec4 &r)
		{
			return Quaternion(x + r.x, y + r.y, z + r.z, w + r.w);
		}

		Quaternion operator+(const Quaternion &r)
		{
			return Quaternion(x + r.x, y + r.y, z + r.z, w + r.w);
		}

		Quaternion operator+=(const Vec4 &r)
		{
			x += r.x;
			y += r.y;
			z += r.z;
			w += r.w;
			return *this;
		}

		Quaternion operator+=(const Quaternion &r)
		{
			x += r.x;
			y += r.y;
			z += r.z;
			w += r.w;
			return *this;
		}

		Quaternion operator-(const Vec4 &r)
		{
			return Vec4(x - r.x, y - r.y, z - r.z, w - r.w);
		}

		Quaternion operator-(const Quaternion &r)
		{
			return Quaternion(x - r.x, y - r.y, z - r.z, w - r.w);
		}

		Quaternion operator-=(const Vec4 &r)
		{
			x -= r.x;
			y -= r.y;
			z -= r.z;
			w -= r.w;
			return *this;
		}

		Quaternion operator-=(const Quaternion &r)
		{
			x -= r.x;
			y -= r.y;
			z -= r.z;
			w -= r.w;
			return *this;
		}

		Quaternion operator*(const float &value)
		{
			return Quaternion(x * value, y * value, z * value, w * value);
		}


		Quaternion operator*(const Quaternion& r)
		{
			glm::quat other = glm::quat(r.w, r.x, r.y, r.z);
			glm::quat thisOne = glm::quat(w, x, y, z);
			glm::quat result = thisOne * other;
			return Quaternion(result);
		}

		Quaternion operator*(const Vec3& r)
		{
			glm::quat result = glm::quat(w, x, y, z) * glm::vec3(r.x, r.y, r.z);
			return Quaternion(result);
		}

		Vec3 Multiply(const Vec3& r)
		{
			glm::vec3 result = glm::vec3(r.x, r.y, r.z) * glm::quat(w, x, y, z);
			return Vec3(result);
		}

		std::string ToString()
		{
			return glm::to_string(glm::quat(w, x, y, z));
		}

		std::string ToString() const
		{
			return glm::to_string(glm::quat(w, x, y, z));
		}

		// adapted from: https://community.khronos.org/t/how-to-limit-x-axis-rotation/75515/11
		static Mat4 CalculateView(float pitch, Quaternion orientation, Vec3 position)
		{
			glm::mat4 view = glm::rotate(glm::mat4{}, pitch, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::mat4_cast(glm::quat(orientation.w, orientation.x, orientation.y, orientation.z)) *
				glm::translate(glm::mat4(), glm::vec3(-1 * position.x, -1 * position.y, -1 * position.z));
			return Mat4(view);
		}

		float x, y, z, w;
	};
}


VISITABLE_STRUCT(Flow::Vec3, x, y, z);