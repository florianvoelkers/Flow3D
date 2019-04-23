#pragma once

#include "Flow3D/GameObject.hpp"

namespace Flow {

	class Component
	{
	public:
		Component() {}
		virtual ~Component() {}

		virtual void OnUpdate (double deltaTime) {}
		virtual void OnEvent (Event& event) {}
		virtual void Render () {}

	private:

	};
}
