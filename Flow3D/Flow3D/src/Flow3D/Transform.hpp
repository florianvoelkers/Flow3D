#pragma once

#include "Math.hpp"

namespace Flow {

	enum DIRECTIONS {
		up, down, right, left, front, back
	};

	struct Transform
	{
	public:
		// Creates a Transform with default values for positon, rotation and scale
		Transform(const Vec3& position = Vec3(0.0f), const Vec3& rotation = Vec3(0.0f), const Vec3& scale = Vec3(1.0f));
		
		void Translate(const Vec3& translation); 
		void Rotate(const Vec3& axis, float angle);
		void Rotate(Quaternion& rotation);
		void SetOrientation(const Quaternion& orientation);
		void SetIsCamera(bool isCamera); 

		inline void SetPosition(const Vec3& position) { m_Position = position; }
		inline void SetScale(const Vec3& scale) { m_Scale = scale; }
		inline void SetParent(Transform* parent) { m_Parent = parent; }
		inline void SetFrontVector(Vec3& front) { m_Front = front; }
		inline void SetRightVector(Vec3& right) { m_Right = right; }
		inline void SetUpVector(Vec3& up) { m_Up = up; }

		inline const Vec3 GetFrontVector() const { return m_Front; }
		inline const Vec3 GetUpVector() const { return m_Up; }
		inline const Vec3 GetRightVector() const { return m_Right; }
		inline const bool GetIsCamera() const { return m_IsCamera; }

		inline const Vec3 GetPosition() const { return m_Position; }
		inline const Vec3 GetRotation() const { return m_RotationEuler; }
		inline const Vec3 GetScale() const { return m_Scale; }
		
		Mat4 GetTransformation() const;
		const Vec3 GetWorldPosition() const;
		const Vec3 GetWorldRotation() const;
		const Quaternion GetOrientation() const;
		const Vec3 GetWorldScale() const;		

	private:
		Transform* m_Parent;
		bool m_IsCamera;
		Vec3 m_Position;
		Vec3 m_RotationEuler; 
		Quaternion m_Rotation;
		Vec3 m_Scale;

		Vec3 m_Front;
		Vec3 m_Up;
		Vec3 m_Right;
		Vec3 m_WorldUp;

		void UpdateVectors();
	};
}


