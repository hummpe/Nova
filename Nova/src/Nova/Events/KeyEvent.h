#pragma once

#include "Event.h"

namespace Nova {
	
	/**
	* Base class for all KeyEvents
	*/
	class NOVA_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		// Protected constructor so that you can't create an instance
		// of KeyEvent anywhere than from derived classes
		KeyEvent(int keyCode)
			: m_KeyCode{ keyCode } {}

		int m_KeyCode;
	};

	class NOVA_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent{ keyCode }, m_RepeatCount{ repeatCount } {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			// Maybe not the "fastest"/best performance way of doing it
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class NOVA_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent{ keyCode } {}

		std::string ToString() const override
		{
			// Maybe not the "fastest"/best performance way of doing it
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}