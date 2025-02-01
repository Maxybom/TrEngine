#include "Tepch.h"
#include "ImGuiLayer.h"
#include "TrEngine/Application.h"
#include "TrEngine/Input.h"
#include "TrEngine/KeyCode.h"

namespace TrEngine
{
	ImGuiLayer::ImGuiLayer()
		: Layer( "ImGuiLayer" )
	{}

	ImGuiLayer::~ImGuiLayer() = default;

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL( window, true );
		ImGui_ImplOpenGL3_Init( "#version 130" );

		glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2( app.GetWindow().GetWidth(), app.GetWindow().GetHeight() );

		auto time = (float) glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool showDemoWindow = true;
		ImGui::ShowDemoWindow( &showDemoWindow );

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
		ImGui::EndFrame();
	}

	void ImGuiLayer::OnEvent( Event& event )
	{
		EventDispatcher dispatcher( event );

		dispatcher.Dispatch<MouseButtonPressedEvent>( TE_BIND_EVENT_FN( ImGuiLayer::OnMouseButtonPressedEvent ) );
		dispatcher.Dispatch<MouseButtonReleasedEvent>( TE_BIND_EVENT_FN( ImGuiLayer::OnMouseButtonReleasedEvent ) );
		dispatcher.Dispatch<MouseMovedEvent>( TE_BIND_EVENT_FN( ImGuiLayer::OnMouseMovedEvent ) );
		dispatcher.Dispatch<MouseScrolledEvent>( TE_BIND_EVENT_FN( ImGuiLayer::OnMouseScrolledEvent ) );
		dispatcher.Dispatch<KeyPressedEvent>( TE_BIND_EVENT_FN( ImGuiLayer::OnKeyPressedEvent ) );
		dispatcher.Dispatch<KeyReleasedEvent>( TE_BIND_EVENT_FN( ImGuiLayer::OnKeyReleasedEvent ) );
		dispatcher.Dispatch<KeyTypedEvent>( TE_BIND_EVENT_FN( ImGuiLayer::OnKeyTypedEvent ) );
		dispatcher.Dispatch<WindowResizeEvent>( TE_BIND_EVENT_FN( ImGuiLayer::OnWindowResizedEvent ) );

		if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard)
			event.SetHandled( true );
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent( MouseButtonPressedEvent& e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent( MouseButtonReleasedEvent& e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent( MouseMovedEvent& e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2( e.GetX(), e.GetY() );
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent( MouseScrolledEvent& e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent( KeyPressedEvent& e )
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey key = GLFWKeyToImGuiKey( e.GetKeyCode() );

		if (key != ImGuiKey_None)
		{
			io.AddKeyEvent( key, true );
		}

		if (io.WantCaptureKeyboard) // Evita input non necessari
			return false;

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent( KeyReleasedEvent& e )
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey key = GLFWKeyToImGuiKey( e.GetKeyCode() );

		if (key != ImGuiKey_None)
		{
			io.AddKeyEvent( key, false );
		}

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent( KeyTypedEvent& e )
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter( (unsigned short) keycode );
		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent( WindowResizeEvent& e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2( (float) e.GetWidth(), (float) e.GetHeight() );
		return false;
	}
}
