#pragma once

#include "Component.hpp"
#include "Flow3D/Math.hpp"
#include "Flow3D/Color.hpp"

// from https://github.com/BennyQBD/3DEngineCpp/blob/master/src/rendering/lighting.h
// and  https://github.com/BennyQBD/3DEngineCpp/blob/master/src/rendering/lighting.cpp

namespace Flow {

	class BaseLight : public Component
	{

		CLASS_DECLARATION(Lighting)

	public: 
		BaseLight(GameObject* gameObject, const Color& color, float intensity)
			: Component(gameObject), m_Color(color), m_Intensity(intensity)
		{

		}

		inline const Color& GetColor() const { return m_Color; }
		inline const float GetIntensity() const { return m_Intensity; }

	protected:
		Color m_Color;
		float m_Intensity;
	};

	class DirectionalLight : public BaseLight
	{

		CLASS_DECLARATION(DirectionalLight)

	public:
		DirectionalLight(GameObject* gameObject, const Color& color = Color(0.0f, 0.0f, 0.0f), float intensity = 0)
			: BaseLight(gameObject, color, intensity)
		{

		}
	};

	class Attenuation
	{
		
	public:
		Attenuation(float constant = 0, float linear = 0, float exponent = 1)
			: m_Constant(constant), m_Linear(linear), m_Exponent(exponent)
		{}

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
		PointLight(GameObject* gameObject, const Color& color = Color(0.0f, 0.0f, 0.0f), float intensity = 0, const Attenuation& attenuation = Attenuation())
			: BaseLight(gameObject, color, intensity), m_Attenuation(attenuation)
		{
			float a = m_Attenuation.GetExponent();
			float b = m_Attenuation.GetLinear();
			float c = m_Attenuation.GetConstant() - 256 * m_Intensity; // 256 is the COLOR_DEPTH

			m_Range = (-b + sqrtf(b*b - 4 * a*c)) / (2 * a);
		}

	private:
		Attenuation m_Attenuation;
		float m_Range;
	};

	class SpotLight : public BaseLight
	{

		CLASS_DECLARATION(SpotLight)

	public:
		SpotLight(GameObject* gameObject, const Color& color = Color(0.0f, 0.0f, 0.0f), float intensity = 0, const Attenuation& attenuation = Attenuation(), float viewAngle = Math::Radians(170.f))
			: BaseLight(gameObject, color, intensity), m_Attenuation(attenuation), m_Cutoff(Math::Cos(viewAngle/2))
		{
			float a = m_Attenuation.GetExponent();
			float b = m_Attenuation.GetLinear();
			float c = m_Attenuation.GetConstant() - 256 * m_Intensity; // 256 is the COLOR_DEPTH

			m_Range = (-b + sqrtf(b*b - 4 * a*c)) / (2 * a);
		}

	private:
		Attenuation m_Attenuation;
		float m_Range;
		float m_Cutoff;
	};
}