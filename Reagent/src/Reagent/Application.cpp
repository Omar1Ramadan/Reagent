#include "rgpch.h"
#include "Application.h"

#include "Reagent/Events/ApplicationEvent.h"
#include "Reagent/Log.h"

namespace rg {
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run() 
	{

		WindowResizeEvent event(1280, 720);
		if (event.IsInCategory(EventCategoryApplication))
		{
			RG_CORE_INFO("nigagas");
		}
		if (event.IsInCategory(EventCategoryInput))
		{
			RG_CORE_TRACE(event.ToString());
		}
		RG_CORE_TRACE(event.ToString());
		RG_CORE_INFO("Application is running...");

		while (true)
		{
		};
	}
}