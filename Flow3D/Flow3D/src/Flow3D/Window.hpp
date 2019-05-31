#pragma once

#include "Events\Event.hpp"

#include <iostream>
#include <functional>

namespace Flow {

	struct WindowProperties {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title = "Flow3D", unsigned int width = 1840, unsigned int height = 1035)
			: Title(title), Width(width), Height(height) {}
	};

	// Sets the base functionality and data for every window of the Flow3D engine. 
	// The specific platform- and rendering-method-based implementation will be in subclasses.
	class Window
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void ShowMouse(bool show) = 0;

		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}
