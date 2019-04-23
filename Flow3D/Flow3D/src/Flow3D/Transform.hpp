#pragma once

#include "Math.hpp"

namespace Flow {

	class Transform
	{
	public:
		// Creates a Transform with default values for positon, rotation and scale
		Transform(const Vec3& position = Vec3(0.0f), const Vec3& rotation = Vec3(0.0f), const Vec3& scale = Vec3(1.0f));
		~Transform();

		// TODO: Useful functions
		/*

		bool HasChanged(); // return true if something has changed to inform children
		Mat4 GetTransformation() const;

		void Rotate(const Vec3& axis, float angle);
		void Rotate(const Quaternion& rotation);
		void LookAt(const Vec3& point, const Vec3 up);
		void Translate(const Vec3& translation); // moves transofrm in the direction and distance of translation
		*/

		inline void SetPosition(const Vec3& position) { m_Position = position; }
		inline void SetRotation(const Vec3& rotation) { m_Rotation = rotation; }
		inline void SetScale(const Vec3& scale) { m_Scale = scale; }
		inline void SetParent(Transform* parent) { m_Parent = parent; }

		Transform* m_Parent;
		Vec3 m_Position;
		Vec3 m_Rotation; // TODO: make rotation a quaternion maybe
		Vec3 m_Scale;
		
	};
}
