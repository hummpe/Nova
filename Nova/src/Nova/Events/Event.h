#pragma once

// TODO: Figure out why novapch.h is needed in here, is it because we don't have a .cpp file for any Event etc?
#include "novapch.h"
#include "Nova/Core.h"

namespace Nova {

	// NOTE: All events in Nova are as of now "blocking", meaning:
	//		 When an event occurs, it gets dispatched immediately and
	//		 needs/must be "taken care of" righ then a there.
	//		 
	//		 In the future, exchange system for a kind of buffer which
	//		 stores all events and process them during the "event" part
	//		 of the update-part

	/**
	* ENUM for identifying an Events Type
	*/
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/**
	 * ENUM for grouping Events together
	 */
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	/**
	* Macros defined for shortening any class that derives from Event
	* Helps when "Implementing" GetEventType, GetName and GetCategoryFlags
	*/

// Takes care of implementing GetEventType and GetName
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

// Takes care of implementing GetCategoryFlags
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class NOVA_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		// TODO: Maybe make GetName method Debug-only?
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		// TODO: Maybe make ToString method Debug-only?
		virtual std::string ToString() const { return GetName(); }

		/**
		* Performs bitwise-& on the category-bitfield
		* to see if Event is part of EventCategory category
		*/
		inline bool IsInCategory(EventCategory category)
		{
			// Return 0 if not in category, anything else => is in category
			return GetCategoryFlags() & category;
		}
	protected:
		// Need to know if Event has been taken care of/handled/consumed or not
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		// T - Any EventType
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event{ event } {}

		// T - Any EventType
		template<typename T>
		bool Dispatch(EventFunc<T> func)
		{
			// If Event you are trying to dispatch matched the type
			// of function func, it will run it and you have
			// successfully dispatched that event
			if (m_Event.GetEventType == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// Operator overload exists mostly for our logging library
	// to easily call ToString from an Event
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}