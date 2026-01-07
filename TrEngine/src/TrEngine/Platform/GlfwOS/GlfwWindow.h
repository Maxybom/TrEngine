#pragma once
#include "TrEngine/Core.h"

#include "TrEngine/Window.h"
#include "TrEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace TrEngine
{
	class GlfwWindow : public Window
	{
	public:
		explicit GlfwWindow(const WindowProps& props);
		~GlfwWindow() override;

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void* GetNativeWindow() const override { return static_cast<void*>(m_Window); }

		// Windows attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		void Init(const WindowProps& props);
		void Shutdown();

		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
