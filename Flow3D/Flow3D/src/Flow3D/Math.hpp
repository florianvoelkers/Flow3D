#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/quaternion.hpp"

#include <iostream>

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
			float sinHalfAngle = sinf(angle / 2);
			float cosHalfAngle = cosf(angle / 2);

			x = axis.x * sinHalfAngle;
			y = axis.y * sinHalfAngle;
			z = axis.z * sinHalfAngle;
			w = cosHalfAngle;
		}

		Mat4 ToRotationMatrix() const
		{
			Vec3 forward = Vec3(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
			Vec3 up = Vec3(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
			Vec3 right = Vec3(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));

			Mat4 matrix = Mat4();
			matrix.InitRotationFromVectors(forward, up, right);
			return matrix;
		}

		Quaternion Normalize()
		{
			glm::quat normalized = glm::normalize(glm::quat(x, y, z, w));
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
			const float _w = w * r.w - x * r.x - y * r.y - z * r.z;
			const float _x = x * r.w + w * r.x + y * r.z - z * r.y;
			const float _y = y * r.w + w * r.y + z * r.x - x * r.z;
			const float _z = z * r.w + w * r.z + x * r.y - y * r.x;

			return Quaternion(_x, _y, _z, _w);
		}

		Quaternion operator*(const Vec3& v)
		{
			const float _w = -1 * (x * v.x - y * v.y - z * v.z);
			const float _x =	   w * v.x + y * v.z - z * v.y;
			const float _y =	   w * v.y + z * v.x - x * v.z;
			const float _z =	   w * v.z + x * v.y - y * v.x;

			return Quaternion(_x, _y, _z, _w);
		}

		std::string ToString()
		{
			return glm::to_string(glm::quat(x, y, z, w));
		}

		float x, y, z, w;
	};
}
