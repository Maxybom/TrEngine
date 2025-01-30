#pragma once

#include "TrEngine/Input.h"


namespace TrEngine
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl( int keycode ) override;
		virtual bool IsMouseButtonPressedImpl( int button ) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}

#include "Tepch.h"
#include "WindowsInput.h"
#include "TrEngine/Application.h"

#include <GLFW/glfw3.h>

namespace TrEngine
{
    // Inizializzazione della variabile statica s_Instance
    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl( int keycode )
    {
        if (ImGui::GetIO().WantCaptureKeyboard) return false; // Blocca input se ImGui lo sta gestendo
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey( window, keycode );
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }


    bool WindowsInput::IsMouseButtonPressedImpl( int button )
    {
        if (ImGui::GetIO().WantCaptureMouse) return false; // Blocca input se ImGui lo sta gestendo
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton( window, button );
        return state == GLFW_PRESS;
    }


    std::pair<float, float> WindowsInput::GetMousePositionImpl()
    {
        if (ImGui::GetIO().WantCaptureMouse) return {0.0f, 0.0f}; // Blocca il mouse se ImGui lo sta gestendo
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos( window, &xPos, &yPos );
        return {static_cast<float>(xPos), static_cast<float>(yPos)};
    }

    float WindowsInput::GetMouseXImpl()
    {
        return GetMousePositionImpl().first;
    }

    float WindowsInput::GetMouseYImpl()
    {
        return GetMousePositionImpl().second;
    }
}
