#pragma once
#include "Tepch.h"
#include "TrEngine/Core.h"
#include <spdlog/fmt/ostr.h>

namespace TrEngine {

  
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4),
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                    virtual EventType GetEventType() const override { return GetStaticType(); }\
                                    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class TE_API Event {
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }
        inline bool IsInCategory(EventCategory category) {
            return GetCategoryFlags() & category;
        }

        
        bool IsHandled() const { return m_Handled; }
        void SetHandled(bool handled) { m_Handled = handled; }

    protected:
        bool m_Handled = false;

       
        friend class EventDispatcher;
    };


    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : m_Event(event) {}

        template<typename T>
        bool Dispatch(EventFn<T> func) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.SetHandled(func(static_cast<T&>(m_Event)));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };



    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.ToString();
    }

}


namespace fmt {
    template <>
    struct formatter<TrEngine::Event> {
        template <typename ParseContext>
        constexpr auto parse(ParseContext& ctx) {
            return ctx.begin();
        }

        template <typename FormatContext>
        auto format(const TrEngine::Event& e, FormatContext& ctx) {
            
            return format_to(ctx.out(), "Event: {}", e.ToString());
        }
    };
}
