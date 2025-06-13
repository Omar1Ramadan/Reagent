#pragma once
#include "rgpch.h"
#include "../Core.h"


namespace rg {
	/*
	* Events are blocked such that when they occur, they are immediately processed to the dispatcher
	* some form of buffering inside an active event might be useful addition in the future
	* bus and process them during the "event" of the update stage
	*/
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, // window specific events
		AppTick, AppUpdate, AppRender, // application lifecycle events
		KeyPressed, KeyReleased, KeyTyped, // keyboard events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled // mouse events
	};

	// Event mapping to identfy the type of event that has occured
	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	// define a struct that will define the event types for any given returned event
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
	virtual EventType GetEventType() const override { return GetStaticType(); } \
	virtual const char* GetName() const override { return #type; }

// define a macro to define the category of the event 
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	// define general event class that will be the parent of all events in the system
	class Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	// define a dispatcher class that will be used to dispatch events to the appropriate handlers
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {
		}
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// overload the output stream operator for event class to pring the event name
	inline std::ostream& operator <<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}