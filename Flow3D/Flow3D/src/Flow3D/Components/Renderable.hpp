#pragma once

#include "Component.hpp"

#include "Flow3D/Rendering/Model.hpp"
#include "Flow3D/Rendering/Shader.hpp"

namespace Flow {

	// Gives functionality and data for drawing any model with the given shader.
	// Enables blending in the rendering engine if necessary
	class Renderable : public Component
	{

		CLASS_DECLARATION(Renderable)

	public:
		Renderable(GameObject* gameObject, Model* model, Shader* shader, bool blending)
			: m_Model(model), m_Shader(shader), m_Blending(blending), Component(gameObject)
		{

		}

		~Renderable()
		{
			delete m_Model;
			delete m_Shader;
		}

		virtual void Render(Mat4 view, Mat4 projection, RenderingEngine& renderingEngine) override
		{
			// calculate position of model
			// TODO: consider the parents Transform
			Mat4 model = Mat4();
			model.Translate(GetTransform()->m_Position);
			model.Scale(GetTransform()->m_Scale);

			// rotate around all axis; could produce gimbal lock?
			model.Rotate(GetTransform()->m_Rotation.x, Vec3(1, 0, 0));
			model.Rotate(GetTransform()->m_Rotation.y, Vec3(0, 1, 0));
			model.Rotate(GetTransform()->m_Rotation.z, Vec3(0, 0, 1));

			renderingEngine.SetBlending(m_Blending);

			m_Shader->Use();
			m_Shader->SetMat4("projection", projection);
			m_Shader->SetMat4("view", view);
			m_Shader->SetMat4("model", model);
			
			// set view pos, set directional light, set point lights, set spot light, material set in model
			m_Shader->SetVec3("viewPos", renderingEngine.GetViewPosition());
			// directional light
			/*
			m_Shader->SetVec3("dirLight.direction", renderingEngine.GetDirectionalLight().direction);
			m_Shader->SetVec3("dirLight.ambient", renderingEngine.GetDirectionalLight().ambient);
			m_Shader->SetVec3("dirLight.diffuse", renderingEngine.GetDirectionalLight().diffuse);
			m_Shader->SetVec3("dirLight.specular", renderingEngine.GetDirectionalLight().specular);
			*/

			m_Model->Draw(*m_Shader);

			// reset blending to default
			renderingEngine.SetBlending(false);
		}


	private:
		Model* m_Model;
		Shader* m_Shader;
		bool m_Blending;
	};
}