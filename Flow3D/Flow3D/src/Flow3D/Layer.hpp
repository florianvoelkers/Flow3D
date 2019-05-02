#pragma once

#include "Core.hpp"
#include "Events\Event.hpp"

namespace Flow {

	// Layers make up everything the user sees from the actual application, UI elements
	// or overlays like ImGui.
	// TODO: rethink layer architecture; maybe add render method
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(double deltaTime) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}

