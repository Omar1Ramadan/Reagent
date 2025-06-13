#pragma once
#include "rgpch.h"
#include "Event.h"
#include <Reagent/Core/KeyCode.h>

//KeyPressed, KeyReleased, KeyTyped

namespace rg 
{
	class KeyEvent : public Event
	{
	public:
		rg::KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		
	protected:
		KeyEvent(const rg::KeyCode keycode)
			: m_KeyCode(keycode) { }

		rg::KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const rg::KeyCode keycode, bool isRepeat = false)
			: KeyEvent(keycode), m_IsRepeat(isRepeat) { }

		bool isRepeat() const{ return m_IsRepeat; }

		std::string ToString() const override
		{
			return "KeyPressedEvent: " + std::to_string(m_KeyCode) + " (repeat = " + (m_IsRepeat ? "true" : "false") + ")";
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		bool m_IsRepeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) { }
		
		std::string ToString() const override
		{
			return "KeyReleasedEvent: " + std::to_string(m_KeyCode);
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) { }
		
		std::string ToString() const override
		{
			return "KeyTypedEvent: " + std::to_string(m_KeyCode);
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};