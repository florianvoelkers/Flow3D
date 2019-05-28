#pragma once

#include "Component.hpp"
#include "Flow3D/Math.hpp"
#include "Flow3D/Color.hpp"

// from https://github.com/BennyQBD/3DEngineCpp/blob/master/src/rendering/lighting.h
// and  https://github.com/BennyQBD/3DEngineCpp/blob/master/src/rendering/lighting.cpp
// with reference to https://learnopengl.com/Lighting/Multiple-lights

namespace Flow {

	// Basic light which consists of an ambient, diffuse and specular intensity
	// This class should only be used a parent class.
	class BaseLight : public Component
	{

		CLASS_DECLARATION(BaseLight)

	public: 
		BaseLight(GameObject* gameObject, const Vec3& ambient, const Vec3& diffuse, const Vec3& specular, bool enabled = true)
			: Component(gameObject, enabled), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular) {}

		inline const Vec3& GetAmbientIntensity() const{ return m_Ambient; }
		inline const Vec3& GetDiffuseIntensity() const { return m_Diffuse; }
		inline const Vec3& GetSpecularIntensity() const { return m_Specular; }

	protected:		
		// intensities
		Vec3 m_Ambient;
		Vec3 m_Diffuse;
		Vec3 m_Specular;
	};

	// Constructor: DirectionalLight(GameObject* gameObject, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular)
	// DirectionalLight (for example a sun) is made up of ambient, diffuse and specular intensity and a direction of the light.
	class DirectionalLight : public BaseLight
	{

		CLASS_DECLARATION(DirectionalLight)

	public:
		DirectionalLight(GameObject* gameObject, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular, bool enabled = true)
			: BaseLight(gameObject, ambient, diffuse, specular, enabled), m_Direction(direction) {}

		inline const Vec3& GetDirection() const { return m_Direction; }

	private:
		Vec3 m_Direction;
	};

	// To reduce the intensity of light, over the distance a light ray travels, is generally called attenuation.
	// In the shader float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	class Attenuation
	{
		
	public:
		Attenuation(float constant = 0, float linear = 0, float exponent = 1)
			: m_Constant(constant), m_Linear(linear), m_Exponent(exponent) {}

		inline float GetConstant() const { return m_Constant; }
		inline float GetLinear() const { return m_Linear; }
		inline float GetExponent() const { return m_Exponent; }

	private:
		float m_Constant;
		float m_Linear;
		float m_Exponent;
	};

	// Constructor: PointLight(GameObject* gameObject, Vec3 ambient, Vec3 diffuse, Vec3 specular, const Attenuation& attenuation = Attenuation())
	// A point light is a light source with a given position somewhere in a world 
	// that illuminates in all directions where the light rays fade out over distance. 
	// Think of light bulbs and torches as light casters that act as a point light.
	class PointLight : public BaseLight
	{

		CLASS_DECLARATION(PointLight)

	public:
		PointLight(GameObject* gameObject, Vec3 ambient, Vec3 diffuse, Vec3 specular, const Attenuation& attenuation = Attenuation(), bool enabled = true)
			: BaseLight(gameObject, ambient, diffuse, specular, enabled), m_Attenuation(attenuation) {}

		inline const Attenuation& GetAttenuation() const{ return m_Attenuation; }

	private:
		Attenuation m_Attenuation;
	};

	// Constructor: SpotLight(GameObject* gameObject, Vec3 ambient, Vec3 diffuse, Vec3 specular, DIRECTIONS direction, float cutoff, float outerCutoff, const Attenuation& attenuation = Attenuation())
	// A spotlight is a light source that is located somewhere in the environment that, 
	// instead of shooting light rays in all directions, only shoots them in a specific direction. 
	// The result is that only the objects within a certain radius of the spotlight's direction are lit and everything else stays dark. 
	// A good example of a spotlight would be a street lamp or a flashlight.
	class SpotLight : public BaseLight
	{

		CLASS_DECLARATION(SpotLight)

	public:
		SpotLight(GameObject* gameObject, Vec3 ambient, Vec3 diffuse, Vec3 specular, DIRECTIONS direction, 
			float cutoff, float outerCutoff, const Attenuation& attenuation = Attenuation(), bool enabled = true)
			: BaseLight(gameObject, ambient, diffuse, specular, enabled), m_Direction(direction), m_Cutoff(cutoff), m_OuterCutoff(outerCutoff), m_Attenuation(attenuation) {}

		inline const Attenuation& GetAttenuation() const { return m_Attenuation; }
		const Vec3& GetDirection() const 
		{ 
			Vec3 direction = Vec3(0.0f);
			if (m_Direction == DIRECTIONS::up)
			{
				direction += GetTransform().GetUpVector();
			}
			else if(m_Direction == DIRECTIONS::down)
			{
				direction -= GetTransform().GetUpVector();
			}
			else if (m_Direction == DIRECTIONS::right)
			{
				direction += GetTransform().GetRightVector();
			}
			else if (m_Direction == DIRECTIONS::left)
			{
				direction -= GetTransform().GetRightVector();
			}
			else if (m_Direction == DIRECTIONS::front)
			{
				direction += GetTransform().GetFrontVector();
			}
			else if(m_Direction == DIRECTIONS::back)
			{
				direction -= GetTransform().GetFrontVector();
			}

			return direction; 
		}
		inline const float GetCutoff() const { return m_Cutoff; }
		inline const float GetOuterCutoff() const { return m_OuterCutoff; }

	private:
		Attenuation m_Attenuation;
		DIRECTIONS m_Direction;
		float m_Cutoff;
		float m_OuterCutoff;
	};
}