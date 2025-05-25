#pragma once

#include "Core.h"

namespace rg {
	class RG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// define this in the CLIENT
	Application* CreateApplication();
}

