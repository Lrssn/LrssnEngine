#pragma once

namespace LrssnEngine {
	typedef enum class KeyCode : uint16_t 	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

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

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
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
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode) 	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define LE_KEY_SPACE           ::LrssnEngine::Key::Space
#define LE_KEY_APOSTROPHE      ::LrssnEngine::Key::Apostrophe    /* ' */
#define LE_KEY_COMMA           ::LrssnEngine::Key::Comma         /* , */
#define LE_KEY_MINUS           ::LrssnEngine::Key::Minus         /* - */
#define LE_KEY_PERIOD          ::LrssnEngine::Key::Period        /* . */
#define LE_KEY_SLASH           ::LrssnEngine::Key::Slash         /* / */
#define LE_KEY_0               ::LrssnEngine::Key::D0
#define LE_KEY_1               ::LrssnEngine::Key::D1
#define LE_KEY_2               ::LrssnEngine::Key::D2
#define LE_KEY_3               ::LrssnEngine::Key::D3
#define LE_KEY_4               ::LrssnEngine::Key::D4
#define LE_KEY_5               ::LrssnEngine::Key::D5
#define LE_KEY_6               ::LrssnEngine::Key::D6
#define LE_KEY_7               ::LrssnEngine::Key::D7
#define LE_KEY_8               ::LrssnEngine::Key::D8
#define LE_KEY_9               ::LrssnEngine::Key::D9
#define LE_KEY_SEMICOLON       ::LrssnEngine::Key::Semicolon     /* ; */
#define LE_KEY_EQUAL           ::LrssnEngine::Key::Equal         /* = */
#define LE_KEY_A               ::LrssnEngine::Key::A
#define LE_KEY_B               ::LrssnEngine::Key::B
#define LE_KEY_C               ::LrssnEngine::Key::C
#define LE_KEY_D               ::LrssnEngine::Key::D
#define LE_KEY_E               ::LrssnEngine::Key::E
#define LE_KEY_F               ::LrssnEngine::Key::F
#define LE_KEY_G               ::LrssnEngine::Key::G
#define LE_KEY_H               ::LrssnEngine::Key::H
#define LE_KEY_I               ::LrssnEngine::Key::I
#define LE_KEY_J               ::LrssnEngine::Key::J
#define LE_KEY_K               ::LrssnEngine::Key::K
#define LE_KEY_L               ::LrssnEngine::Key::L
#define LE_KEY_M               ::LrssnEngine::Key::M
#define LE_KEY_N               ::LrssnEngine::Key::N
#define LE_KEY_O               ::LrssnEngine::Key::O
#define LE_KEY_P               ::LrssnEngine::Key::P
#define LE_KEY_Q               ::LrssnEngine::Key::Q
#define LE_KEY_R               ::LrssnEngine::Key::R
#define LE_KEY_S               ::LrssnEngine::Key::S
#define LE_KEY_T               ::LrssnEngine::Key::T
#define LE_KEY_U               ::LrssnEngine::Key::U
#define LE_KEY_V               ::LrssnEngine::Key::V
#define LE_KEY_W               ::LrssnEngine::Key::W
#define LE_KEY_X               ::LrssnEngine::Key::X
#define LE_KEY_Y               ::LrssnEngine::Key::Y
#define LE_KEY_Z               ::LrssnEngine::Key::Z
#define LE_KEY_LEFT_BRACKET    ::LrssnEngine::Key::LeftBracket   /* [ */
#define LE_KEY_BACKSLASH       ::LrssnEngine::Key::Backslash     /* \ */
#define LE_KEY_RIGHT_BRACKET   ::LrssnEngine::Key::RightBracket  /* ] */
#define LE_KEY_GRAVE_ACCENT    ::LrssnEngine::Key::GraveAccent   /* ` */
#define LE_KEY_WORLD_1         ::LrssnEngine::Key::World1        /* non-US #1 */
#define LE_KEY_WORLD_2         ::LrssnEngine::Key::World2        /* non-US #2 */

/* Function keys */
#define LE_KEY_ESCAPE          ::LrssnEngine::Key::Escape
#define LE_KEY_ENTER           ::LrssnEngine::Key::Enter
#define LE_KEY_TAB             ::LrssnEngine::Key::Tab
#define LE_KEY_BACKSPACE       ::LrssnEngine::Key::Backspace
#define LE_KEY_INSERT          ::LrssnEngine::Key::Insert
#define LE_KEY_DELETE          ::LrssnEngine::Key::Delete
#define LE_KEY_RIGHT           ::LrssnEngine::Key::Right
#define LE_KEY_LEFT            ::LrssnEngine::Key::Left
#define LE_KEY_DOWN            ::LrssnEngine::Key::Down
#define LE_KEY_UP              ::LrssnEngine::Key::Up
#define LE_KEY_PAGE_UP         ::LrssnEngine::Key::PageUp
#define LE_KEY_PAGE_DOWN       ::LrssnEngine::Key::PageDown
#define LE_KEY_HOME            ::LrssnEngine::Key::Home
#define LE_KEY_END             ::LrssnEngine::Key::End
#define LE_KEY_CAPS_LOCK       ::LrssnEngine::Key::CapsLock
#define LE_KEY_SCROLL_LOCK     ::LrssnEngine::Key::ScrollLock
#define LE_KEY_NUM_LOCK        ::LrssnEngine::Key::NumLock
#define LE_KEY_PRINT_SCREEN    ::LrssnEngine::Key::PrintScreen
#define LE_KEY_PAUSE           ::LrssnEngine::Key::Pause
#define LE_KEY_F1              ::LrssnEngine::Key::F1
#define LE_KEY_F2              ::LrssnEngine::Key::F2
#define LE_KEY_F3              ::LrssnEngine::Key::F3
#define LE_KEY_F4              ::LrssnEngine::Key::F4
#define LE_KEY_F5              ::LrssnEngine::Key::F5
#define LE_KEY_F6              ::LrssnEngine::Key::F6
#define LE_KEY_F7              ::LrssnEngine::Key::F7
#define LE_KEY_F8              ::LrssnEngine::Key::F8
#define LE_KEY_F9              ::LrssnEngine::Key::F9
#define LE_KEY_F10             ::LrssnEngine::Key::F10
#define LE_KEY_F11             ::LrssnEngine::Key::F11
#define LE_KEY_F12             ::LrssnEngine::Key::F12
#define LE_KEY_F13             ::LrssnEngine::Key::F13
#define LE_KEY_F14             ::LrssnEngine::Key::F14
#define LE_KEY_F15             ::LrssnEngine::Key::F15
#define LE_KEY_F16             ::LrssnEngine::Key::F16
#define LE_KEY_F17             ::LrssnEngine::Key::F17
#define LE_KEY_F18             ::LrssnEngine::Key::F18
#define LE_KEY_F19             ::LrssnEngine::Key::F19
#define LE_KEY_F20             ::LrssnEngine::Key::F20
#define LE_KEY_F21             ::LrssnEngine::Key::F21
#define LE_KEY_F22             ::LrssnEngine::Key::F22
#define LE_KEY_F23             ::LrssnEngine::Key::F23
#define LE_KEY_F24             ::LrssnEngine::Key::F24
#define LE_KEY_F25             ::LrssnEngine::Key::F25

/* Keypad */
#define LE_KEY_KP_0            ::LrssnEngine::Key::KP0
#define LE_KEY_KP_1            ::LrssnEngine::Key::KP1
#define LE_KEY_KP_2            ::LrssnEngine::Key::KP2
#define LE_KEY_KP_3            ::LrssnEngine::Key::KP3
#define LE_KEY_KP_4            ::LrssnEngine::Key::KP4
#define LE_KEY_KP_5            ::LrssnEngine::Key::KP5
#define LE_KEY_KP_6            ::LrssnEngine::Key::KP6
#define LE_KEY_KP_7            ::LrssnEngine::Key::KP7
#define LE_KEY_KP_8            ::LrssnEngine::Key::KP8
#define LE_KEY_KP_9            ::LrssnEngine::Key::KP9
#define LE_KEY_KP_DECIMAL      ::LrssnEngine::Key::KPDecimal
#define LE_KEY_KP_DIVIDE       ::LrssnEngine::Key::KPDivide
#define LE_KEY_KP_MULTIPLY     ::LrssnEngine::Key::KPMultiply
#define LE_KEY_KP_SUBTRACT     ::LrssnEngine::Key::KPSubtract
#define LE_KEY_KP_ADD          ::LrssnEngine::Key::KPAdd
#define LE_KEY_KP_ENTER        ::LrssnEngine::Key::KPEnter
#define LE_KEY_KP_EQUAL        ::LrssnEngine::Key::KPEqual

#define LE_KEY_LEFT_SHIFT      ::LrssnEngine::Key::LeftShift
#define LE_KEY_LEFT_CONTROL    ::LrssnEngine::Key::LeftControl
#define LE_KEY_LEFT_ALT        ::LrssnEngine::Key::LeftAlt
#define LE_KEY_LEFT_SUPER      ::LrssnEngine::Key::LeftSuper
#define LE_KEY_RIGHT_SHIFT     ::LrssnEngine::Key::RightShift
#define LE_KEY_RIGHT_CONTROL   ::LrssnEngine::Key::RightControl
#define LE_KEY_RIGHT_ALT       ::LrssnEngine::Key::RightAlt
#define LE_KEY_RIGHT_SUPER     ::LrssnEngine::Key::RightSuper
#define LE_KEY_MENU            ::LrssnEngine::Key::Menu