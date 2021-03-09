#include "lepch.h"
#include "LrssnEngine/Core/Input.h"

#ifdef LE_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace LrssnEngine {

	Scope<Input> Input::s_mInstance = Input::Create();

	Scope<Input> Input::Create() 	{
	#ifdef LE_PLATFORM_WINDOWS
			return CreateScope<WindowsInput>();
	#else
			LE_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
	#endif
	}
}