#pragma once

#include "Window.hpp"

#include "GLFW\glfw3.h"

namespace Flow {

	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(const WindowProperties& properties);
		virtual ~OpenGLWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_WindowData.Width; }
		inline unsigned int GetHeight() const override { return m_WindowData.Height; }

		inline void SetEventCallback(const EventCallbackFunction& callback) override { m_WindowData.EventCallback = callback; }
	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;

			EventCallbackFunction EventCallback;
		};

		WindowData m_WindowData;

		virtual void Init(const WindowProperties& properties);
	};
}
