#pragma once

#include "LrssnEngine/Core/Base.h"
#include "LrssnEngine/Core/KeyCodes.h"
#include "LrssnEngine/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace LrssnEngine {

	class Input {
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}