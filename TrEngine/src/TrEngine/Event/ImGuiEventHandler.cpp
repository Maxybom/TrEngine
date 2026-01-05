#include "Tepch.h"

#include "ImGuiEventHandler.h"

namespace TrEngine
{
	void ImGuiEventHandler::HandleEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseButtonPressedEvent>(TE_BIND_EVENT_FN(ImGuiEventHandler::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(TE_BIND_EVENT_FN(ImGuiEventHandler::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(TE_BIND_EVENT_FN(ImGuiEventHandler::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(TE_BIND_EVENT_FN(ImGuiEventHandler::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(TE_BIND_EVENT_FN(ImGuiEventHandler::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(TE_BIND_EVENT_FN(ImGuiEventHandler::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(TE_BIND_EVENT_FN(ImGuiEventHandler::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(TE_BIND_EVENT_FN(ImGuiEventHandler::OnWindowResizedEvent));
	}

	bool  ImGuiEventHandler::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiEventHandler::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiEventHandler::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiEventHandler::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
		return false;
	}

	bool ImGuiEventHandler::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey key = GLFWKeyToImGuiKey(e.GetKeyCode());

		if (key != ImGuiKey_None)
		{
			io.AddKeyEvent(key, true);
		}

		if (io.WantCaptureKeyboard)
			return false;

		return false;
	}

	bool ImGuiEventHandler::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey key = GLFWKeyToImGuiKey(e.GetKeyCode());

		if (key != ImGuiKey_None)
		{
			io.AddKeyEvent(key, false);
		}

		return false;
	}

	bool ImGuiEventHandler::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short) keycode);
		return false;
	}

	bool ImGuiEventHandler::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float) e.GetWidth(), (float) e.GetHeight());
		return false;
	}
}