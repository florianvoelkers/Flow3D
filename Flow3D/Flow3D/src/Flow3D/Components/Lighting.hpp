#pragma once

#include "Component.hpp"
#include "Flow3D/Math.hpp"
#include "Flow3D/Color.hpp"

// from https://github.com/BennyQBD/3DEngineCpp/blob/master/src/rendering/lighting.h
// and  https://github.com/BennyQBD/3DEngineCpp/blob/master/src/rendering/lighting.cpp

namespace Flow {

	class BaseLight : public Component
	{

		CLASS_DECLARATION(BaseLight)

	public: 
		BaseLight(GameObject* gameObject, const Color& color, const Vec3& ambient, const Vec3& diffuse, const Vec3& specular)
			: Component(gameObject), m_Color(color), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular) {}

		inline const Color& GetColor() const { return m_Color; }
		inline const Vec3& GetAmbientIntensity() const{ return m_Ambient; }
		inline const Vec3& GetDiffuseIntensity() const { return m_Diffuse; }
		inline const Vec3& GetSpecularIntensity() const { return m_Specular; }

	protected:
		Color m_Color;
		
		// intensities
		Vec3 m_Ambient;
		Vec3 m_Diffuse;
		Vec3 m_Specular;
	};

	class DirectionalLight : public BaseLight
	{

		CLASS_DECLARATION(DirectionalLight)

	public:
		DirectionalLight(GameObject* gameObject, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular, const Color& color = Color(0.0f, 0.0f, 0.0f))
			: BaseLight(gameObject, color, ambient, diffuse, specular), m_Direction(direction) {}

		inline const Vec3& GetDirection() const { return m_Direction; }

	private:
		Vec3 m_Direction;
	};

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

	class PointLight : public BaseLight
	{

		CLASS_DECLARATION(PointLight)

	public:
		PointLight(GameObject* gameObject, Vec3 ambient, Vec3 diffuse, Vec3 specular, const Color& color = Color(0.0f, 0.0f, 0.0f), const Attenuation& attenuation = Attenuation())
			: BaseLight(gameObject, color, ambient, diffuse, specular), m_Attenuation(attenuation) {}

		inline const Attenuation& GetAttenuation() const{ return m_Attenuation; }

	private:
		Attenuation m_Attenuation;
	};

	class SpotLight : public BaseLight
	{

		CLASS_DECLARATION(SpotLight)

	public:
		SpotLight(GameObject* gameObject, Vec3 ambient, Vec3 diffuse, Vec3 specular, DIRECTIONS direction, float cutoff, float outerCutoff,
					const Color& color = Color(0.0f, 0.0f, 0.0f), const Attenuation& attenuation = Attenuation())
			: BaseLight(gameObject, color, ambient, diffuse, specular), m_Direction(direction), m_Cutoff(cutoff), m_OuterCutoff(outerCutoff), m_Attenuation(attenuation) {}

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