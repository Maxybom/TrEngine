#include "Tepch.h"
#include "ImGuiLayer.h"

namespace TrEngine
{
	ImGuiLayer::ImGuiLayer() : Layer( "ImGuiLayer" ) {}
	ImGuiLayer::~ImGuiLayer() = default;

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		Application& app = Application::Get();
		auto* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL( window, true );
		ImGui_ImplOpenGL3_Init( "#version 130" );

		glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
		

		NewWindow( "Editor", ImGuiWindowFlags_MenuBar );
		NewWindow( "Console", ImGuiWindowFlags_NoCollapse );
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

		SetupDockSpace();

		// window manager
		for (auto it = m_Windows.begin(); it != m_Windows.end();)
		{
			if (it->second.isOpen)
			{
				ImGui::SetNextWindowDockID( ImGui::GetID( "MyDockSpace" ), ImGuiCond_FirstUseEver );
				ImGui::Begin( it->first.c_str(), &it->second.isOpen, it->second.flags );
				ImGui::Text( "Contenuto di %s", it->first.c_str() );
				ImGui::End();
				++it;
			}
			else
			{
				it = m_Windows.erase( it ); //close window
			}
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
		ImGui::EndFrame();
	}

	void ImGuiLayer::SetupDockSpace()
	{
		ImGuiIO& io = ImGui::GetIO();

		// position of visible windows
		ImGui::SetNextWindowPos( ImVec2( 0, 0 ) );
		ImGui::SetNextWindowSize( io.DisplaySize );
		ImGui::SetNextWindowBgAlpha( 0.0f );
		ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
		ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
		ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );

		ImGui::Begin( "DockSpace Window", nullptr,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus );

		ImGuiID dockspace_id = ImGui::GetID( "MyDockSpace" );
		ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), ImGuiDockNodeFlags_PassthruCentralNode );

		ImGui::End();
		ImGui::PopStyleVar( 3 );
	}

	void ImGuiLayer::NewWindow( const std::string& name, ImGuiWindowFlags flags )
	{
		m_Windows[name] = {true, flags};
	}

	void ImGuiLayer::CloseWindow( const std::string& name )
	{
		if (m_Windows.find( name ) != m_Windows.end())
		{
			m_Windows[name].isOpen = false;
		}
	}

	// need optimization and maybe to move to another script
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

	bool  ImGuiLayer::OnMouseButtonPressedEvent( MouseButtonPressedEvent& e )
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