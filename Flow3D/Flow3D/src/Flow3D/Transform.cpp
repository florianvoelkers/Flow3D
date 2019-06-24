#include "Transform.hpp"

#include "Flow3D/Log.hpp"
#include "GameObject.hpp"


Transform::Transform(const GameObject* gameObject, const Vec3& position, const Vec3& rotation, const Vec3& scale)
	: m_GameObject(gameObject), m_Position(position), m_Rotation(rotation), m_Scale(scale), m_Parent(nullptr)
{
	m_WorldUp = Vec3(0.0f, 1.0f, 0.0f);
	m_Orientation = Quaternion(m_Rotation);
	m_IsCamera = false;

	UpdateVectors();
}

void Transform::Translate(Vec3& translation)
{
	if (constrainPositionX)
		translation.x = 0.0f;

	if (constrainPositionY)
		translation.y = 0.0f;

	if (constrainPositionZ)
		translation.z = 0.0f;

	m_Position += translation;
}

void Transform::Rotate(const Vec3 & axis, float angle)
{
	if (axis.x > 0.0f && constrainRotationX)
		FLOW_CORE_INFO("x axis rotation is constrained");
	else if (axis.y > 0.0f && constrainRotationY)
		FLOW_CORE_INFO("y axis rotation is constrained");
	else if (axis.z > 0.0f && constrainRotationZ)
		FLOW_CORE_INFO("z axis rotation is constrained");
	else
	{
		Quaternion quat = Quaternion(axis, angle);
		Rotate(quat);
	}		
}

void Transform::Rotate(Quaternion& rotation)
{
	m_Orientation = Quaternion(rotation * m_Orientation).Normalize();

	UpdateVectorRotations();
	UpdateVectors();
}

void Transform::SetOrientation(const Quaternion & orientation)
{
	m_Orientation = orientation;
	UpdateVectorRotations();
	// don't call UpdateVectors because this is done from the camera component
	if (!m_IsCamera)
		UpdateVectors();
}

void Transform::SetParent(Transform* parent) 
{ 
	m_Parent = parent; 
	if (!m_IsCamera)
		UpdateVectors();
}

void Transform::SetPosition(const Vec3& position)
{
	Vec3 newPosition = position;

	if (constrainPositionX)
		newPosition.x = m_Position.x;

	if (constrainPositionY)
		newPosition.y = m_Position.y;

	if (constrainPositionZ)
		newPosition.z = m_Position.z;

	m_Position = newPosition;
}

void Transform::SetScale(const Vec3& scale)
{
	Vec3 newScale = scale;

	if (constrainScaleX)
		newScale.x = m_Scale.x;

	if (constrainScaleY)
		newScale.y = m_Scale.y;

	if (constrainScaleZ)
		newScale.z = m_Scale.z;

	m_Scale = newScale;
}

Mat4 Transform::GetTransformation() const
{
	Mat4 translationMatrix = Mat4();
	translationMatrix.Translate(m_Position);

	Mat4 rotationMatrix;
		
	if (m_IsCamera)
	{
		Vec3 adjustedEuler = Vec3(-1 * m_Rotation.x, -1 * m_Rotation.y, - 1 * m_Rotation.z);
		rotationMatrix = Quaternion(adjustedEuler).ToMat4();
	}
	else
		rotationMatrix = m_Orientation.ToMat4();			

	Mat4 scaleMatrix = Mat4();
	scaleMatrix.Scale(m_Scale);

	Mat4 result = translationMatrix * rotationMatrix * scaleMatrix;
	if (m_Parent != nullptr) 
		result = m_Parent->GetTransformation() * result;		

	return result;
}

const Vec3 Transform::GetWorldPosition() const
{
	Vec3 position = Vec3(0.0f);
	if (m_Parent != nullptr)
		position = m_Parent->GetWorldPosition();

	position += m_Position;

	return position;
}

const Vec3 Transform::GetWorldRotation() const
{
	Vec3 rotation = Vec3(0.0f);
	if (m_Parent != nullptr)
		rotation = m_Parent->GetWorldRotation();

	rotation += m_Rotation;

	return rotation;
}

const Quaternion Transform::GetOrientation() const
{
	return m_Orientation;
}

const Vec3 Transform::GetWorldScale() const
{
	Vec3 scale = Vec3(1.0f);
	if (m_Parent != nullptr)
	{
		Vec3 parentScale = m_Parent->GetWorldScale();
		scale.x *= parentScale.x;
		scale.y *= parentScale.y;
		scale.z *= parentScale.z;
	}
		
	scale.x *= m_Scale.x;
	scale.y *= m_Scale.y;
	scale.z *= m_Scale.z;

	return scale;
}

void Transform::UpdateVectors()
{
	float pitch, yaw, roll;
	if (m_Parent != nullptr)
	{
		Quaternion parentOrientation = m_Parent->GetOrientation();
		Quaternion worldOrientation = parentOrientation * m_Orientation;
		Quaternion::ToEulerAngle(worldOrientation, pitch, yaw, roll);
	}
	else
	{
		pitch = m_Rotation.x;
		yaw = m_Rotation.y;
		roll = m_Rotation.z;
	}
		

	// Calculate the new Front vector
	glm::vec3 front;
	front.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(-pitch));
	front.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));

	m_Forward = Vec3(glm::normalize(front));
	// Also re-calculate the Right and Up vector
	m_Right = Vec3(glm::normalize(glm::cross(glm::vec3(m_Forward.x, m_Forward.y, m_Forward.z), glm::vec3(m_WorldUp.x, m_WorldUp.y, m_WorldUp.z))));
	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_Up = glm::normalize(glm::cross(glm::vec3(m_Right.x, m_Right.y, m_Right.z), glm::vec3(m_Forward.x, m_Forward.y, m_Forward.z)));
}

void Transform::UpdateVectorRotations()
{
	float pitch, yaw, roll;
	Quaternion::ToEulerAngle(m_Orientation, pitch, yaw, roll);
	m_Rotation = Vec3(pitch, yaw, roll);
}
