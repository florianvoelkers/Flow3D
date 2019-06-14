#pragma once

#include "Component.hpp"

#include "Flow3D/Application.hpp"
#include "Lighting.hpp"

#include "Flow3D/Rendering/Model.hpp"
#include "Flow3D/Rendering/Shader.hpp"

#include "Flow3D/Log.hpp"


namespace Flow {

	// Constructor: Renderable(GameObject& gameObject, Model model, Shader shader, bool blending = false, bool enabled = true)
	// Gives functionality and data for drawing any model with the given shader.
	// Enables blending in the rendering engine if necessary
	class Renderable : public Component
	{

		CLASS_DECLARATION(Renderable)

	public:
		Renderable(GameObject& gameObject, std::shared_ptr<Model> model = std::make_shared<Model>(std::make_shared<Cube>(0.5f, 0.5f, 0.5f, 1.0f)), 
			std::shared_ptr<Shader> shader = Application::Get().GetAllShaders().at(1), bool blending = false, bool enabled = true)
			: m_Model(model), m_Shader(shader), m_Blending(blending), Component(gameObject, enabled, "Renderable") {}

		virtual void Render(Mat4 view, Mat4 projection, RenderingEngine& renderingEngine) override
		{
			// calculate position of model
			// TODO: consider the parents Transform
			Mat4 model = Mat4(GetTransform().GetTransformation());

			renderingEngine.SetBlending(m_Blending);

			m_Shader->Use();
			m_Shader->SetMat4("projection", projection);
			m_Shader->SetMat4("view", view);
			m_Shader->SetMat4("model", model);

			// set view pos, set directional light, set point lights, set spot light, material set in model
			m_Shader->SetVec3("viewPos", renderingEngine.GetViewPosition());
			// directional light
			DirectionalLight& directionalLight = Application::Get().GetCurrentScene().GetDirectionalLight();
			m_Shader->SetVec3("dirLight.direction", directionalLight.GetDirection());
			m_Shader->SetVec3("dirLight.ambient", directionalLight.GetAmbientIntensity());
			m_Shader->SetVec3("dirLight.diffuse", directionalLight.GetDiffuseIntensity());
			m_Shader->SetVec3("dirLight.specular", directionalLight.GetSpecularIntensity());

			std::vector<PointLight*> pointLights = Application::Get().GetCurrentScene().GetPointLights();
			std::string uniform;
			m_Shader->SetInt("numberOfPointLights", (int)pointLights.size());
			for (unsigned int i = 0; i < pointLights.size(); i++)
			{
				uniform += std::string("pointLights[") + std::to_string(i) + std::string("].");
				std::string shaderString = uniform + std::string("position");
				m_Shader->SetVec3(shaderString, pointLights[i]->GetTransform().GetWorldPosition());
				if (pointLights[i]->GetEnabled() && pointLights[i]->GetGameObject().GetIsActive())
				{
					shaderString = uniform + std::string("ambient");
					m_Shader->SetVec3(shaderString, pointLights[i]->GetAmbientIntensity());
					shaderString = uniform + std::string("diffuse");
					m_Shader->SetVec3(shaderString, pointLights[i]->GetDiffuseIntensity());
					shaderString = uniform + std::string("specular");
					m_Shader->SetVec3(shaderString, pointLights[i]->GetSpecularIntensity());
				}
				else
				{
					shaderString = uniform + std::string("ambient");
					m_Shader->SetVec3(shaderString, Vec3(0.0f, 0.0f, 0.0f));
					shaderString = uniform + std::string("diffuse");
					m_Shader->SetVec3(shaderString, Vec3(0.0f, 0.0f, 0.0f));
					shaderString = uniform + std::string("specular");
					m_Shader->SetVec3(shaderString, Vec3(0.0f, 0.0f, 0.0f));
				}				
				shaderString = uniform + std::string("constant");
				m_Shader->SetFloat(shaderString, pointLights[i]->GetAttenuation().GetConstant());
				shaderString = uniform + std::string("linear");
				m_Shader->SetFloat(shaderString, pointLights[i]->GetAttenuation().GetLinear());
				shaderString = uniform + std::string("quadratic");
				m_Shader->SetFloat(shaderString, pointLights[i]->GetAttenuation().GetExponent());
				uniform = "";
			}

			std::vector<SpotLight*> spotLights = Application::Get().GetCurrentScene().GetSpotLights();
			m_Shader->SetInt("numberOfSpotLights", (int)spotLights.size());
			for (unsigned int i = 0; i < spotLights.size(); i++)
			{
				// temporary solution for disabling spotlights
				
				uniform += std::string("spotLights[") + std::to_string(i) + std::string("].");
				std::string shaderString = uniform + std::string("position");
				m_Shader->SetVec3(shaderString, spotLights[i]->GetTransform().GetWorldPosition());
				shaderString = uniform + std::string("direction");
				m_Shader->SetVec3(shaderString, spotLights[i]->GetDirection());
				shaderString = uniform + std::string("cutOff");
				m_Shader->SetFloat(shaderString, glm::cos(glm::radians(spotLights[i]->GetCutoff())));
				shaderString = uniform + std::string("outerCutOff");
				m_Shader->SetFloat(shaderString, glm::cos(glm::radians(spotLights[i]->GetOuterCutoff())));
				if (spotLights[i]->GetEnabled() && spotLights[i]->GetGameObject().GetIsActive() )
				{
					shaderString = uniform + std::string("ambient");
					m_Shader->SetVec3(shaderString, spotLights[i]->GetAmbientIntensity());
					shaderString = uniform + std::string("diffuse");
					m_Shader->SetVec3(shaderString, spotLights[i]->GetDiffuseIntensity());
					shaderString = uniform + std::string("specular");
					m_Shader->SetVec3(shaderString, spotLights[i]->GetSpecularIntensity());
				}
				else
				{
					shaderString = uniform + std::string("ambient");
					m_Shader->SetVec3(shaderString, Vec3(0.0f, 0.0f, 0.0f));
					shaderString = uniform + std::string("diffuse");
					m_Shader->SetVec3(shaderString, Vec3(0.0f, 0.0f, 0.0f));
					shaderString = uniform + std::string("specular");
					m_Shader->SetVec3(shaderString, Vec3(0.0f, 0.0f, 0.0f));
				}
				shaderString = uniform + std::string("constant");
				m_Shader->SetFloat(shaderString, spotLights[i]->GetAttenuation().GetConstant());
				shaderString = uniform + std::string("linear");
				m_Shader->SetFloat(shaderString, spotLights[i]->GetAttenuation().GetLinear());
				shaderString = uniform + std::string("quadratic");
				m_Shader->SetFloat(shaderString, spotLights[i]->GetAttenuation().GetExponent());
				uniform = "";				
			}

			m_Model->Draw(*m_Shader);

			// reset blending to default
			renderingEngine.SetBlending(false);
		}

		void SetShader(std::shared_ptr<Shader> shader) {	m_Shader = shader; }
		Model& GetModel() { return *m_Model; }
		Shader& GetShader() { return *m_Shader; }

	private:
		std::shared_ptr<Model> m_Model;
		std::shared_ptr<Shader> m_Shader;
		bool m_Blending;
	};
}