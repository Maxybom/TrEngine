#pragma once
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "Tepch.h"
#include "TrEngine/Input.h"
#include "TrEngine/Application.h"

namespace TrEngine
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput() = default;
		~WindowsInput() = default;

	protected:
		virtual bool IsKeyPressedImpl(int keycode) override
		{
			if (ImGui::GetIO().WantCaptureKeyboard)
				return false;

			auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetKey(window, keycode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		virtual bool IsMouseButtonPressedImpl(int button) override
		{
			if (ImGui::GetIO().WantCaptureMouse)
				return false;

			auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetMouseButton(window, button);
			return state == GLFW_PRESS;
		}

		virtual std::pair<float, float> GetMousePositionImpl() override
		{
			if (ImGui::GetIO().WantCaptureMouse)
				return {0.0f, 0.0f};

			auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
			double xPos, yPos;
			glfwGetCursorPos(window, &xPos, &yPos);
			return {static_cast<float>(xPos), static_cast<float>(yPos)};
		}

		virtual float GetMouseXImpl() override
		{
			return GetMousePositionImpl().first;
		}

		virtual float GetMouseYImpl() override
		{
			return GetMousePositionImpl().second;
		}

	private:
		static Input* s_Instance;
	};

	// static var initialization
	Input* Input::s_Instance = new WindowsInput();
}