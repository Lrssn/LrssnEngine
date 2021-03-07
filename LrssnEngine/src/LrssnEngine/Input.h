#pragma once

#include "LrssnEngine/Core.h"

namespace LrssnEngine {

	class LrssnEngine_API Input 	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_mInstance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_mInstance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_mInstance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_mInstance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_mInstance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_mInstance;
	};

}