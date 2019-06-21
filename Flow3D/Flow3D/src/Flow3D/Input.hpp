#pragma once

#include "Math.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

namespace Flow {

	// most common GLFW keycodes for mouse and keyboard
	enum class Keycode {
		MouseLeft = 0,
		MouseRight = 1,
		MouseMiddle = 2,

		Space = 32,
		Apostrophe = 39,
		Comma = 44,
		Minus = 45,
		Period = 46,
		Slash = 47,
		Key0 = 48,
		Key1 = 49,
		Key2 = 50,
		Key3 = 51,
		Key4 = 52,
		Key5 = 53,
		Key6 = 54,
		Key7 = 55,
		Key8 = 56,
		Key9 = 57,
		Semicolon = 59,
		Equal = 61,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LeftBracket = 91,
		Backslash = 92,
		RightBracket = 93,
		GraveAccent = 96,
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		Num0 = 320,
		Num1 = 321,
		Num2 = 322,
		Num3 = 323,
		Num4 = 324,
		Num5 = 325,
		Num6 = 326,
		Num7 = 327,
		Num8 = 328,
		Num9 = 329,
		Decimal = 330,
		Divide = 331,
		Multiply = 332,
		Subtract = 333,
		Add = 334,
		NumEnter = 335,
		NumEqual = 336,
		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	};

	// This class handles everything related to input. At the moment keyboard and mouse.
	// It receives OnEvent calls from the window and depending on the event it changes
	// the state of key-state and mouse-state arrays. It provides several methods to access
	// the current state of key or the mouse. There can be only one instance of Input.
	class Input {
	public:
		Input();
		virtual ~Input() {}

		void OnUpdate(double deltaTime);
		void OnEvent(Event& event);

		inline static Input& Get() { return *s_Instance; }

		inline bool GetKey(Keycode keyCode) const { return m_Inputs[(int)keyCode]; }
		inline bool GetKey(int keyCode) const { return m_Inputs[keyCode]; }
		inline bool GetKeyDown(Keycode keyCode) const { return m_DownKeys[(int)keyCode]; }
		inline bool GetKeyDown(int keyCode) const { return m_DownKeys[keyCode]; }
		inline bool GetKeyUp(Keycode keyCode) const { return m_UpKeys[(int)keyCode]; }
		inline bool GetKeyUp(int keyCode) const { return m_UpKeys[keyCode]; }
		inline bool GetMouse(Keycode keyCode) const { return m_MouseInput[(int)keyCode]; }
		inline bool GetMouse(int keyCode) const { return m_MouseInput[keyCode]; }
		inline bool GetMouseDown(Keycode keyCode) const { return m_DownMouse[(int)keyCode]; }
		inline bool GetMouseDown(int keyCode) const { return m_DownMouse[keyCode]; }
		inline bool GetMouseUp(Keycode keyCode) const { return m_UpMouse[(int)keyCode]; }
		inline bool GetMouseUp(int keyCode) const { return m_UpMouse[keyCode]; }

		// temporary functions for mouseX and mouseY, later Vector2
		inline Vec2 GetMousePosition() const { return m_MousePosition; }

		inline std::vector<std::tuple<Keycode, const char*>>& GetKeyMap() { return keyMap; }

		static const int NUMBER_OF_KEYS = 512;
		static const int NUMBER_OF_MOUSEBUTTONS = 16;

	private:
		static Input* s_Instance;

		std::vector<std::tuple<Keycode, const char*>> keyMap;

		bool m_Inputs[NUMBER_OF_KEYS]; // 
		bool m_DownKeys[NUMBER_OF_KEYS]; // reset every frame
		bool m_UpKeys[NUMBER_OF_KEYS]; // reset every frame
		bool m_MouseInput[NUMBER_OF_MOUSEBUTTONS];
		bool m_DownMouse[NUMBER_OF_MOUSEBUTTONS]; // reset every frame
		bool m_UpMouse[NUMBER_OF_MOUSEBUTTONS]; // reset every frame
		Vec2 m_MousePosition;

		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
	};
}
