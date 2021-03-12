#pragma once

#include "LrssnEngine/Core/Base.h"
#include "LrssnEngine/Core/KeyCodes.h"
#include "LrssnEngine/Core/MouseCodes.h"

namespace LrssnEngine {

	class Input {
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}