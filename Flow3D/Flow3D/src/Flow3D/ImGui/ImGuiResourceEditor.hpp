#pragma once

#include <imgui/imgui.h>

#include "Flow3D/Application.hpp"
#include "Flow3D/Rendering/Shader.hpp"
#include "Flow3D/Rendering/Texture.hpp"
#include "Flow3D/Rendering/Model.hpp"

namespace Flow {

	struct FlowResourceEditor
	{
		std::vector<std::shared_ptr<Shader>> shaders;
		std::vector<std::shared_ptr<Texture>> textures;
		std::vector<std::shared_ptr<Model>> models;

		FlowResourceEditor();

		void Draw();
	};
}