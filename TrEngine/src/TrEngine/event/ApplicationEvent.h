#pragma once
#include "Event.h"

namespace TrEngine
{
	class TE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		virtual ~WindowResizeEvent() = default;

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class TE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
		virtual	~WindowCloseEvent();

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class TE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;
		virtual ~AppTickEvent();
		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class TE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;
		virtual	~AppUpdateEvent();

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class TE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;
		virtual ~AppRenderEvent();

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
