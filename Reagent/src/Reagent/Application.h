#pragma once
#include "rgpch.h"
#include "Core.h"
#include "Events/Event.h"
#include "Core/Window.h";

namespace rg {
	class RG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// define this in the CLIENT
	Application* CreateApplication();
}
