#pragma once

#include "LrssnEngine/Core/Core.h"
#include "LrssnEngine/Core/KeyCodes.h"
#include "LrssnEngine/Core/MouseCodes.h"

namespace LrssnEngine {

	class Input 	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
		inline static bool IsKeyPressed(KeyCode key) { return s_mInstance->IsKeyPressedImpl(key); }

		inline static bool IsMouseButtonPressed(MouseCode button) { return s_mInstance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_mInstance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_mInstance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_mInstance->GetMouseYImpl(); }
		static Scope<Input> Create();
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Scope<Input> s_mInstance;
	};

}