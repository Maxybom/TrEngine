#include "Tepch.h"
#include "ImGuiLayer.h"
#include "TrEngine/event/ImGuiEventHandler.h"

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
		
		//window
		NewWindow( "Editor", ImGuiWindowFlags_MenuBar );
		NewWindow( "Console", ImGuiWindowFlags_NoCollapse );
		NewWindow( "Menu", ImGuiWindowFlags_NoCollapse );
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
				ImGui::Text( "Container %s", it->first.c_str() );
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
}