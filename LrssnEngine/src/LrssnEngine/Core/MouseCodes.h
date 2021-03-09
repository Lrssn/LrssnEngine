#pragma once

namespace LrssnEngine {
	typedef enum class MouseCode : uint16_t 	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode) 	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define LE_MOUSE_BUTTON_0      ::LrssnEngine::Mouse::Button0
#define LE_MOUSE_BUTTON_1      ::LrssnEngine::Mouse::Button1
#define LE_MOUSE_BUTTON_2      ::LrssnEngine::Mouse::Button2
#define LE_MOUSE_BUTTON_3      ::LrssnEngine::Mouse::Button3
#define LE_MOUSE_BUTTON_4      ::LrssnEngine::Mouse::Button4
#define LE_MOUSE_BUTTON_5      ::LrssnEngine::Mouse::Button5
#define LE_MOUSE_BUTTON_6      ::LrssnEngine::Mouse::Button6
#define LE_MOUSE_BUTTON_7      ::LrssnEngine::Mouse::Button7
#define LE_MOUSE_BUTTON_LAST   ::LrssnEngine::Mouse::ButtonLast
#define LE_MOUSE_BUTTON_LEFT   ::LrssnEngine::Mouse::ButtonLeft
#define LE_MOUSE_BUTTON_RIGHT  ::LrssnEngine::Mouse::ButtonRight
#define LE_MOUSE_BUTTON_MIDDLE ::LrssnEngine::Mouse::ButtonMiddle