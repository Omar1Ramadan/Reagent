#pragma once
#include "rgpch.h"

#include "Reagent/Core.h"
#include "Reagent/Events/Event.h"


namespace rg {
	
	// default struct for window properties
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		WindowProps(const std::string& title = "Reagent Engine",
			uint32_t width = 1800,
			uint32_t height = 1000)
			: Title(title), Width(width), Height(height) {}
	};

	// interface for window classes, this will be create windows 
	class Window
	{
	public :
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0; // update the window every frame

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		// static function to create a window instance despite the platform 
		static Scope<Window> Create(const WindowProps& props = WindowProps());

	};
}