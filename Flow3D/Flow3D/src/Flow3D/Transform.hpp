#pragma once

#include "Math.hpp"

namespace Flow {

	enum DIRECTIONS {
		up, down, right, left, front, back
	};

	class Transform
	{
	public:
		// Creates a Transform with default values for positon, rotation and scale
		Transform(const Vec3& position = Vec3(0.0f), const Vec3& rotation = Vec3(0.0f), const Vec3& scale = Vec3(1.0f));
		~Transform();

		// TODO: Useful functions
		/*

		bool HasChanged(); // return true if something has changed to inform children
		
		6
		
		void LookAt(const Vec3& point, const Vec3 up);
		*/
		
		void Translate(const Vec3& translation); 
		void Rotate(const Vec3& axis, float angle);
		void Rotate(const Quaternion& rotation);
		void SetOrientation(const Quaternion& orientation);

		inline void SetPosition(const Vec3& position) { m_Position = position; }
		inline void SetScale(const Vec3& scale) { m_Scale = scale; }
		inline void SetParent(Transform* parent) { m_Parent = parent; }
		inline void SetIsCamera(bool isCamera) { m_IsCamera = isCamera; }

		inline const Vec3 GetFrontVector() const { return m_Front; }
		inline const Vec3 GetUpVector() const { return m_Up; }
		inline const Vec3 GetRightVector() const { return m_Right; }
		inline const bool GetIsCamera() const { return m_IsCamera; }
		
		glm::mat4 GetTransformation() const;
		const Vec3 GetPosition() const;
		const Vec3 GetRotation() const;
		const Quaternion GetOrientation() const;
		const Vec3 GetScale() const;		

	private:
		Transform* m_Parent;
		bool m_IsCamera;
		Vec3 m_Position;
		Vec3 m_Rotation; // TODO: make rotation a quaternion maybe
		Quaternion m_Orientation;
		Vec3 m_Scale;

		Vec3 m_Front;
		Vec3 m_Up;
		Vec3 m_Right;
		Vec3 m_WorldUp;

		void UpdateVectors();
	};
}
