#include "rgpch.h"
#include "Application.h"

#include "Reagent/Events/ApplicationEvent.h"
#include "Reagent/Log.h"
#include <GLFW/glfw3.h>
#include <Platform/Windows/WindowsWindow.h>

namespace rg {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run() 
	{

		WindowResizeEvent event(1280, 720);
		if (event.IsInCategory(EventCategoryApplication))
		{
			RG_CORE_INFO("Window has been created");
		}
		if (event.IsInCategory(EventCategoryInput))
		{
			RG_CORE_TRACE(event.ToString());
		}
		RG_CORE_TRACE(event.ToString());
		RG_CORE_INFO("Application is running...");

		while (m_Running)
		{
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		};
	}
}