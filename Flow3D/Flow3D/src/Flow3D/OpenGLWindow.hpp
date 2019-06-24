#pragma once

#include "Window.hpp"
#include "Flow3D/Math.hpp"

#include "GLFW\glfw3.h"

// Creates and sets up an OpenGl window using the GLFW library.
// It also handles forwarding window, key and mouse events by setting callbacks to GLFW event functions.
// The callback method for those events is set in Application.cpp.
// TODO: create functionality to customize the window and it's properties
class OpenGLWindow : public Window
{
public:
	OpenGLWindow(const WindowProperties& properties);
	virtual ~OpenGLWindow();

	void OnUpdate() override;

	inline unsigned int GetWidth() const override { return m_WindowData.Width; }
	inline unsigned int GetHeight() const override { return m_WindowData.Height; }
		
	virtual void ShowMouse(bool show) override;

	inline void SetEventCallback(const EventCallbackFunction& callback) override { m_WindowData.EventCallback = callback; }
private:
	GLFWwindow* m_Window;
	Vec2 m_OldMouse;

	struct WindowData {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		EventCallbackFunction EventCallback;
	};

	WindowData m_WindowData;

	virtual void Init(const WindowProperties& properties);
};
