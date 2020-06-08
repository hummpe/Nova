#pragma once

#include "Event.h"

// TODO: Maybe move these kind of include into "Core.h"?
#include <sstream>

namespace Nova {

	class NOVA_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX{ x }, m_MouseY{ y } {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		// Maybe not the "fastest"/best performance way of doing it
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class NOVA_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset{ xOffset }, m_YOffset{ yOffset } {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class NOVA_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		// Protected constructor so that you can't create an instance
		// of MouseButtonEvent anywhere than from derived classes
		MouseButtonEvent(int button)
			: m_Button{ button } {}

		int m_Button;
	};

	class NOVA_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent{ button } {}

		std::string ToString() const override
		{
			// Maybe not the "fastest"/best performance way of doing it
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class NOVA_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent{ button } {}

		std::string ToString() const override
		{
			// Maybe not the "fastest"/best performance way of doing it
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}