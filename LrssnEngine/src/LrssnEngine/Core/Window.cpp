#include "lepch.h"
#include "LrssnEngine/Core/Window.h"

#ifdef LE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace LrssnEngine {

	Scope<Window> Window::Create(const WindowProps& props) 	{
	#ifdef LE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		LE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}