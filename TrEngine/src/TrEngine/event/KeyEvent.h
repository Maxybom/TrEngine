#pragma once
#include "Event.h"

namespace TrEngine
{

    class TE_API KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY( EventCategoryKeyboard | EventCategoryInput )
    protected:
        KeyEvent( int keyCode )
            : m_KeyCode( keyCode )
        {}

        int m_KeyCode;
    };

    class TE_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent( int keyCode, int repeatCount, bool shift, bool ctrl, bool alt, bool super )
            : KeyEvent( keyCode ), m_RepeatCount( repeatCount ), m_Shift( shift ), m_Ctrl( ctrl ), m_Alt( alt ), m_Super( super )
        {}

        inline int GetRepeatCount() const { return m_RepeatCount; }
        inline bool IsShiftPressed() const { return m_Shift; }
        inline bool IsCtrlPressed() const { return m_Ctrl; }
        inline bool IsAltPressed() const { return m_Alt; }
        inline bool IsSuperPressed() const { return m_Super; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE( KeyPressed )
    private:
        int m_RepeatCount;
        bool m_Shift, m_Ctrl, m_Alt, m_Super;
    };

    class TE_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent( int keyCode, bool shift, bool ctrl, bool alt, bool super )
            : KeyEvent( keyCode ), m_Shift( shift ), m_Ctrl( ctrl ), m_Alt( alt ), m_Super( super )
        {}

        inline bool IsShiftPressed() const { return m_Shift; }
        inline bool IsCtrlPressed() const { return m_Ctrl; }
        inline bool IsAltPressed() const { return m_Alt; }
        inline bool IsSuperPressed() const { return m_Super; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE( KeyReleased )
    private:
        bool m_Shift, m_Ctrl, m_Alt, m_Super;
    };

    class TE_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent( int keyCode )
            : KeyEvent( keyCode )
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE( KeyTyped )
    };
}
