#pragma once
#include <unordered_map>

#include "imgui_impl_glfw.h"
#include "TrEngine/Layer.h"

#include "imgui.h"

#include "TrEngine/Application.h"

namespace TrEngine
{
	struct WindowData
	{
		bool isOpen = true;
		ImGuiWindowFlags flags = 0;
	};

	class TE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
	public:
		void NewWindow(const std::string& name, ImGuiWindowFlags flags = 0);
		void CloseWindow(const std::string& name);
		void SetupDockSpace();
	private:
		float m_Time = 0.0f;
		std::unordered_map<std::string, WindowData> m_Windows;
	};
}