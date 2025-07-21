#include "../../rgpch.h"
#include"Window.h"


#ifdef RG_WINDOWS
	#include "../../Platform/Windows/WindowsWindow.h"
#endif

namespace rg
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef RG_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		RG_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
}