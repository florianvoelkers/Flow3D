#pragma once

#include "Math.hpp"

namespace Flow {

	enum DIRECTIONS {
		up, down, right, left, front, back
	};
	
	class GameObject;

	class Transform
	{
	public:
		// Creates a Transform with default values for positon, rotation and scale
		Transform(const GameObject& gameObject, const Vec3& position = Vec3(0.0f), const Vec3& rotation = Vec3(0.0f), const Vec3& scale = Vec3(1.0f));
		
		void Translate(Vec3& translation); 
		void Rotate(const Vec3& axis, float angle);
		void Rotate(Quaternion& rotation);
		void SetOrientation(const Quaternion& orientation);
		void SetIsCamera(bool isCamera); 
		void SetParent(Transform* parent);
		void SetPosition(const Vec3& position);
		void SetScale(const Vec3& scale);

		Transform* GetParent() { return m_Parent; }
		const GameObject& GetGameObject() { return m_GameObject; }		

		inline void SetFrontVector(Vec3& front) { m_Forward = front; }
		inline void SetRightVector(Vec3& right) { m_Right = right; }
		inline void SetUpVector(Vec3& up) { m_Up = up; }
		inline const Vec3 GetForwardVector() const { return m_Forward; }
		inline const Vec3 GetUpVector() const { return m_Up; }
		inline const Vec3 GetRightVector() const { return m_Right; }

		inline const bool GetIsCamera() const { return m_IsCamera; }

		inline const Vec3 GetPosition() const { return m_Position; }
		inline const Vec3 GetRotation() const { return m_Rotation; }
		inline const Vec3 GetScale() const { return m_Scale; }
		
		Mat4 GetTransformation() const;
		const Vec3 GetWorldPosition() const;
		const Vec3 GetWorldRotation() const;
		const Quaternion GetOrientation() const;
		const Vec3 GetWorldScale() const;		

		void ConstrainPosition(bool x, bool y, bool z)
		{
			constrainPositionX = x;
			constrainPositionY = y;
			constrainPositionZ = z;
		}

		void ConstrainRotation(bool x, bool y, bool z)
		{
			constrainRotationX = x;
			constrainRotationY = y;
			constrainRotationZ = z;
		}

		void ConstrainScale(bool x, bool y, bool z)
		{
			constrainScaleX = x;
			constrainScaleY = y;
			constrainScaleZ = z;
		}

		inline bool GetConstrainPositionX() { return constrainPositionX; }
		inline bool GetConstrainPositionY() { return constrainPositionY; }
		inline bool GetConstrainPositionZ() { return constrainPositionZ; }

		inline bool GetConstrainRotationX() { return constrainRotationX; }
		inline bool GetConstrainRotationY() { return constrainRotationY; }
		inline bool GetConstrainRotationZ() { return constrainRotationZ; }

		inline bool GetConstrainScaleX() { return constrainScaleX; }
		inline bool GetConstrainScaleY() { return constrainScaleY; }
		inline bool GetConstrainScaleZ() { return constrainScaleZ; }

		void SetConstrainScaleX(bool scaleX) { constrainScaleX = scaleX; }
		void SetConstrainScaleY(bool scaleY) { constrainScaleY = scaleY; }
		void SetConstrainScaleZ(bool scaleZ) { constrainScaleZ = scaleZ; }

	private:
		const GameObject& m_GameObject;
		Vec3 m_Position;
		Vec3 m_Rotation; 
		Vec3 m_RotationEuler;
		Quaternion m_Orientation;
		Vec3 m_Scale;
		Transform* m_Parent;
		bool m_IsCamera;	

		bool constrainPositionX = false;
		bool constrainPositionY = false;
		bool constrainPositionZ = false;
		bool constrainRotationX = false;
		bool constrainRotationY = false;
		bool constrainRotationZ = false;
		bool constrainScaleX = false;
		bool constrainScaleY = false;
		bool constrainScaleZ = false;

		Vec3 m_Forward;
		Vec3 m_Up;
		Vec3 m_Right;
		Vec3 m_WorldUp;

		void UpdateVectors();
		void UpdateVectorRotations();
	};
}


